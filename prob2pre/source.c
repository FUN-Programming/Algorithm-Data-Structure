#include <stdio.h>

void ary_reverse(int *a, int n) {
    int *b, t;

    for (b = a + n - 1; a < b; a++, b--) {
        t = *a;
        *a = *b;
        *b = t;
    }
}

int main(void) {
    int i;
    int x[7];
    int nx = sizeof(x) / sizeof(x[0]);

    printf("%d 個の整数を入力してください。\n", nx);

    for (i = 0; i < nx; i++) {
        printf("x[%d] : ", i);
        scanf("%d", &x[i]);
    }

    ary_reverse(x, nx);
    printf("配列の要素の並びを逆転しました。\n");

    for (i = 0; i < nx; i++) {
        printf("x[%d] : %d\n", i, x[i]);
    }

    return 0;
}