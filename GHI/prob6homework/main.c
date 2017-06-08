#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    double vision;
    int height;
} Body;

typedef struct {
    char *name;
    Body body;
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
    printf("%s %d %0.2lf", x->name, x->body.height, x->body.vision);
}

void Print(const PhysCheckStack *s) {
    int i;

    for (i = 0; i < s->ptr; i++) {
        PrintOne(&s->stk[i]);
        putchar('\n');
    }
}

int Search(PhysCheckStack *s, PhysCheck *x) {
    int i, counter = 0;

    for (i = 0; i < s->ptr; i++) {
        if (strstr(s->stk[i].name, x->name) != NULL) {
            PrintOne(&s->stk[i]);
            putchar('\n');
            counter++;
        }
    }

    return counter;
}

int main(void) {
    PhysCheckStack s;

    Initialize(&s, MAX);

    while (1) {
        int menu, search;
        PhysCheck x;
        printf("現在のデータ数:%d/%d\n", Size(&s), Capacity(&s));
        printf("(1)プッシュ (2)ポップ (3)ピーク (4)表示 (5)探索 (0)終了:");
        scanf("%d", &menu);
        // ----------------①

        if (menu == 0) break;

        switch (menu) {
            case 1:
                x.name = calloc(20, sizeof(char));
                printf("名前：");
                scanf("%s", x.name);
                printf("身長：");
                scanf("%d", &x.body.height);
                printf("視力：");
                scanf("%lf", &x.body.vision);
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
                free(x.name);
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
            case 5:
                x.name = calloc(20, sizeof(char));
                printf("パターン：");
                scanf("%s", x.name);
                if ((search = Search(&s, &x)) == 0)
                    puts("パターンは存在しません.");
                else
                    printf("パターンは %d 個見つかりました.\n", search);
                free(x.name);
                break;
        }
    }
    return 0;
}