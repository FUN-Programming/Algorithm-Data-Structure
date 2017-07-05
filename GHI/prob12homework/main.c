#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap(type, x, y) do {type t; t = x; x = y; y = t;} while(0)

typedef struct {
    int no;
    char name[20];
} Member;

int AscendingMemberNoCmp(const Member *x, const Member *y) {
    return x->no < y->no ? -1 : x->no > y->no ? 1 : 0;
}

int DescendingMemberNoCmp(const Member *x, const Member *y) {
    return x->no < y->no ? 1 : x->no > y->no ? -1 : 0;
}

int AscendingMemberNameCmp(const Member *x, const Member *y) {
    return strcmp(x->name, y->name);
}

int DescendingMemberNameCmp(const Member *x, const Member *y) {
    return strcmp(y->name, x->name);
}

void PrintLnMember(const Member *x) {
    printf("%d %s\n", x->no, x->name);
}

void Print(const Member *data, int n) {
    int i;

    for (i = 0; i < n; i++) {
        PrintLnMember(data + i);
    }
}

void quick(Member *a, int left, int right, int compare(const Member *y, const Member *z)) {
    int pl = left;
    int pr = right;
    Member x = a[(pl + pr) / 2];

    do {
        while (compare(&x, a + pl) > 0) pl++;
        while (compare(a + pr, &x) > 0) pr--;
        if (pl <= pr) {
            swap(Member, a[pl], a[pr]);
            pl++;
            pr--;
        }
    } while (pl <= pr);
    // ------------------------------------- 1
    if (left < pr) quick(a, left, pr, compare);
    if (pl < right) quick(a, pl, right, compare);
}

typedef enum {
    TERMINATE, ASCEND_NO, ASCEND_NAME,
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
            printf("(%2d) %-18.18s  ", i + 1, mstring[i]);
            if ((i % 3) == 2)
                putchar('\n');
        }
        printf("( 0) End : ");
        scanf("%d", &ch);
    } while (ch < TERMINATE || ch > PRINT_ALL);

    return (Menu) ch;
}

int main(void) {
    Menu menu;
    Member data[] = {
            {1, "takashi"},
            {3, "kouji"},
            {5, "umeda"},
            {7, "satoshi"},
            {6, "noyuri"},
            {2, "daisuke"},
            {0, "motoko"},
            {4, "agemi"},
            {9, "ito"},
            {2, "ohta"}
    };

    int ndata = sizeof(data) / sizeof(data[0]);

    do {
        switch (menu = SelectMenu()) {
            case ASCEND_NO:
                quick(data, 0, ndata-1, AscendingMemberNoCmp);
                break;
            case ASCEND_NAME:
                quick(data, 0, ndata-1, AscendingMemberNameCmp);
                break;
            case DESCEND_NO:
                quick(data, 0, ndata-1, DescendingMemberNoCmp);
                break;
            case DESCEND_NAME:
                quick(data, 0, ndata-1, DescendingMemberNameCmp);
                break;
            case PRINT_ALL:
                Print(data, ndata);
                break;
        }
    } while (menu != TERMINATE);

    return 0;
}
