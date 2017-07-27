#include <stdio.h>
#include <string.h>

#define swap(type, x, y) do {type t; t = x; x = y; y = t;} while(0)

typedef struct {
    int no;
    char name[20];
} Member;

int counter = 0;

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

    printf("[\n");
    for (i = 0; i < n; i++) {
        printf("\t{%d,\"%s\"},\n", data[i].no, data[i].name);
    }
    printf("]\n");

//    for (i = 0; i < n; i++)
//        PrintLnMember(data + i);
}

static void updownheap(Member *a, int left, int right,
                       int compare(const Member *y, const Member *z)) {
    Member temp = a[left];
    int child;
    int parent;

    for (parent = left; parent < (right + 1) / 2; parent = child) {
        int cl = parent * 2 + 1;
        int cr = cl + 1;
        child = (cr <= right && compare(a + cr, a + cl) > 0) ? cr : cl;

        if (++counter && compare(&temp, a + child) > 0) // <------------------ ①
            break;
        a[parent] = a[child];
    }
    a[parent] = temp;
}

void heapsort(Member *a, int n, int compare(const Member *y, const Member *z)) {
    int i;
    counter = 0;

    for (i = (n - 1) / 2; i >= 0; i--) {
        updownheap(a, i, n - 1, compare); // <------------------ ②
        printf("i=%d: ", i);
        Print(a, n);
    }

    for (i = n - 1; i > 0; i--) {
        swap(Member, a[0], a[i]);
        updownheap(a, 0, i - 1, compare);
    }

    printf("counter = %d\n", counter);
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

    do {
        switch (menu = SelectMenu()) {
            case ASCEND_NO:
                heapsort(data, ndata, AscendingMemberNoCmp);
                break;
            case ASCEND_NAME:
                heapsort(data, ndata, AscendingMemberNameCmp);
                break;
            case DESCEND_NO:
                heapsort(data, ndata, DescendingMemberNoCmp);
                break;
            case DESCEND_NAME:
                heapsort(data, ndata, DescendingMemberNameCmp);
                break;
            case PRINT_ALL:
                Print(data, ndata);
                break;
        }
    } while (menu != TERMINATE);

    return 0;
}
