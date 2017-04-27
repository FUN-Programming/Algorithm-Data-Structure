#include <stdio.h>

#define VMAX 21

typedef struct {
    double vision;
    int height;
} Body;

typedef struct {
    Body body;
    char name[20];
} PhysCheck;

double ave_height(PhysCheck *dat) {
    int n = 0;
    double sum = 0.0;
    while (dat->body.height > 0) {
        sum += (dat++)->body.height;
        n++;
    }
    return sum / n;
}

void dist_vision(PhysCheck *dat, int dist[]) {
    int vision;
    while ((vision = (int) (10 * ((dat++)->body.vision) + 0.5)) >= 0) {
        if (vision < VMAX)
            ++*(dist + vision);
        // -------------------- ①
    }
}

int main(void) {
    PhysCheck *y, x[] = {
            {{0.3, 162}, "AKASAKA Tadao"},
            {{0.7, 173}, "KATOH Tomiaki"},
            {{2.0, 175}, "SAITOH Syouji"},
            {{1.5, 171}, "TAKEDA Shinya"},
            {{0.4, 168}, "NAGAHAMA Masaki"},
            {{1.2, 174}, "HAMADA Tetsuaki"},
            {{1.0, 181}, "NAKASHIMA hideyuki"},
            {{0.8, 169}, "MATSUTOMI Akio"},
            {{-0.5, -1}, ""}
    };
    int *z, vdist[VMAX] = {};

    puts("■□■ 身体検査一覧表 ■□■");
    puts(" 氏名 身長 視力 ");
    puts("----------------------------");

    for (y = x; y->body.height > 0; y++)
        printf("%-18.18s%4d%5.1f\n", y->name, y->body.height, y->body.vision);
    printf("\n平均身長：%5.1f\n", ave_height(x));
    dist_vision(x, vdist);
    // ------------------- ②

    printf("\n視力の分布\n");
    for (z = vdist; z < vdist + VMAX; z++)
        if (*z > 0) printf("%3.1f〜：%2d人\n", (z - vdist) / 10.0, *z);

    return 0;
}