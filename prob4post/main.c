#include <stdio.h>
#include <string.h>
#include <limits.h>

char *bm_match(char *pat, char *txt) {
    char *pt;
    char *pp;
    int txt_len = (int) strlen(txt);
    int pat_len = (int) strlen(pat);
    int skip[UCHAR_MAX + 1];
    int i;

    for (i = 0; i <= UCHAR_MAX; i++)
        skip[i] = pat_len;
    for (pp = pat; *pp != '\0'; pp++)
        skip[*pp] = (int) (strlen(pp) - 1);
    skip[*(pp - 1)] = pat_len;

    pt = txt + pat_len - 1;
    while (pt < txt + txt_len) {
        pp = pat + pat_len - 1;
        while (*pt == *pp) {
            if (pp == pat) return pt;
            pp--;
            pt--;
        }
        pt += (skip[*pt] > strlen(pp)) ? (size_t) skip[*pt] : strlen(pp);
    }
    return NULL;
}

int bm_count(char *pat, char *txt) {
    char *s = txt;
    int counter = 0;

    do {
        s = bm_match(pat, s);
        if (s != NULL) {
            counter++;
            s++;
        }
    } while (s != NULL);

    return counter;
}

int main(void) {
    int count = 0;
    char s1[80];
    char s2[80];

    printf("テキスト：");
    scanf("%s", s1);
    printf("パターン：");
    scanf("%s", s2);

    count = bm_count(s2, s1);

    if (count == 0)
        puts("テキスト中にパターンは存在しません。");
    else
        printf("パターンは%d個見つかりました。\n", count);
    return 0;
}