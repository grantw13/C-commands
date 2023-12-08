#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int is_leap(int year) {
    if (year % 400 == 0 && year % 100 != 0) return 1;
    else return 0;
}

int main(int argc, char *argv[]) {
    int curday, curmon, curyear, day, month, totalb = 0, totalt = 0, result = 0;
    int yearbuf = 0, daybuf = 0, monbuf = 0, temp = 0, j = 0, i = 0;
    time_t t;
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    setbuf(stdout, NULL);

    //time variables and output
    struct tm* curr_time;
    t = time(NULL);
    curr_time = localtime(&t);
    curday = curr_time->tm_mday;
    curmon = curr_time->tm_mon + 1;
    curyear = curr_time->tm_year + 1900;
    char name[15];

    FILE *fp;
    fp = popen("whoami", "r");
    fscanf(fp, "%s", name);
    printf("Hello %s\n", name);

    //calculate day offset
    if (argc > 1) {
	temp = *argv[1];
        j = curmon - 2;
        if (j < 0) {
            j = j + 12;
            yearbuf = yearbuf + 1;
            monbuf = monbuf - j;
        }
        while (temp > days[j]) {
            temp = temp - days[j];
            monbuf = monbuf + 1;
            j = j - 1;

            if (j < 0) {
                j = 11;
                yearbuf = yearbuf + 1;
            }
        }
        if (temp < curday) daybuf = temp;
        else {
            daybuf = days[j] - temp;
            monbuf = monbuf - 1;
        }
        printf("Offset by %d days, the date is %d-%02d-%02d %02d:%02d:%02d\n", temp, curyear - yearbuf, curmon - monbuf, curday - daybuf, curr_time->tm_hour, curr_time->tm_min, curr_time->tm_sec);
    } else {
        printf("The current date is %d-%02d-%02d %02d:%02d:%02d\n", curyear, curmon, curday, curr_time->tm_hour, curr_time->tm_min, curr_time->tm_sec);
    }

    printf("Enter your day of birth (DD)\n");
    scanf("%d", &day);
    printf("Enter your month of birth (MM)\n");
    scanf("%d", &month);

    //check input
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        printf("Invalid input. Closing program.\n");
        return 0;
    }
    //calculate days until birthday from jan 1
    for (i = 0; i < month - 1; i++) {
        totalb = totalb + days[i];
    }
    totalb = totalb + day;

    //calculate days until today from jan 1
    for (i = 0; i < curmon - 1; i++) {
        totalt = totalt + days[i];
    }
    totalt = totalt + curday;

    if (totalb < totalt) {
        result = 365 - totalt + totalb;
    } else {
        result = totalb - totalt;
    }

    if (result != 0) {
        printf("\nYour birthday is in %d days.\n", result);
    } else {
        printf("Happy birthday!\n");
    }
    
    return 0;
}
