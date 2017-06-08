#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int max;
    int num;
    int front;
    int rear;
    char **que;
} StringsQueue;

int Initialize(StringsQueue *q, int max) {
    q->num = q->front = q->rear = 0;
    if ((q->que = calloc(max, sizeof(char *))) == NULL) {
        q->max = 0;
        return -1;
    }
    q->max = max;
    return 0;
}

void Terminate(StringsQueue *q) {
    int i;
    if (q->que != NULL) {
        for (i = 0; i < q->num; i++) {
            free(q->que[(i + q->front) % q->max]);
        }
        free(q->que);
        q->max = q->num = q->front = q->rear = 0;
    }
}

int Enquq(StringsQueue *q, char *x) {
    int i;

    if (q->num >= q->max)
        return -1;
    else {
        q->num++;
        q->que[q->rear] = calloc(81, sizeof(char));

        /* xの文字列をqueにコピー */
        for (i = 0; x[i] != '\0'; i++)
            q->que[q->rear][i] = x[i];

        q->rear++;

        if (q->rear == q->max) q->rear = 0;

        return 0;
    }
}

int Deque(StringsQueue *q, char *x) {
    int i;

    if (q->num <= 0)
        return -1;
    else {
        q->num--;

        /* queの文字列をxにコピー */
        for (i = 0; q->que[q->front][i] != '\0'; i++)
            x[i] = q->que[q->front][i];
        q->que[q->front][i + 1] = '\0';

        free(q->que[q->front]);
        q->front++;

        if (q->front == q->max) q->front = 0;

        return 0;
    }
}

int Peek(const StringsQueue *q, char *x) {
    int i;

    if (q->num <= 0)
        return -1;

    for (i = 0; q->que[q->front][i] != '\0'; i++)
        x[i] = q->que[q->front][i];
    q->que[q->front][i + 1] = '\0';

    return 0;
}

int Capacity(const StringsQueue *q) {
    return q->max;
}

int Size(const StringsQueue *q) {
    return q->num;
}

void Print(const StringsQueue *q) {
    int i;

    for (i = 0; i < q->num; i++)
        printf("%s ", q->que[(i + q->front) % q->max]);
    putchar('\n');
}

int main(void) {
    StringsQueue que;

    if (Initialize(&que, 6) == -1) {
        puts("キューの生成に失敗しました。");
        return 1;
    }

    while (1) {
        int m;
        char *x = calloc(81, sizeof(char));

        printf("現在のデータ数：%d/%d\n", Size(&que), Capacity(&que));
        printf("(1)エンキュー (2)デキュー (3)ピーク (4)表示 (0)終了：");
        scanf("%d", &m);
        // --------------①

        if (m == 0) break;

        switch (m) {
            case 1:
                printf("データ：");
                scanf("%s", x);
                if (Enquq(&que, x) == -1)
                    puts("\aエラー：データのエンキューに失敗しました。");
                break;
            case 2:
                if (Deque(&que, x) == -1)
                    puts("\aエラー：デキューに失敗しました。");
                else
                    printf("デキューしたデータは%sです。\n", x);
                break;
            case 3:
                if (Peek(&que, x) == -1)
                    puts("\aエラー：ピークに失敗しました。");
                else
                    printf("ピークしたデータは%sです。\n", x);
                break;
            case 4:
                Print(&que);
                break;
            default:
                break;
        }

        free(x);
    }
    Terminate(&que);
    return 0;
}