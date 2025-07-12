// 문제: https://softeer.ai/practice/6283
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int v[8];
    for (int i = 0; i < 8; i++) scanf("%d", &v[i]);

    if (v[0] == 1)
    {
        int flag1 = 0;
        for (int i = 1; i < 8; i++) {
            if (v[i] != v[i - 1] + 1) {
                flag1 = 1;
                break;
            }
        }

        if (flag1 == 1) printf("mixed");
        else printf("ascending");
    }
    else if (v[0] == 8)
    {
        int flag2 = 0;
        for (int i = 1; i < 8; i++) {
            if (v[i] != v[i - 1] - 1) {
                flag2 = 1;
                break;
            }
        }

        if (flag2 == 1) printf("mixed");
        else printf("descending");
    }
    else printf("mixed");

    return 0;
}