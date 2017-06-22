#include <stdio.h>
#include <string.h>

#define String_Max 82

void recur2(char *st) {
    int n = strlen(st);

    if (n > 0) {
        recur2(st + 1);
        if (n > 1) recur2(st + 2);
        else recur2(st + 1);
        printf("%c", *st);
    }
}

int main(void) {
    char x[String_Max];

    printf("Input string : ");
    scanf("%s", x);
    recur2(x);
    printf("\n");

    return 0;
}
