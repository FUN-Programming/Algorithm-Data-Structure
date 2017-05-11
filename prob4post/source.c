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
            // TODO: ------------------ ①
            if (pp == pat) return pt;
            pp--;
            pt--;
        }
        pt += (skip[*pt] > strlen(pp)) ? (size_t) skip[*pt] : strlen(pp);
    }
    return NULL;
}

int main(void) {
    char *s;
    char s1[80];
    char s2[80];

    printf("テキスト：");
    scanf("%s", s1);
    printf("パターン：");
    scanf("%s", s2);

    s = bm_match(s2, s1);
    // TODO: ------------------ ②

    if (s == NULL)
        puts("テキスト中にパターンは存在しません。");
    else
        printf("%d文字目に見つかりました。\n", (int) (s - s1 + 1));
    return 0;
}