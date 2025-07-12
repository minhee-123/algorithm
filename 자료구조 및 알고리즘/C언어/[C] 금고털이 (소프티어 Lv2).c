// 문제: https://softeer.ai/practice/6288
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stone
{
    int M;
    int P;
};

int comp(const void* a, const void* b)
{
    struct stone A = *(struct stone*)a;
    struct stone B = *(struct stone*)b;

    if (A.P > B.P) return -1; //음수는 자리변경 없음
    else if (A.P < B.P) return 1; //양수는 자리변경

    if (A.M > B.M) return -1;
    else if (A.M < B.M) return 1;

    return 0;
} //내림차순 정렬

int main(void)
{
    int W, N; scanf("%d %d", &W, &N);

    struct stone gold[1000001];
    for (int i = 0; i < N; i++) scanf("%d %d", &gold[i].M, &gold[i].P);
    qsort(gold, N, sizeof(struct stone), comp);

    long long money = 0; //오버플로우 주의
    int bag = 0;
    int index = 0;
    while (1)
    {
        if (gold[index].M >= W - bag) { //여기서는 W-bag 값으로 무게를 업데이트해야하므로 bag 값 업데이트 안함 (어차피 break)
            money += (W - bag) * gold[index].P;
            break;
        }
        else if (gold[index].M < W - bag) {
            bag += gold[index].M;
            money += gold[index].M * gold[index].P;
            index++;
        }
    }

    printf("%d", money);
    return 0;
}