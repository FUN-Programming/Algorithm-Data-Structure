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
    int counter = 0;

    for (i = 0; i <= UCHAR_MAX; i++)
        skip[i] = pat_len;
    for (pp = pat; *pp != '\0'; pp++)
        skip[*pp] = (int) (strlen(pp) - 1);
    skip[*(pp - 1)] = pat_len;
    printf("skip['G']: %d, skip['A']: %d\n", skip['G'], skip['A']);

    pt = txt + pat_len - 1;
    while (pt < txt + txt_len) {
        pp = pat + pat_len - 1;
        while (++counter && *pt == *pp) {
            // TODO: ------------------ ①
            if (pp == pat) {
                printf("counter: %d\n", counter);
                return pt;
            }
            pp--;
            pt--;
        }
        pt += (skip[*pt] > strlen(pp)) ? (size_t) skip[*pt] : strlen(pp);
    }
    return NULL;
}

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

//char *bm_reverse_text_match(char *pat, char *txt) {
//    char *pt;
//    char *pp;
//    int txt_len = (int) strlen(txt);
//    int pat_len = (int) strlen(pat);
//    int skip[UCHAR_MAX + 1];
//    int i;
////    char s[txt_len + 1];
////
////    for (pt = txt, i = 1; *pt != '\0'; pt++, i++) {
////        s[txt_len - i] = *pt;
////    }
////
////    s[txt_len] = '\0';
////    printf("%s\n", s);
//
//    for (i = 0; i <= UCHAR_MAX; i++) {
//        skip[i] = pat_len;
//    }
//
//    for (pp = pat; *pp != '\0'; pp++) {
//        skip[*pp] = (int) (strlen(pp) - 1);
//    }
//
//    skip[*(pp - 1)] = pat_len;
//
//    pt = txt + pat_len - 1;
//
//    while (pt < txt + txt_len) {
//        pp = pat + pat_len - 1;
//        while (*pt == *pp) {
//            if (pp == pat) return pt;
//            pp--;
//            pt--;
//        }
//        pt += (skip[*pt] > strlen(pp)) ? (size_t) skip[*pt] : strlen(pp);
//    }
//    return NULL;
//}

int main(void) {
    char *s;
//    char s1[80] = "AACAGACAGG";
//    char s2[80] = "AGG";
//    char s1[80] = "APCPAACBABEAAA";
//    char s2[80] = "AAA";
    char s1[80] = "ABCDEF";
    char s2[80] = "CBA";

//    printf("テキスト：");
//    scanf("%s", s1);
//    printf("パターン：");
//    scanf("%s", s2);


//    s = bm_match(s2, s1);
    s = bm_reverse_text_match(s2, s1);
    // TODO: ------------------ ②

    if (s == NULL)
        puts("テキスト中にパターンは存在しません。");
    else {
        printf("%d文字目に見つかりました。\n", (int) (s - s1 + 1));
        printf("戻り値のポインタが指す文字：%s\n", s);
    }
    return 0;
}