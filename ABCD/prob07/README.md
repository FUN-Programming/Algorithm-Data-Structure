# prob07

ソースコード：[source.c](./source.c)

### 1)

キューに *47* *42* *11* *24* の順で値をエンキューしたあと、下線部①の部分で入力待ちとなった。

- (ア) この状態から、連続して何回デキューできるか
- (イ) この状態から、連続して何回エンキューできるか
- (ウ) この状態から、`que.max` `que.front` `que.rear` `que.que[0]` の値は何か

### 2)

スタックに保存するデータが文字列となっている [授業中練習問題6](../prob06) のプログラムを元に、このプログラムのキューに保存するデータを文字列に変更する。ただし [授業中練習問題6](../prob06) のプログラムで文字列スタックとして *StringsStack* 型を定義したように、このプログラムでも文字列キューとして *StringsQueue* 型を定義して利用する。また、キューに保存できる文字列は、動的な文字配列で実現する。ただし *main* で入力できる文字列の長さは *81* 文字以内とする。答えは、変更したプログラム中の *StringsQueue* 型の定義 *Enque* 関数 *Deque* 関数を答える。

## 答え

```
1)
(ア) 4回
(イ) 6回
(ウ) que.max: 10, que.front: 0, que.rear: 4, que.que[0]: 47

2)

typedef struct {
    int max;
    int num;
    int front;
    int rear;
    char **que;
} StringsQueue;

int Enque(StringsQueue *q, char *x) {
    int i;

    if (q->num >= q->max)
        return -1;
    else {
        q->num++;
        q->que[q->rear] = calloc(81, sizeof(char));

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