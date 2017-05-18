#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX 10

typedef struct {
    double vision;
    int height;
} Body;

typedef struct {
    Body body;
    char name[20];
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
    printf("%s %.2f %d", x->name, x->body.vision, x->body.height);
}

void Print(const PhysCheckStack *s) {
    int i;

    for (i = 0; i < s->ptr; i++) {
        PrintOne(&s->stk[i]);
        printf("\n");
    }
}

char *bm_match(char *pat, char *txt) {
    char *pt;
    char *pp;
    int txt_len = (int) strlen(txt);
    int pat_len = (int) strlen(pat);
    int skip[UCHAR_MAX + 1];
    int i;

    for (i = 0; i <= UCHAR_MAX; i++)
        skip[i] = pat_len;
    for (pp = pat; *pp != '\0'; pp++)
        skip[*pp] = (int) (strlen(pp) - 1);
    skip[*(pp - 1)] = pat_len;

    pt = txt + pat_len - 1;
    while (pt < txt + txt_len) {
        pp = pat + pat_len - 1;
        while (*pt == *pp) {
            if (pp == pat) return pt;
            pp--;
            pt--;
        }
        pt += (skip[*pt] > strlen(pp)) ? (size_t) skip[*pt] : strlen(pp);
    }
    return NULL;
}

int Count(PhysCheckStack *s, PhysCheck *x) {
    int i, counter = 0;

    for (i = 0; i < s->ptr; i++) {
        if (bm_match(x->name, s->stk[i].name) != NULL) {
            counter++;
        }
    }

    return counter;
}

int main() {
    PhysCheckStack s;

    Initialize(&s, MAX);

    while (1) {
        int menu, counter;
        PhysCheck x;
        printf("現在のデータ数：%d/%d\n", Size(&s), Capacity(&s));
        printf("(1)プッシュ (2)ポップ (3)ピーク (4)表示 (5)計数 (0)終了：");
        scanf("%d", &menu);
        //-----------------①

        if (menu == 0) break;

        switch (menu) {
            case 1:
                printf("名前：");
                scanf("%s", x.name);
                printf("視力：");
                scanf("%lf", &x.body.vision);
                printf("身長：");
                scanf("%d", &x.body.height);
                if (Push(&s, x) == -1)
                    puts("\aエラー：プッシュに失敗しました。");
                break;
            case 2:
                if (Pop(&s, &x) == -1)
                    puts("\aエラー：プッシュに失敗しました。");
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
            case 5:
                printf("パターン：");
                scanf("%s", x.name);
                if ((counter = Count(&s, &x)) == 0)
                    puts("パターンは存在しません.");
                else
                    printf("パターンの個数は %d 個です。\n", counter);
                break;
            default:
                break;
        }
    }

    return 0;
}