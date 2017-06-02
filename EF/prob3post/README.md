## 第3回講義中課題

ソースコード：[source.c](./source.c)

第3回講義資料の理解度確認練習問題のプログラムで、身体検査データを定義する構造体 PhysCheck の型を以下のように変更して、元のプログラムと同じ働きをするように、プログラムを変更してください。

```
/*--- 身体データ型 ---*/
typedef struct{
    double vision; /* 視力 */
    int height; /* 身長 */
} Body;
/*--- 身体検査データ型 ---*/
typedef struct{
    Body body; /* 身体データ型 ---*/
    char name[20]; /* 氏名 */
} PhysCheck;
```

## 提出

- [kadai3.c](./kadai3.c)