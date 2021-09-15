#include <malloc.h>
#include <stdio.h>
#include <string.h>

void main(void)
{
    FILE *input;
    long mail, password, calendar;
    char string[80], *sptr;

    sptr = malloc(80);
    mail = password = calendar = 0L;
    if ((input = fopen("status.log", "r")) != NULL) {
        while (!feof(input)) {
            fgets(sptr, 80, input);
            sptr[strlen(sptr) - 3] = '\0';
            if (strcmp(sptr + (strlen(sptr) - 5), "3Mail") == 0)
                mail++;
            if (strcmp(sptr + (strlen(sptr) - 3), "MTS") == 0)
                calendar++;
            if (strcmp(sptr + (strlen(sptr) - 13), "Password Mod!") == 0)
                password++;
        }
        fclose(input);
    }
    printf("Mail Accesses: %ld\nPassword Modifications: %ld\nCalendar Accesses: %ld\n", mail, password, calendar);
}
