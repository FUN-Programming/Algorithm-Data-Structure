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
    struct __node *next;
} Node;

typedef struct {
    Node *head;
    Node *crnt;
} List;

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

static Node *AllocNode(void) {
    return calloc(1, sizeof(Node));
}

static void SetNode(Node *n, const Member *x, const Node *next) {
    n->data = *x;
    n->next = next;
}

void Initialize(List *list) {
    list->head = NULL;
    list->crnt = NULL;
}

Node *Search(List *list, const Member *x,
             int compare(const Member *x, const Member *y)) {
    Node *ptr = list->head;

    while (ptr != NULL) {
        if (compare(&ptr->data, x) == 0) {
            list->crnt = ptr;
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void InsertFront(List *list, const Member *x) {
    Node *ptr = list->head;
    list->head = list->crnt = AllocNode();
    SetNode(list->head, x, ptr);
}

void InsertRear(List *list, const Member *x) {
    if (list->head == NULL)
        InsertFront(list, x);
    else {
        Node *ptr = list->head;
        while (ptr->next != NULL)
            ptr = ptr->next;
        ptr->next = list->crnt = AllocNode();
        SetNode(ptr->next, x, NULL);
    }
}

void RemoveFront(List *list) {
    if (list->head != NULL) {}
    Node *ptr = list->head->next;
    free(list->head);
    list->head = list->crnt = ptr;
}

void RemoveRear(List *list) {
    if (list->head != NULL) {
        if ((list->head)->next == NULL)
            RemoveFront(list);
        else {
            Node *ptr = list->head;
            Node *pre;

            while (ptr->next != NULL) {
                pre = ptr;
                ptr = ptr->next;
            }
            pre->next = NULL;
            free(ptr);
            list->crnt = pre;
        }
    }
}

void RemoveCurrent(List *list) {
    if (list->head != NULL) {
        if (list->crnt == list->head)
            RemoveFront(list);
        else {
            Node *ptr = list->head;

            while (ptr->next != list->crnt)
                ptr = ptr->next;
            ptr->next = list->crnt->next;
            free(list->crnt);
            list->crnt = ptr;
        }
    }
}

void Clear(List *list) {
    while (list->head != NULL)
        RemoveFront(list);
    list->crnt = NULL;
}

void PrintCurrent(const List *list) {
    if (list->crnt == NULL)
        printf("着目ノードはありません。");
    else
        PrintMember(&list->crnt->data);
}

void PrintLnCurrent(const List *list) {
    PrintCurrent(list);
    putchar('\n');
}

void Print(const List *list) {
    if (list->head == NULL)
        puts("ノードがありません。");
    else {
        Node *ptr = list->head;

        puts("【一覧表】");
        while (ptr != NULL) {
            PrintLnMember(&ptr->data);
            ptr = ptr->next;
        }
    }
}

void Terminate(List *list) {
    Clear(list);
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
        printf("( 0) 終了 ：");
        scanf("%d", &ch);
    } while (ch < TERMINATE || ch > CLEAR);

    return (Menu) ch;
}

int main(void) {
    Menu menu;
    List list;
    Member x;

    Initialize(&list);

    do {
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
            case RMV_CRNT:
                RemoveCurrent(&list);
                break;
            case PRINT_CRNT:
                PrintLnCurrent(&list);
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