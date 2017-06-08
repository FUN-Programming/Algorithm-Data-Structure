#include <stdio.h>

#define MAX 10

typedef struct {
    char name[20];
    int height;
    double vision;
} PhysCheck;

typedef struct {
    int max;
    int ptr;
    PhysCheck stk[MAX];
} PhysCheckStack;

int Initialize(PhysCheckStack *s, int max) {
    s->ptr = 0;
    s->max = max;
    return 0;
}

int Push(PhysCheckStack *s, PhysCheck x) {
    if (s->ptr >= s->max) return -1;
    s->stk[s->ptr] = x;
    s->ptr++;
    return 0;
}

int Pop(PhysCheckStack *s, PhysCheck *x) {
    if (s->ptr <= 0) return -1;
    s->ptr--;
    *x = s->stk[s->ptr];
    return 0;
}

int Peek(PhysCheckStack *s, PhysCheck *x) {
    if (s->ptr <= 0) return -1;
    *x = s->stk[s->ptr - 1];
    return 0;
}

int Capacity(const PhysCheckStack *s) {
    return s->max;
}

int Size(const PhysCheckStack *s) {
    return s->ptr;
}

void PrintOne(const PhysCheck *x) {
    printf("%s %d %0.2lf", x->name, x->height, x->vision);
}

void Print(const PhysCheckStack *s) {
    int i;

    for (i = 0; i < s->ptr; i++) {
        PrintOne(&s->stk[i]);
        putchar('\n');
    }
}

int main(void) {
    PhysCheckStack s;

    Initialize(&s, MAX);

    while (1) {
        int menu;
        PhysCheck x;
        printf("現在のデータ数:%d/%d\n", Size(&s), Capacity(&s));
        printf("(1) プッシュ (2) ポップ (3) ピーク (4) 表示 (0) 終了:");
        scanf("%d", &menu);
        // ----------------①

        if (menu == 0) break;

        switch (menu) {
            case 1:
                printf("名前：");
                scanf("%s", x.name);
                printf("身長：");
                scanf("%d", &x.height);
                printf("視力：");
                scanf("%lf", &x.vision);
                if (Push(&s, x) == -1)
                    puts("\aエラー；プッシュに失敗しました。");
                break;
            case 2:
                if (Pop(&s, &x) == -1)
                    puts("\aエラー：ポップに失敗しました。");
                else {
                    printf("ポップしたデータは ");
                    PrintOne(&x);
                    printf(" です。\n");
                }
                break;
            case 3:
                if (Peek(&s, &x) == -1)
                    puts("\aエラー：ピークに失敗しました。");
                else {
                    printf("ピークしたデータは ");
                    PrintOne(&x);
                    printf(" です。\n");
                }
                break;
            case 4:
                Print(&s);
                break;
        }
    }
    return 0;
}