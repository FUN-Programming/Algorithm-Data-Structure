#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int max;
    int num;
    int front;
    int rear;
    int *que;
} IntQueue;

int Initialize(IntQueue *q, int max) {
    q->num = q->front = q->rear = 0;
    if ((q->que == calloc(max, sizeof(int))) == NULL) {
        q->max = 0;
        return -1;
    }
    q->max = max;
    return 0;
}

void Terminate(IntQueue *q) {
    if (q->que != NULL) {
        free(q->que);
        q->max = q->num = q->front = q->rear = 0;
    }
}

int Enquq(IntQueue *q, int x) {
    if (q->num >= q->max)
        return -1;
    else {
        q->num++;
        q->que[q->rear++] = x;
        if (q->rear == q->max) q->rear = 0;
        return 0;
    }
}

int Deque(IntQueue *q, int *x) {
    if (q->num <= 0)
        return -1;
    else {
        q->num--;
        *x = q->que[q->front++];
        if (q->front == q->max) q->front = 0;
        return 0;
    }
}

int Peek(const IntQueue *q, int *x) {
    if (q->num <= 0)
        return -1;
    *x = q->que[q->front];
    return 0;
}

int Capacity(const IntQueue *q) {
    return q->max;
}

int Size(const IntQueue *q) {
    return q->num;
}

void Print(const IntQueue *q) {
    int i;

    for (i = 0; i < q->num; i++)
        printf("%d ", q->que[(i + q->front) % q->max]);
    putchar('\n');
}

int main(void) {
    IntQueue que;

    if (Initialize(&que, 6) == -1) {
        puts("キューの生成に失敗しました。");
        return 1;
    }

    while (1) {
        int m, x;

        printf("現在のデータ数：%d/%d\n", Size(&que), Capacity(&que));
        printf("(1)エンキュー (2)デキュー (3)ピーク (4)表示 (0)終了：");
        scanf("%d", &m);
        // --------------①

        if (m == 0) break;

        switch (m) {
            case 1:
                printf("データ：");
                scanf("%d", &x);
                if (Enquq(&que, x) == -1)
                    puts("\aエラー：データのエンキューに失敗しました。");
                break;
            case 2:
                if (Deque(&que, &x) == -1)
                    puts("\aエラー：デキューに失敗しました。");
                else
                    printf("デキューしたデータは%dです。\n", x);
                break;
            case 3:
                if (Peek(&que, &x) == -1)
                    puts("\aエラー：ピークに失敗しました。");
                else
                    printf("ピークしたデータは%dです。\n", x);
                break;
            case 4:
                Print(&que);
                break;
        }
    }
    Terminate(&que);
    return 0;
}