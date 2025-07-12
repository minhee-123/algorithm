// 문제: https://softeer.ai/practice/7628
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N;
int number[101];
int visit[101];

void Divide(int num)
{
    for (int i = num; i > 1; i--) {
        if (num % i == 0) visit[i] = 1;
    } //약수 기록
}

int main(void)
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &number[i]);
        Divide(number[i]);
    }

    int max_house = 0;
    for (int i = 1; i <= 100; i++) {
        if (visit[i] == 0) continue; //약수가 아닌 경우 pass

        int cnt = 0;
        for (int k = 0; k < N; k++) {
            if (number[k] % i == 0) cnt++;
        }

        if (cnt > max_house) max_house = cnt; //가장 많이 나눠진 값을 저장
    }

    printf("%d", max_house);
    return 0;
}