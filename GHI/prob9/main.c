#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMBER_NO 1
#define MEMBER_NAME 2

typedef struct {
    int no;
    char name[20];
} Member;

typedef struct __node {
    Member data;
    struct __node *prev;
    struct __node *next;
} Dnode;

typedef struct {
    Dnode *head;
    Dnode *crnt;
} Dlist;

int MemberNoCmp(const Member *x, const Member *y) {
    return x->no < y->no ? -1 : x->no > y->no ? 1 : 0;
}

int MemberNameCmp(const Member *x, const Member *y) {
    return strcmp(x->name, y->name);
}

void PrintMember(const Member *x) {
    printf("%d %s", x->no, x->name);
}

void PrintLnMember(const Member *x) {
    printf("%d %s\n", x->no, x->name);
}

Member ScanMember(const char *message, int sw) {
    Member temp;

    printf("%sするデータを入力してください。\n", message);

    if (sw & MEMBER_NO) {
        printf("番号：");
        scanf("%d", &temp.no);
    }

    if (sw & MEMBER_NAME) {
        printf("氏名：");
        scanf("%s", temp.name);
    }

    return temp;
}

static Dnode *AllocDnode(void) {
    return calloc(1, sizeof(Dnode));
}

static void SetDnode(Dnode *n, const Member *x, const Dnode *prev, const Dnode *next) {
    n->data = *x;
    n->prev = (Dnode *) prev;
    n->next = (Dnode *) next;
}

static int IsEmpty(const Dlist *list) {
    return list->head->next == list->head;
}

void Initialize(Dlist *list) {
    Dnode *dummyNode = AllocDnode();
    list->head = list->crnt = dummyNode;
    dummyNode->prev = dummyNode->next = dummyNode;
}

void PrintCurrent(const Dlist *list) {
    if (IsEmpty(list))
        printf("着目要素はありません。");
    else
        PrintMember(&list->crnt->data);
}

void PrintLnCurrent(const Dlist *list) {
    PrintCurrent(list);
    putchar('\n');
}

Dnode *Search(Dlist *list, const Member *x,
              int compare(const Member *x, const Member *y)) {
    Dnode *ptr = list->head->next;

    while (ptr != list->head) {
        if (compare(&ptr->data, x) == 0) {
            list->crnt = ptr;
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void Print(const Dlist *list) {
    if (IsEmpty(list))
        puts("ノードがありません。");
    else {
        Dnode *ptr = list->head->next;

        puts("【一覧表】");
        while (ptr != list->head) {
            PrintLnMember(&ptr->data);
            ptr = ptr->next;
        }
    }
}

void InsertAfter(Dlist *list, Dnode *p, const Member *x) {
    Dnode *ptr = AllocDnode();
    Dnode *nxt = p->next;

    p->next = p->next->prev = ptr;
    SetDnode(ptr, x, p, nxt);
    list->crnt = ptr;
}

void InsertFront(Dlist *list, const Member *x) {
    InsertAfter(list, list->head, x);
}

void InsertRear(Dlist *list, const Member *x) {
    InsertAfter(list, list->head->prev, x);
}

void Remove(Dlist *list, Dnode *p) {
    p->prev->next = p->next;
    p->next->prev = p->prev;
    list->crnt = p->prev;
    free(p);
    if (list->crnt == list->head)
        list->crnt = list->head->next;
}

void RemoveFront(Dlist *list) {
    if (!IsEmpty(list))
        Remove(list, list->head->next);
}

void RemoveRear(Dlist *list) {
    if (!IsEmpty(list))
        Remove(list, list->head->prev);
}

void RemoveCurrent(Dlist *list) {
    if (list->crnt != list->head)
        Remove(list, list->crnt);
}

void Clear(Dlist *list) {
    while (!IsEmpty(list))
        RemoveFront(list);
}

void Terminate(Dlist *list) {
    Clear(list);
    free(list->head);
}

typedef enum {
    TERMINATE, INS_FRONT, INS_REAR, RMV_FRONT, RMV_REAR, PRINT_CRNT,
    RMV_CRNT, SRCH_NO, SRCH_NAME, PRINT_ALL, CLEAR
} Menu;

Menu SelectMenu(void) {
    int i, ch;
    char *mstring[] = {
            "先頭にノードを挿入", "末尾にノードを挿入", "先頭のノードを削除",
            "末尾のノードを削除", "着目ノードを表示", "着目ノードを削除",
            "番号で探索", "氏名で探索", "全ノードを表示", "全ノードを削除"
    };

    do {
        for (i = TERMINATE; i < CLEAR; i++) {
            printf("(%2d) %-18.18s  ", i + 1, mstring[i]);
            if ((i % 3) == 2)
                putchar('\n');
        }
        printf("( 0) 終了 : ");
        scanf("%d", &ch);
    } while (ch < TERMINATE || ch > CLEAR);

    return (Menu) ch;
}

int main(void) {
    Menu menu;
    Dlist list;

    Initialize(&list);

    do {
        int n;
        Member x;
        Member *ptr;

        switch (menu = SelectMenu()) {
            case INS_FRONT:
                x = ScanMember("先頭に挿入", MEMBER_NO | MEMBER_NAME);
                InsertFront(&list, &x);
                break;
            case INS_REAR:
                x = ScanMember("末尾に挿入", MEMBER_NO | MEMBER_NAME);
                InsertRear(&list, &x);
                break;
            case RMV_FRONT:
                RemoveFront(&list);
                break;
            case RMV_REAR:
                RemoveRear(&list);
                break;
            case PRINT_CRNT:
                PrintLnCurrent(&list);
                break;
            case RMV_CRNT:
                RemoveCurrent(&list);
                break;
            case SRCH_NO:
                x = ScanMember("探索", MEMBER_NO);
                if (Search(&list, &x, MemberNoCmp) != NULL)
                    PrintLnCurrent(&list);
                else
                    puts("その番号のデータはありません。");
                break;
            case SRCH_NAME:
                x = ScanMember("探索", MEMBER_NAME);
                if (Search(&list, &x, MemberNameCmp) != NULL)
                    PrintLnCurrent(&list);
                else
                    puts("その名前のデータはありません。");
                break;
            case PRINT_ALL:
                Print(&list);
                break;
            case CLEAR:
                Clear(&list);
                break;
        }
    } while (menu != TERMINATE);

    Terminate(&list);

    return 0;
}
