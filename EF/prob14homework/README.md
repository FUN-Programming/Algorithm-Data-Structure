# 練習問題 14 (宿題)

画像や動画などデータ容量が大きいものの配列をソートする場合は、配列の要素を移動されるとデータの移動に多くの時間が必要なので非効率である。しかし、実際のデータが保存された配列の要素を移動させるのでなく、配列の添字を管理する配列をソートすれば、データを移動する必要がなくなる。そこで、[授業中練習問題14](../prob14) のプログラムを以下の指示に従って変更し、データを移動させることなく、配列の添字を管理してヒープソートすることを実現する。

- `main()` の関数を以下のように変更し、配列 `data[]` のデータを移動させることなく、ヒープソートが正しく動作するようにプログラムを変更する。

```
int main(void) {
    Menu menu;
    Member data[] = {
            {1, "takahashi"},
            {3, "konishi"},
            {5, "ueda"},
            {7, "sato"},
            {9, "niimi"},
            {8, "okonishi"},
            {2, "motoike"},
            {4, "agemi"}
    };
    int ndata = sizeof(data) / sizeof(data[0]);
    int i, *sortindex = calloc(ndata, sizeof(int));

    for (i = 0; i < ndata; i ++) sortindex[i] = i;

    do {
        switch (menu = SelectMenu()) {
            case ASCEND_NO:
                Heapsort(data, sortindex, ndata, AscendingMemberNoCmp);
                break;
            case ASCEND_NAME:
                Heapsort(data, sortindex, ndata, AscendingMemberNameCmp);
                break;
            case DESCEND_NO:
                Heapsort(data, sortindex, ndata, DescendingMemberNoCmp);
                break;
            case DESCEND_NAME:
                Heapsort(data, sortindex, ndata, DescendingMemberNameCmp);
                break;
            case PRINT_ALL:
                Print(data, sortindex, ndata);
                break;
        }
    } while (menu != TERMINATE);

    return 0;
}
```

## 提出

- [kadai14.c](./kadai14.c)