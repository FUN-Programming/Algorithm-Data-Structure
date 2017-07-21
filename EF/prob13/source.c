#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMBER_NO 1
#define MEMBER_NAME 2

typedef struct {
    int no;
    char name[20];
} Member;

typedef struct __bnode {
    Member data;
    struct __bnode *left;
    struct __bnode *right;
} BinNode;

int MemberNoCmp(const Member *x, const Member *y) {
    return x->no < y->no ? -1 : x->no > y->no ? 1 : 0;
}

int MemberNameCmp(const Member *x, const Member *y) {
    return strcmp(x->name, y->name);
}

void PrintLnMember(const Member *x) {
    printf("%d %s\n", x->no, x->name);
}

Member ScanMember(const char *message, int sw) {
    Member temp;

    printf("Please input data to %s.\n", message);

    if (sw & MEMBER_NO) {
        printf("No: ");
        scanf("%d", &temp.no);
    }

    if (sw & MEMBER_NAME) {
        printf("Name: ");
        scanf("%s", temp.name);
    }

    return temp;
}

static BinNode *AllocBinNode(void) {
    return calloc(1, sizeof(BinNode));
}

static void SetBinNode(BinNode *n, const Member *x,
                       const BinNode *left, const BinNode *right) {
    n->data = *x;
    n->left = (BinNode *) left;
    n->right = (BinNode *) right;
}

BinNode *Search(BinNode *p, const Member *x) {
    int cond;

    if (p == NULL)
        return NULL;
    else if ((cond = MemberNameCmp(x, &p->data)) == 0)
        return p;
    else if (cond < 0)
        return Search(p->left, x);
    else
        return Search(p->right, x);
}

BinNode *Add(BinNode *p, const Member *x) {
    int cond;

    if (p == NULL) {
        p = AllocBinNode();
        SetBinNode(p, x, NULL, NULL);
    } else if ((cond = MemberNameCmp(x, &p->data)) == 0)
        printf("[ERROR] %s already exists.\n", x->name);
    else if (cond < 0)
        p->left = Add(p->left, x);
    else
        p->right = Add(p->right, x);
    return p;
}

int Remove(BinNode **root, const Member *x) {
    BinNode *next, *temp;
    BinNode **left;
    BinNode **p = root;

    while (1) {
        int cond;
        if (*p == NULL) {
            printf("[ERROR] %s does not exists.\n", x->name);
            return -1;
        } else if ((cond = MemberNameCmp(x, &(*p)->data)) == 0)
            break;
        else if (cond < 0)
            p = &((*p)->left);
        else
            p = &((*p)->right);
    }
    if ((*p)->left == NULL)
        next = (*p)->right;
    else {
        left = &((*p)->left);
        while ((*left)->right != NULL)
            left = &(*left)->right;
        next = *left;
        *left = (*left)->left;
        next->left = (*p)->left;
        next->right = (*p)->right;
    }
    temp = *p;
    *p = next;
    free(temp);

    return 0;
}

void PrintTree(const BinNode *p) {
    if (p != NULL) {
        PrintTree(p->left);
        PrintLnMember(&p->data);
        PrintTree(p->right);
    }
}

void FreeTree(BinNode *p) {
    if (p != NULL) {
        FreeTree(p->left);
        FreeTree(p->right);
        free(p);
    }
}

typedef enum {
    TERMINATE, ADD, REMOVE, SEARCH, PRINT_ALL
} Menu;

Menu SelectMenu(void) {
    int i, ch;
    char *mstring[] = {"Insert", "Remove", "Search", "Print"};

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
    BinNode *root = NULL;

    do {
        Member x;
        BinNode *temp;

        switch (menu = SelectMenu()) {
            case ADD:
                x = ScanMember("insert", MEMBER_NO | MEMBER_NAME);
                root = Add(root, &x);
                break;
            case REMOVE:
                x = ScanMember("remove", MEMBER_NAME);
                break;
            case SEARCH:
                x = ScanMember("search", MEMBER_NAME);
                if ((temp = Search(root, &x)) != NULL)
                    PrintLnMember(&temp->data);
                break;
            case PRINT_ALL:
                puts("--- List ---");
                PrintTree(root);
                break;
        }
    } while (menu != TERMINATE);

    return 0;
}
