# 授業中練習問題5

ソースコード：[source.c](./source.c)

![](./assets/prob5.png)

## 提出

```
1)
(ア) Pop
(イ) -1
(ウ) 0

2)
(ア) s.ptr: 7, s.stk[4]: 83
(イ) 47
(ウ) 47

3)
typedef struct {
    int max;
    int ptr;
    PhysCheck stk[MAX];
} PhysCheckStack;

int Push(PhysCheckStack *s, PhysCheck x) {
    if (s->ptr >= s->max) return -1;
    s->stk[s->ptr] = x;
    s->ptr++;
    return 0;
}

int Pop(PhysCheckStack *s, PhysCheck *x) {
    if (s->ptr <= 0) return -1;
    s->ptr--;
    *x = s->stk[s->ptr];
    return 0;
}
```