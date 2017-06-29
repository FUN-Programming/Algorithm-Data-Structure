#include <stdio.h>
#include <string.h>

#define  String_Max 82

void recur3(char *st) {
    int n = strlen(st);

    if (n > 0) {
        if (n > 1) recur3(st + 2);
        else recur3(st + 1);
        printf("%c", *st);
        recur3(st + 1);
    }
}

int main(void) {
    char x[String_Max];

    printf("Input String: ");
    scanf("%s", x);

    recur3(x);
    printf("\n");

    return 0;
}
