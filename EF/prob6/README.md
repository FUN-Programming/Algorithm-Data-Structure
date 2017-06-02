# 第6回講義中課題

ソースコード：[source.c](./source.c)

### 1)

プログラムの動作直後に **-1** を入力すると「スタックの生成に失敗しました。」とメッセージが表示され、プログラムが終了した。そのようになった原因を説明する。

### 2)

プログラムの動作直後に **0** を入力すると、プログラムは終了せず動作し、下線部①の部分で入力待ちになる。このとき、以下の問いに答える。

- (ア) ポップを指示した場合、どのようなことが起こるか説明する
- (イ) スタックに文字列 `Maki` をプッシュした場合、どのようなことが起こるか説明する

### 3)

プログラムの動作直後に **10** を入力し、文字列 `Ant` `Deck` `Eagle` `Ferret` `Gar` `Hare` `Pika` の順に **7** 回プッシュした。このとき、以下の問いに答える。

- (ア) この状態で、スタックから文字列を連続していくつ取り出せるか
- (イ) この状態から、スタックに連続して文字列をいくつ積めるか

### 4)

このプログラムにパターンの文字列を入力すると、その入力したパータンがスタック上の文字列の中にないか探索する関数 *Search* を追加する。探索は、スタックの頂上からそこに向かって行う(後に入れたものから最初に入れたものへ向かって探索する)。そして、最初に見つかった文字列の入っているスタックのポインタの値を返す。また、関数 *Search* は以下のような動作をする。

`int Search(StringsStack *s, char *x)` は、スタックに積まれている文字列の中から、パターンの文字列( *x* の先頭からパターンが入っている)で指定された文字列を、スタックの頂上からそこに向かって探索し、最初に見つけたパターンを含む文字列のスタックポインタの値を戻り値として返すようにする。ただし、パターンが見つからなかった場合は **-1** を返すようにする。

## 提出

(1) 0よりも小さい値が渡されたのでメモリを確保するcalloc関数がうまく動作しなかったのが原因

(2)

- (ア) ポップ関数でポップを試みるが s.ptr が0以下なので -1 が返され、「エラー: ポップに失敗しました。」と表示される
- (イ) プッシュ関数でプッシュを試みるが s.max = 0 で s.ptr = 0 なので、s.ptr が s.max 以上であるという判定になり -1 が返され、「エラー: プッシュに失敗しました。」と表示される

(3)

- (ア) 7
- (イ) 3

(4)
```
int Search(StringsStack *s, char *x) {
    int i;

    for (i = s->ptr - 1; i > 0; i--) {
        if (strstr(s->stk[i], x) != NULL)
            return i;
    }

    return -1;
}
```