## 第4回講義資料の理解度確認

ソースコード：[source.c](./source.c)

### 問1)

キーボードからテキストとして「AACAGACAGG」を、パターンとして「AGG」を入力したとき、次の問いに答えなさい。

#### (ア)

スキップテーブルを表す配列の `skip['G]` と `skip['A]` の値はいくらですか。

#### (イ)

下線部②の関数 `bm_match(s2, s1)` の戻り値のポインタが指している文字は、テキスト「AACAGACAGG」のどの文字ですか。

### 問2)

キーボードからテキストとして「APCPAACBABEAAA」を、パターンとして「AAA」を入力したとき、下線部①の `while` の条件式 `(*pt == *pp)` は何度評価されますか。

### 問3)

Boyer-Moore 法のアルゴリズムを変更して、指定したパターンをテキストの末尾から先頭に向かって探索する関数 `char *bm_reverse_text_match(char *pat, char *txt)` を作成してください。すなわち、 `bm_reverse_text_match` では、txt がさす文字列の末尾から先頭に向かって逆順で並んでいるものをテキストとして、`pat` が指す文字列のパターンを探索するものとします。但し、関数 `bm_reverse_text_match` の引数も戻り値も、関数 `bm_match` と同じとします。例えば、`txt` が指す文字列が "ABCDEF" の場合、`pat` が指す文字列が "ABC" なら「テキスト中にパターンは存在しません。」となるが、`pat` が指す文字列が "CBA" なら「4文字目に見つかりました。」となるようにしてください。

## 提出

```
1)
    (ア) skip['G']: 3, skip['A']: 2
    (イ) A
2) 12回
3)
```

```
char *bm_reverse_text_match(char *pat, char *txt) {
    char *pt;
    char *pp;
    int txt_len = strlen(txt);
    int pat_len = strlen(pat);
    int skip[UCHAR_MAX + 1];
    int i;
    char s[txt_len + 1];

    for (pp = pat, i = 1; *pp != '\0'; pp++, i++) {
        s[pat_len - i] = *pp;
    }
    s[pat_len] = '\0';

    for (i = 0; i <= UCHAR_MAX; i++) {
        skip[i] = pat_len;
    }

    for (pp = s; *pp != '\0'; pp++) {
        skip[*pp] = strlen(pp) - 1;
    }

    skip[*(pp - 1)] = pat_len;
    pt = txt + pat_len - 1;

    while (pt < txt + txt_len) {
        pp = s + pat_len - 1;

        while (*pt == *pp) {
            if (pp == s) return pt;
            pp--;
            pt--;
        }

        pt += (skip[*pt] > strlen(pp)) ? skip[*pt] : strlen(pp);
    }

    return NULL;
}
```