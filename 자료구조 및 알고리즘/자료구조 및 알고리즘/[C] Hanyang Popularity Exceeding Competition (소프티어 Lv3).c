// 문제: https://softeer.ai/practice/9495
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 유명인과 만남 순서를 바꿀 수 없고 (원하는대로 만날 수 없음)
// 인기도가 오를 수 없는 유명인을 만난다고 해도 → 인기도가 하락하지는 않으므로
// 시간 복잡도 조건에도 문제가 없으니까 그냥 모든 유명인을 만나서 계산하면 됨
int main(void)
{
    int N; scanf("%d", &N);
    int popu = 0;

    int P, C;
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &P, &C);
        if (abs(P - popu) <= C) popu++; //문제오류 (|P - X| <= C로 해야 정상적으로 계산이 됨)
    }

    printf("%d", popu);
    return 0;
}