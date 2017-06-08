# 第7回講義中課題

ソースコード：[source.c](./source.c)

### 1)

プログラムを動作させ、キューに *47* *42* *35* *11* *24* の順で値をエンキューした後、下線部①の部分で入力待ちとなった場合に、次の問いに答える。

- (ア) キューから連続して何回デキューできるか
- (イ) キューから連続して何回エンキューできるか
- (ウ) `que.max` `que.front` `que.rear` `que.que[0]` の値を書く

### 2)

[授業中練習問題6](../prob6) のプログラムで、スタックに保存するデータは文字列にしたのを参考に、このプログラムのキューに保存するデータを文字列に変更する。ただし、[授業中練習問題6](../prob6) のプログラムで文字列のスタック *StringsStack* 型を定義したように、このプログラムでも文字列のキューとして *StringsQueue* 型を定義して利用する。なお、キューに保存できる文字列は、動的な文字列として実現する。この時 *main* で入力できる文字列の長さは **81** 文字以内とする。答えは、変更したプログラムの *StringsQueue* 型の定義と *Enque* 関数と *Deque* 関数を答える。

## 提出

```
1)
(ア) 5回
(イ) 1回
(ウ) que.max: 6, que.front: 0, que.rear: 5, que.que[0]: 47

2)

typedef struct {
    int max;
    int num;
    int front;
    int rear;
    char **que;
} StringsQueue;

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
```