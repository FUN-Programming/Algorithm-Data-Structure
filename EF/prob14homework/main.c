#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void Print(const Member *data, const int *sortindex, int n) {
    int i;

    for (i = 0; i < n; i++)
        PrintLnMember(data + sortindex[i]);
}

static void updownheap(Member *a, int *sortindex, int left, int right,
                       int compare(const Member *y, const Member *z)) {
    int temp = sortindex[left];
    int child;
    int parent;

    for (parent = left; parent < (right + 1) / 2; parent = child) {
        int cl = parent * 2 + 1;
        int cr = cl + 1;
        child = (cr <= right && compare(a + sortindex[cr], a + sortindex[cl]) > 0) ? cr : cl;

        if (compare(a + temp, a + sortindex[child]) > 0) // <------------------ ①
            break;
        sortindex[parent] = sortindex[child];
    }
    sortindex[parent] = temp;
}

void Heapsort(Member *a, int *sortindex, int n, int compare(const Member *y, const Member *z)) {
    int i;

    for (i = (n - 1) / 2; i >= 0; i--)
        updownheap(a, sortindex, i, n - 1, compare); // <------------------ ②

    for (i = n - 1; i > 0; i--) {
        swap(int, sortindex[0], sortindex[i]);
        updownheap(a, sortindex, 0, i - 1, compare);
    }
}

typedef enum {
    TERMINATE, ASCEND_NO, ASCEND_NAME, DESCEND_NO, DESCEND_NAME, PRINT_ALL
} Menu;

Menu SelectMenu(void) {
    int i, ch;
    char *mstring[] = {
            "Sort Ascend No", "Sort Ascend Name",
            "Sort Descend No", "Sord Descend Name",
            "Print All"
    };

    do {
        for (i = TERMINATE; i < PRINT_ALL; i++) {
            printf("(%2d) %-22.22s  ", i + 1, mstring[i]);
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
            {1, "takahashi"},
            {3, "konishi"},
            {5, "ueda"},
            {7, "sato"},
            {9, "niimi"},
            {8, "okonishi"},
            {2, "motoike"},
            {4, "agemi"}
    };
    int ndata = sizeof(data) / sizeof(data[0]);
    int i, *sortindex = calloc(ndata, sizeof(int));

    for (i = 0; i < ndata; i ++) sortindex[i] = i;

    do {
        switch (menu = SelectMenu()) {
            case ASCEND_NO:
                Heapsort(data, sortindex, ndata, AscendingMemberNoCmp);
                break;
            case ASCEND_NAME:
                Heapsort(data, sortindex, ndata, AscendingMemberNameCmp);
                break;
            case DESCEND_NO:
                Heapsort(data, sortindex, ndata, DescendingMemberNoCmp);
                break;
            case DESCEND_NAME:
                Heapsort(data, sortindex, ndata, DescendingMemberNameCmp);
                break;
            case PRINT_ALL:
                Print(data, sortindex, ndata);
                break;
        }
    } while (menu != TERMINATE);

    return 0;
}
