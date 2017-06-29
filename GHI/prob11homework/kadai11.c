#include <stdio.h>
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

void shaker(Member *a, int n, int compare(const Member *x, const Member *y), int order) {
    int left = 0;
    int right = n - 1;
    int last = right;

    while (left < right) {
        int j;
        for (j = right; j > left; j--) {
            if (compare(a + j - 1 + order, a + j - order) > 0) {
                swap(Member, a[j - 1], a[j]);
                last = j;
            }
        }
        left = last;

        for (j = left; j < right; j++) {
            if (compare(a + j + order, a + j + 1 - order) > 0) {
                swap(Member, a[j], a[j + 1]);
                last = j;
            }
        }
        right = last;
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
        switch (menu = SelectMenu()) {
            case ASCEND_NO:
                shaker(data, ndata, MemberNoCmp, ASCENDING);
                break;
            case ASCENT_NAME:
                shaker(data, ndata, MemberNameCmp, ASCENDING);
                break;
            case DESCEND_NO:
                shaker(data, ndata, MemberNoCmp, DESCENDING);
                break;
            case DESCEND_NAME:
                shaker(data, ndata, MemberNameCmp, DESCENDING);
                break;
            case PRINT_ALL:
                Print(data, ndata);
                break;
            default:
                break;
        }
    } while (menu != TERMINATE);

    return 0;
}
