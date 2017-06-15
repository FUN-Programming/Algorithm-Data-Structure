#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PHYSCHECK_NAME 1
#define PHYSCHECK_VISION 2
#define PHYSCHECK_HEIGHT 4

typedef struct {
    double vision;
    int height;
} Body;

typedef struct {
    Body body;
    char *name;
} PhysCheck;

typedef struct __node {
    PhysCheck data;
    struct __node *next;
} Node;

typedef struct {
    Node *head;
    Node *crnt;
} List;

int PhysCheckVisionCmp(const PhysCheck *x, const PhysCheck *y) {
    return x->body.vision < y->body.vision ? -1 : x->body.vision > y->body.vision ? 1 : 0;
}

int PhysCheckHeightCmp(const PhysCheck *x, const PhysCheck *y) {
    return x->body.height < y->body.height ? -1 : x->body.height > y->body.height ? 1 : 0;
}

int PhysCheckNameCmp(const PhysCheck *x, const PhysCheck *y) {
    return strcmp(x->name, y->name);
}

void PrintPhysCheck(const PhysCheck *x) {
    printf("%0.1lf %d %s", x->body.vision, x->body.height, x->name);
}

void PrintLnPhysCheck(const PhysCheck *x) {
    printf("%0.1lf %d %s\n", x->body.vision, x->body.height, x->name);
}

PhysCheck ScanPhysCheck(const char *message, int sw) {
    PhysCheck temp;

    printf("Please input data to %s.\n", message);

    if (sw & PHYSCHECK_VISION) {
        printf("vision: ");
        scanf("%lf", &temp.body.vision);
    }

    if (sw & PHYSCHECK_HEIGHT) {
        printf("height: ");
        scanf("%d", &temp.body.height);
    }

    if (sw & PHYSCHECK_NAME) {
        temp.name = calloc(82, sizeof(char));
        printf("name: ");
        scanf("%s", temp.name);
    }

    return temp;
}

static Node *AllocNode(void) {
    return calloc(1, sizeof(Node));
}

static void SetNode(Node *n, const PhysCheck *x, Node *next) {
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
    if (list->head != NULL) {
        Node *ptr = list->head->next;
        free(list->head);
        list->head = list->crnt = ptr;
    }
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
        printf("The current node does not exist.");
    else
        PrintPhysCheck(&list->crnt->data);
}

void PrintLnCurrent(const List *list) {
    PrintCurrent(list);
    putchar('\n');
}

void Print(const List *list) {
    if (list->head == NULL)
        puts("The node does not exist.");
    else {
        Node *ptr = list->head;

        puts("---List---");
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
            "Insert Front", "Insert Rear", "Remove Front",
            "Remove Rear", "Print Current", "Remove Current",
            "Search Vision", "Search Height", "Search Name",
            "Print All", "Clear All"
    };

    do {
        for (i = TERMINATE; i < CLEAR; i++) {
            printf("(%2d) %-18.18s  ", i + 1, mstring[i]);
            if ((i % 3) == 2)
                putchar('\n');
        }
        printf("( 0) End：");
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
                x = ScanPhysCheck("insert front", PHYSCHECK_VISION | PHYSCHECK_HEIGHT | PHYSCHECK_NAME);
                InsertFront(&list, &x);
                break;
            case INS_REAR:
                x = ScanPhysCheck("insert rear", PHYSCHECK_VISION | PHYSCHECK_HEIGHT | PHYSCHECK_NAME);
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
            case SRCH_VISION:
                x = ScanPhysCheck("search", PHYSCHECK_VISION);
                if (Search(&list, &x, PhysCheckVisionCmp) != NULL)
                    PrintLnCurrent(&list);
                else
                    puts("The vision does not exist.");
                break;
            case SRCH_HEIGHT:
                x = ScanPhysCheck("search", PHYSCHECK_HEIGHT);
                if (Search(&list, &x, PhysCheckHeightCmp) != NULL)
                    PrintLnCurrent(&list);
                else
                    puts("The height does not exist");
                break;
            case SRCH_NAME:
                x = ScanPhysCheck("search", PHYSCHECK_NAME);
                if (Search(&list, &x, PhysCheckNameCmp) != NULL)
                    PrintLnCurrent(&list);
                else
                    puts("The name does not exist");
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
