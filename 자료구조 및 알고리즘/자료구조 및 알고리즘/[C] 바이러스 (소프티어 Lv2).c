// 문제: https://softeer.ai/practice/6284
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int K, P, N;
    scanf("%d %d %d", &K, &P, &N);
    // 단순 계산 구현 문제인데 범위가 너무 커서 처리할때 약간의 추가 연산이 필요함 (알고리즘 보다는 수학문제)

    long long virus = (long*)K;
    while (N) {
        virus = (virus * P) % 1000000007;
        N--;
    }

    printf("%lld", virus % 1000000007);
    return 0;
}