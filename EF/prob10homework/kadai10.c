#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define  String_Max 82

typedef struct {
    int max;
    int ptr;
    char **stk;
} StringsStack;

int Initialize(StringsStack *s, int max) {
    s->ptr = 0;
    if ((s->stk = calloc(max, sizeof(char *))) == NULL) {
        s->max = 0;
        return -1;
    }
    s->max = max;
    return 0;
}

void Terminate(StringsStack *s) {
    free(s->stk);
}

int Push(StringsStack *s, char *x) {
    if (s->ptr >= s->max) return -1;
    s->stk[s->ptr++] = x;
    return 0;
}


int Pop(StringsStack *s, char **x) {
    if (s->ptr <= 0) return -1;
    *x = s->stk[--s->ptr];
    return 0;
}

int IsEmpty(const StringsStack *s) {
    return s->ptr <= 0;
}

void recur3(char *st) {
    StringsStack stk;
    char *temp = st;

    if (Initialize(&stk, 100) == -1) {
        puts("Error: Failed Initialize.");
        return;
    }

    while (1) {

        while (strlen(temp) > 0) {
            if (Push(&stk, temp) == -1) {
                puts("Error: Failed Push.");
                return;
            }
            temp += (strlen(temp) > 1) ? 2 : 1;
        }

        if (IsEmpty(&stk)) {
            break;
        }

        if (Pop(&stk, &temp) == -1) {
            puts("Error: Failed Pop.");
            return;
        }
        printf("%c", *temp);
        temp += 1;
    }

    Terminate(&stk);
}

int main(void) {
    char x[String_Max];

    printf("Input String: ");
    scanf("%s", x);

    recur3(x);
    printf("\n");

    return 0;
}
