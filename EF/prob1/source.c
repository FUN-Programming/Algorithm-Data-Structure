#include <stdio.h>

int main() {
    int a, b, c;
    int max;

    printf("Value of a:"); scanf("%d", &a);
    printf("Value of b:"); scanf("%d", &b);
    printf("Value of c:"); scanf("%d", &c);

    max = a;

    if (b > max) max = b;
    if (c > max) max = c;

    printf("Maximum : %d\n", max);

    return 0;
}