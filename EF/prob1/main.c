#include <stdio.h>

int main() {
    int a, b, c, d;
    int min;

    puts("bXXXXXXX hogehoge piyo");

    printf("Value of a:"); scanf("%d", &a);
    printf("Value of b:"); scanf("%d", &b);
    printf("Value of c:"); scanf("%d", &c);
    printf("Value of d:"); scanf("%d", &d);

    min = a;

    if (b < min) min = b;
    if (c < min) min = c;
    if (d < min) min = d;

    printf("Minimum : %d\n", min);

    return 0;
}