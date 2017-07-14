# 練習問題13(宿題)

[授業中練習問題13](../prob13) のプログラムを以下の指示に従って変更する。

(1) 2分探索木のデータを以下の構造体 *PhysCheck* となるようにプログラムを変更する。具体的には以下の条件を満たす。

- (ア) `__bnode` の *data* 型を、以下の *PhysCheck* のように、氏名の文字列(`name`)は動的な文字列配列で実現する。

```
typedef struct {
    double vision;
    int height;
} Body;

typedef struct {
    char *name;
    Body body;
} PhysCheck;
```

- (イ) プログラム中の `MEMBER_NO` と `MEMBER_NAME` の代わりに以下のものを用いる

```
#define PHYSCHECK_VISION 1
#define PHYSCHECK_HEIGHT 2
#define PHYSCHECK_NAME 4
```

- (ウ) プログラムの動作直後に整数の *1* を入力すると視力で木を作成し、整数の *2* を入力すると身長で木を作成し、整数の *4* を入力すると名前で木を作成できるようにする

- (エ) ノードを挿入する場合に、キーボードから読み込むデータは三種類(身長・視力・氏名)とする。ただし、氏名として利用できる文字は **81** 文字以内の英文字のみとし、空白や日本語などは利用しないものとする。

- (オ) 表示するデータも三種類(身長・視力・氏名)とする

## 提出

- [kadai13.c](./kadai13.c)