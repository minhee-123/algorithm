// 문제: https://softeer.ai/practice/7374
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)

int money = 100;
int map[3][3];

int comp(const void* a, const void* b)
{
    int A = *(int*)a;
    int B = *(int*)b;

    if (A > B) return 1;
    else if (A < B) return -1;
    else return 0;
}

void cal_row(int index)
{
    int arr[3];
    arr[0] = abs(map[index][0] - map[index][1]);
    arr[1] = abs(map[index][1] - map[index][2]);
    arr[2] = abs(map[index][2] - map[index][0]);
    qsort(arr, 3, sizeof(int), comp);

    if (arr[0] + arr[1] < money) money = arr[0] + arr[1];
} //논리가 조금 헷갈리는데, 비교값 중 작은거 두개를 더한게 최소 이동

void cal_col(int index)
{
    int arr[3];
    arr[0] = abs(map[0][index] - map[1][index]);
    arr[1] = abs(map[1][index] - map[2][index]);
    arr[2] = abs(map[2][index] - map[0][index]);
    qsort(arr, 3, sizeof(int), comp);

    if (arr[0] + arr[1] < money) money = arr[0] + arr[1];
}

int main(void)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) scanf("%d", &map[i][j]);
    }
    //경우의 수가 6 밖에 안되므로 브루트포스 수행

    for (int i = 0; i < 3; i++) {
        cal_row(i);
        cal_col(i);
    }

    printf("%d", money);
    return 0;
}