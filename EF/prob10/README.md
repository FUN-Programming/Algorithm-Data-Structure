# 授業中練習問題10

ソースコード：[source.c](./source.c)

![](./assets/prob10.jpg)

## 提出

```
(ア) abacabdabaceabacabdf
(イ) abacabdabaceabacabdf
⓪ recur2(\0) : none
① recur2(a) : a
② recur2(ba) : ① ⓪ b : ab
③ recur2(cba) : ② ① c : abac
④ recur2(dcba) : ③ ② d : abacabd
⑤ recur2(edcba) : ④ ③ e : abacabdabace
⑥ recur2(fedcba) : ⑤ ④ f : abacabdabaceabacabdf
```