#include <stdio.h>
#include <string.h>

void main(void)
{
    FILE *input;
    char string[161];
    
    if ((input = fopen("nasa.log", "r")) != NULL) {
        while (!feof(input)) {
            fgets(string, 160, input);
            string[strlen(string) - 1] = '\0';
            printf("%s\n", string);
        }
        fclose(input);
    }
}

