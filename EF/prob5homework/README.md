# 練習問題5(宿題)

[授業中練習問題5](../prob5) のプログラムを以下の指示に従った変更したもの作る。

### 1)

[授業中練習問題5](../prob5) の 3) で変更したプログラムに、以下の引数と戻り値を取る関数 Count を追加して、パターン文字列を入力するとスタック上に積まれている身体検査データの名前を全て探索し、見つけたパターンの全個数を表示するようにする。

```c
int Count(PhysCheckStack *s, PhysCheck +x)
```

ただし、関数 Count では、パターン文字列(`x->name`)で指定された文字列を、スタック s 上に積まれている全ての身体検査データの名前から探索し、見つけたパターンの戸数を関数の戻り値として返す。ただし、パターンが見つからなかった場合は、0を返す。

### 2)

main 関数では「(1)プッシュ (2)ポップ (3)ピーク (4)表示 (5)計算 (0)終了：」と表示され、数字の 5 を入力すると、パターンの文字列を `x.name` に読み込み、戻り値が int 型の `Count(&s, &x)` 関数を呼ぶようにします。さらに、`Count(&s, &x)` の戻り値の値が 0 の場合は、`"パターンが存在しません."` と表示し、`Count(&s, &x)` の戻り値の値が 1 以上の場合は、見つけたパターンの個数を表示するようにする。

## 提出

- [kadai5.c](./kadai5.c)