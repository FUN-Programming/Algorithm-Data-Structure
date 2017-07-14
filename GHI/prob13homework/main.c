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

typedef struct __bnode {
    PhysCheck data;
    struct __bnode *left;
    struct __bnode *right;
} BinNode;

int PhysCheckVisionCmp(const PhysCheck *x, const PhysCheck *y) {
    return x->body.vision < y->body.vision ? -1 : x->body.vision > y->body.vision ? 1 : 0;
}

int PhysCheckHeightCmp(const PhysCheck *x, const PhysCheck *y) {
    return x->body.height < y->body.height ? -1 : x->body.height > y->body.height ? 1 : 0;
}

int PhysCheckNameCmp(const PhysCheck *x, const PhysCheck *y) {
    return strcmp(x->name, y->name);
}

void PrintLnPhysCheck(const PhysCheck *x) {
    printf("%0.2lf %d %s\n", x->body.vision, x->body.height, x->name);
}

PhysCheck ScanPhysCheck(const char *message, int sw) {
    PhysCheck temp;
    printf("Please input data to %s.\n", message);

    if (sw & PHYSCHECK_VISION) {
        printf("Vision: ");
        scanf("%lf", &temp.body.vision);
    }

    if (sw & PHYSCHECK_HEIGHT) {
        printf("Height: ");
        scanf("%d", &temp.body.height);
    }

    if (sw & PHYSCHECK_NAME) {
        temp.name = calloc(82, sizeof(char));
        printf("Name: ");
        scanf("%s", temp.name);
    }

    return temp;
}

static BinNode *AllocBinNode(void) {
    return calloc(1, sizeof(BinNode));
}

static void SetBinNode(BinNode *n, const PhysCheck *x,
                       const BinNode *left, const BinNode *right) {
    n->data = *x;
    n->left = (BinNode *) left;
    n->right = (BinNode *) right;
}

BinNode *Search(BinNode *p, const PhysCheck *x,
                int compare(const PhysCheck *y, const PhysCheck *z)) {
    int cond;
    if (p == NULL)
        return NULL;
    else if ((cond = compare(x, &p->data)) == 0)
        return p;
    else if (cond < 0)
        return Search(p->left, x, compare);
    else
        return Search(p->right, x, compare);
}

BinNode *Add(BinNode *p, const PhysCheck *x,
             int compare(const PhysCheck *y, const PhysCheck *z)) {
    int cond;
    if (p == NULL) {
        p = AllocBinNode();
        SetBinNode(p, x, NULL, NULL);
    } else if ((cond = compare(x, &p->data)) == 0)
        printf("[ERROR] %s already exists.\n", x->name);
    else if (cond < 0)
        p->left = Add(p->left, x, compare);
    else
        p->right = Add(p->right, x, compare);
    return p;
}

int Remove(BinNode **root, const PhysCheck *x,
           int compare(const PhysCheck *y, const PhysCheck *z)) {
    BinNode *next, *temp;
    BinNode **left;
    BinNode **p = root;
    while (1) {
        int cond;
        if (*p == NULL) {
            printf("[ERROR] %s does not exists.\n", x->name);
            return -1;
        } else if ((cond = compare(x, &(*p)->data)) == 0)
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
    free(temp->data.name);
    free(temp);

    return 0;
}

void PrintTree(const BinNode *p) {
    if (p != NULL) {
        PrintTree(p->left);
        PrintLnPhysCheck(&p->data);
        PrintTree(p->right);
    }
}

void FreeTree(BinNode *p) {
    if (p != NULL) {
        FreeTree(p->left);
        FreeTree(p->right);
        free(p->data.name);
        free(p);
    }
}

typedef enum {
    TERMINATE, ADD, REMOVE, SEARCH, PRINT_ALL
} Menu;

Menu SelectMenu(void) {
    int i, ch;
    char *mstring[] = {
            "Insert", "Remove", "Search", "Print"
    };

    do {
        for (i = TERMINATE; i < PRINT_ALL; i++) {
            printf("(%2d) %-18.18s ", i + 1, mstring[i]);
            if ((i % 3) == 2)
                putchar('\n');
        }
        printf("( 0) End ：");
        scanf("%d", &ch);
    } while (ch < TERMINATE || ch > PRINT_ALL);

    return (Menu) ch;
}

int main(void) {
    int sw;
    Menu menu;
    BinNode *root = NULL;

    do {
        printf("Please input number.\n");
        printf("(%d) Vision Tree (%d) Height Tree (%d) Name Tree : ",
               PHYSCHECK_VISION, PHYSCHECK_HEIGHT, PHYSCHECK_NAME);
        scanf("%d", &sw);
        putchar('\n');
    } while (sw != PHYSCHECK_VISION && sw != PHYSCHECK_HEIGHT && sw != PHYSCHECK_NAME);

    do {
        PhysCheck x;
        BinNode *temp;

        switch (menu = SelectMenu()) {
            case ADD :
                x = ScanPhysCheck("insert", PHYSCHECK_VISION | PHYSCHECK_HEIGHT | PHYSCHECK_NAME);
                root = Add(root, &x, sw == PHYSCHECK_VISION ? PhysCheckVisionCmp :
                                     sw == PHYSCHECK_HEIGHT ? PhysCheckHeightCmp : PhysCheckNameCmp);
                break;
            case REMOVE :
                x = ScanPhysCheck("remove", PHYSCHECK_NAME);
                Remove(&root, &x, sw == PHYSCHECK_VISION ? PhysCheckVisionCmp :
                                  sw == PHYSCHECK_HEIGHT ? PhysCheckHeightCmp : PhysCheckNameCmp);
                break;
            case SEARCH :
                x = ScanPhysCheck("search", PHYSCHECK_NAME);
                if ((temp = Search(root, &x, sw == PHYSCHECK_VISION ? PhysCheckVisionCmp :
                                             sw == PHYSCHECK_HEIGHT ? PhysCheckHeightCmp :
                                             PhysCheckNameCmp)) != NULL)
                    PrintLnPhysCheck(&temp->data);
                break;
            case PRINT_ALL :
                puts("--- List ---");
                PrintTree(root);
                break;
        }
    } while (menu != TERMINATE);

    FreeTree(root);

    return 0;
}
