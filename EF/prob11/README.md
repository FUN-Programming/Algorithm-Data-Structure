# 授業中練習問題11

ソースコード：[source.c](./source.c)

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap(type, x, y) do {type t; t = x; x = y; y = t;} while (0)

#define ASCENDING 0
#define DESCENDING 1

typedef struct {
    int no;
    char name[20];
} Member;

int MemberNoCmp(const Member *x, const Member *y) {
    return x->no < y->no ? -1 : x->no > y->no ? 1 : 0;
}

int MemberNameCmp(const Member *x, const Member *y) {
    return strcmp(x->name, y->name);
}

void PrintLnMember(const Member *x) {
    printf("%d %s\n", x->no, x->name);
}

void bubble(Member *a, int n, int compare(const Member *x, const Member *y), int order) {
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = n - 1; j > i; j--)
            if (compare(a + j - 1 + order, a + j - order) > 0)
                swap(Member, a[j - 1], a[j]);
    }
}

void Print(const Member *data, int n) {
    int i;

    for (i = 0; i < n; i++)
        PrintLnMember(data + i);
}

typedef enum {
    TERMINATE, ASCEND_NO, ASCENT_NAME,
    DESCEND_NO, DESCEND_NAME, PRINT_ALL
} Menu;

Menu SelectMenu(void) {
    int i, ch;
    char *mstring[] = {
            "Sort Ascend No", "Sort Ascend Name",
            "Sort Descend No", "Sort Descend Name",
            "Print All"
    };

    do {
        for (i = TERMINATE; i < PRINT_ALL; i++) {
            printf("(%2d) %-24.24s  ", i + 1, mstring[i]);
            if ((i % 3) == 2)
                putchar('\n');
        }
        printf("( 0) 終了 : ");
        scanf("%d", &ch);
    } while (ch < TERMINATE || ch > PRINT_ALL);

    return (Menu) ch;
}

int main(void) {
    Menu menu;
    Member data[] = {
            {5, "umeda"},
            {7, "satoshi"},
            {6, "noyuri"},
            {0, "daisuke"},
            {0, "motoko"},
            {4, "agemi"},
            {9, "ito"},
            {2, "ohta"},
            {1, "takashi"},
            {3, "kouji"}
    };
    int ndata = sizeof(data) / sizeof(data[0]);

    do {
        int n;

        switch (menu = SelectMenu()) {
            case ASCEND_NO:
                bubble(data, ndata, MemberNoCmp, ASCENDING);
                break;
            case ASCENT_NAME:
                bubble(data, ndata, MemberNameCmp, ASCENDING);
                break;
            case DESCEND_NO:
                bubble(data, ndata, MemberNoCmp, DESCENDING);
                break;
            case DESCEND_NAME:
                bubble(data, ndata, MemberNameCmp, DESCENDING);
                break;
            case PRINT_ALL:
                Print(data, ndata);
                break;
        }
    } while (menu != TERMINATE);

    return 0;
}
```

1) このプログラムの動作直後に数字の **5** を入力したときの `data->name` が指している文字を示せ

2) このプログラムの動作直後に数字の **3** を入力したときの `data->name` が指している文字列を示せ

3) このプログラムの動作直後に数字の **3** を入力したときの *bubble* 関数中の `compare(a + j - 1 + order, a + j - order)` が呼び出されるのは何回か

4) このプログラムの動作直後に、数字の **3** を入力したときの *bubble* 関数中で `i = 0` のとき `swap(Member , a[j - 1], a[j])` が呼び出されるのは何回か

5) このプログラムの動作直後に数字の **4** を入力したときの `data->name` が指している文字列を示せ

6) 5)の状態から更に数字の **2** を入力したときの `data->name` が指している文字列を示せ

7) 5)の状態から更に数字の **2** を入力したときの *bubble* 関数中の `compare(a + j - 1 + order, a + j - order)` が呼び出されるのは何回か

8) 5)の状態から更に数字の **2** を入力したときの *bubble* 関数中で `i = 0` のとき `swap(Member, a[j - 1], a[j])` が呼び出されるのは何回か

## 提出

```
1) u
2) ito
3) 45回
4) 9回
5) umeda
6) agemi
7) 45回
8) 9回
```