#include <stdio.h>

#define VMAX 21

typedef struct {
    char name[20];
    int height;
    double vision;
} PhysCheck;

double ave_height(PhysCheck *dat) {
    int n = 0;
    double sum = 0.0;
    while (dat->height > 0) {
        sum += (dat++)->height;
        n++;
    }
    return sum / n;
}

void dist_vision(PhysCheck *dat, int dist[]) {
    int vision;
    while ((vision = (int) (10 * ((dat++)->vision) + 0.5)) >= 0) {
        if (vision < VMAX)
            ++*(dist + vision);
        // -------------------- ①
    }
}

int main(void) {
    PhysCheck *y, x[] = {
            {"AKASAKA Tadao", 162, 0.3},
            {"KATOH Tomiaki", 173, 0.7},
            {"SAITOH Syouji", 175, 2.0},
            {"TAKEDA Shinya", 171, 1.5},
            {"NAGAHAMA Masaki", 168, 0.4},
            {"HAMADA Tetsuaki", 174, 1.2},
            {"NAKASHIMA hideyuki", 181, 1.0},
            {"MATSUTOMI Akio", 169, 0.8},
            {"", -1, -0.5}
    };
    int *z, vdist[VMAX] = {};

    puts("■□■ 身体検査一覧表 ■□■");
    puts(" 氏名 身長 視力 ");
    puts("----------------------------");

    for (y = x; y->height > 0; y++)
        printf("%-18.18s%4d%5.1f\n", y->name, y->height, y->vision);
    printf("\n平均身長：%5.1f\n", ave_height(x));
    dist_vision(x, vdist);
    // ------------------- ②

    printf("\n視力の分布\n");
    for (z = vdist; z < vdist + VMAX; z++)
        if (*z > 0) printf("%3.1f〜：%2d人\n", (z - vdist) / 10.0, *z);

    return 0;
}