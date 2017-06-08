#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PHYSCHECK_VISION 1
#define PHYSCHECK_HEIGHT 2
#define PHYSCHECK_NAME 4

typedef struct {
    double vision;
    int height;
} Body;

typedef struct {
    char *name;
    Body body;
} PhysCheck;

typedef struct __node {
    PhysCheck data;
    struct __node *next;
} Node;

typedef struct {
    Node *head;
    Node *crnt;
} List;

int PhysCheckHeightCmp(const PhysCheck *x, const PhysCheck *y) {
    return x->body.height < y->body.height ? -1 : x->body.height > y->body.height ? 1 : 0;
}

int PhysCheckVisionCmp(const PhysCheck *x, const PhysCheck *y) {
    return x->body.vision < y->body.vision ? -1 : x->body.vision > y->body.vision ? 1 : 0;
}

int PhysCheckNameCmp(const PhysCheck *x, const PhysCheck *y) {
    return strcmp(x->name, y->name);
}

void PrintPhysCheck(const PhysCheck *x) {
    printf("%0.2lf %d %s", x->body.vision, x->body.height, x->name);
}

void PrintLnPhysCheck(const PhysCheck *x) {
    printf("%0.2lf %d %s\n", x->body.vision, x->body.height, x->name);
}

PhysCheck ScanPhysCheck(const char *message, int sw) {
    PhysCheck temp;

    printf("%sするデータを入力してください。\n", message);

    if (sw & PHYSCHECK_VISION) {
        printf("視力：");
        scanf("%lf", &temp.body.vision);
    }

    if (sw & PHYSCHECK_HEIGHT) {
        printf("身長：");
        scanf("%d", &temp.body.height);
    }

    if (sw & PHYSCHECK_NAME) {
        temp.name = calloc(82, sizeof(char));
        printf("氏名：");
        scanf("%s", temp.name);
    }

    return temp;
}

static Node *AllocNode(void) {
    return calloc(1, sizeof(Node));
}

static void SetNode(Node *n, const PhysCheck *x, const Node *next) {
    n->data = *x;
    n->next = next;
}

void Initialize(List *list) {
    list->head = NULL;
    list->crnt = NULL;
}

Node *Search(List *list, const PhysCheck *x,
             int compare(const PhysCheck *x, const PhysCheck *y)) {
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

void InsertFront(List *list, const PhysCheck *x) {
    Node *ptr = list->head;
    list->head = list->crnt = AllocNode();
    SetNode(list->head, x, ptr);
}

void InsertRear(List *list, const PhysCheck *x) {
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
    free(list->head->data.name);
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
        PrintPhysCheck(&list->crnt->data);

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
            PrintLnPhysCheck(&ptr->data);
            ptr = ptr->next;
        }
    }
}

void Terminate(List *list) {
    Clear(list);
}

typedef enum {
    TERMINATE, INS_FRONT, INS_REAR, RMV_FRONT, RMV_REAR, PRINT_CRNT,
    RMV_CRNT, SRCH_VISION, SRCH_HEIGHT, SRCH_NAME, PRINT_ALL, CLEAR
} Menu;

Menu SelectMenu(void) {
    int i, ch;
    char *mstring[] = {
            "先頭にノードを挿入", "末尾にノードを挿入", "先頭のノードを削除",
            "末尾のノードを削除", "着目ノードを表示", "着目ノードを削除",
            "視力で探索", "身長で探索", "氏名で探索", "全ノードを表示", "全ノードを削除"
    };

    do {
        for (i = TERMINATE; i < CLEAR; i++) {
            printf("(%2d) %-21s   \t", i + 1, mstring[i]);
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
    PhysCheck x;

    Initialize(&list);

    do {
        switch (menu = SelectMenu()) {
            case INS_FRONT:
                x = ScanPhysCheck("先頭に挿入", PHYSCHECK_VISION | PHYSCHECK_HEIGHT | PHYSCHECK_NAME);
                InsertFront(&list, &x);
                break;
            case INS_REAR:
                x = ScanPhysCheck("末尾に挿入", PHYSCHECK_VISION | PHYSCHECK_HEIGHT | PHYSCHECK_NAME);
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
            case SRCH_VISION:
                x = ScanPhysCheck("探索", PHYSCHECK_VISION);
                if (Search(&list, &x, PhysCheckVisionCmp) != NULL)
                    PrintLnCurrent(&list);
                else
                    puts("その視力のデータはありません。");
                break;
            case SRCH_HEIGHT:
                x = ScanPhysCheck("探索", PHYSCHECK_HEIGHT);
                if (Search(&list, &x, PhysCheckHeightCmp) != NULL)
                    PrintLnCurrent(&list);
                else
                    puts("その身長のデータはありません。");
                break;
            case SRCH_NAME:
                x = ScanPhysCheck("探索", PHYSCHECK_NAME);
                if (Search(&list, &x, PhysCheckNameCmp) != NULL)
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