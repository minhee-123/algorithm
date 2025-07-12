// 문제: https://softeer.ai/practice/9497
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

// 문제를 해석하면 가로 혹은 세로줄은 언제든지 같은 구역으로 성립된다
int main(void)
{
    int N; scanf("%d", &N);

    int trash;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) scanf("%d", &trash);
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) printf("%d ", i);
        printf("\n");
    }

    return 0;
}