#include <stdio.h>

#define MAX 10

typedef struct {
    int max;
    int ptr;
    int stk[MAX];
} IntStack;

int Initialize(IntStack *s, int max) {
    s->ptr = 0;
    s->max = max;
    return 0;
}

int Push(IntStack *s, int x) {
    if (s->ptr >= s->max) return -1;
    s->stk[s->ptr] = x;
    s->ptr++;
    return 0;
}

int Pop(IntStack *s, int *x) {
    if (s->ptr <= 0) return -1;
    s->ptr--;
    *x = s->stk[s->ptr];
    return 0;
}

int Peek(IntStack *s, int *x) {
    if (s->ptr <= 0) return -1;
    *x = s->stk[s->ptr - 1];
    return 0;
}

int Capacity(const IntStack *s) {
    return s->max;
}

int Size(const IntStack *s) {
    return s->ptr;
}

void Print(const IntStack *s) {
    int i;

    for (i = 0; i < s->ptr; i++)
        printf("%d ", s->stk[i]);
    putchar('\n');
}

int main() {
    IntStack s;

    Initialize(&s, MAX);

    while (1) {
        int menu, x = 0;
        printf("現在のデータ数：%d/%d\n", Size(&s), Capacity(&s));
        printf("(1) プッシュ (2) ポップ (3) ピーク (4) 表示 (0) 終了：");
        scanf("%d", &menu);
        //-----------------①

        if (menu == 0) break;

        switch (menu) {
            case 1:
                printf("データ：");
                scanf("%d", &x);
                if (Push(&s, x) == -1)
                    puts("\aエラー：プッシュに失敗しました。");
                break;
            case 2:
                if (Pop(&s, x) == -1)
                    puts("\aエラー：プッシュに失敗しました。");
                else
                    printf("ポップしたデータは%dです。\n", x);
                break;
            case 3:
                if (Peek(&s, &x) == -1)
                    puts("\aエラー：ピークに失敗しました。");
                else
                    printf("ピークしたデータは%dです。\n", x);
                break;
            case 4:
                Print(&s);
                break;
            default:break;
        }
    }

    return 0;
}