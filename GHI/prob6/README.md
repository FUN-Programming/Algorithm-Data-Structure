# 授業中練習問題6

ソースコード：[source.c](./source.c)

![](./assets/prob6.png)

## 提出

```
1)
0よりも小さい値が渡されたのでメモリを確保するcalloc関数がうまく動作しなかったのが原因

2)
(ア) ポップ関数でポップを試みるが s.ptr が0以下なので -1 が返され、「エラー: ポップに失敗しました」と表示される
(イ) プッシュ関数でプッシュを試みるが s.max = 0 で s.ptr = 0 なので、s.ptr が s.max 以上であるという判定になり -1 が返され、「エラー: プッシュに失敗しました」と表示される

3)
(ア) 6回
(イ) 4回

4)
int Search(StringsStack *s, char *x) {
    int i;

    for (i = s->ptr - 1; i >= 0; i--) {
        if (strstr(s->stk[i], x) != NULL)
            return i;
    }

    return -1;
}
```