// 문제: https://softeer.ai/practice/11002/talk
#pragma warning(disable:4996)
// 브루트포스로 풀 수 있으나 시간복잡도 문제 발생
// 비트를 다루는 문제 (조금 생소한 문제, 특정 알고리즘까지는 아님)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 비트마스크 + XOR 연산 + 해시맵 (C언어에 해시맵 자료구조가 내제되어 있지는 않아서 필요한 기능을 직접 구현)
// 비트마스크: 비트 연산을 활용하여 여러 상태를 하나의 정수 값으로 표현하는 방법
// XOR 연산: 대응하는 두 비트가 서로 다르면 1을 반환 (0과0은 0, 1과1은 0, 1과0은 1)

#define MAX_M (1<<30) 
//비트마스크 최대 크기 (2^30) → 단 너무 커져서 정적배열로는 사용 못함, 아래처럼 동적배열을 만들어서 사용함
//1<<0: 0001 (1)
//1<<1: 0010 (2)
//1<<2: 0100 (4)
//1<<i: 1...(i개의 0).. → 2^i 정수값

int N, M;
int* freq; //동적할당 배열 (스택 메모리 초과 문제 때문에 동적배열 사용)
//이런식으로 최대값까지 0을 채운 배열을 만들고, 값이 있을 때마다 ++해주는 방식도 자주 쓰임

int str_to_bitmask(char* str)
{
    int mask = 0;
    for (int i = 0; i < M; i++) {
        if (str[i] == '1') mask |= (1 << i); //OR연산: 대응하는 비트가 하나라도 1이면 1 반환
    }
    return mask;
}

int main(void)
{
    scanf("%d %d", &N, &M);

    long long MAX_MASK = (1 << M);
    freq = (int*)calloc(MAX_MASK, sizeof(int));
    //malloc (초기화 없음): (int*)malloc(MAX_MASK * sizeof(int))
    //calloc (0으로 초기화): (int*)calloc(MAX_MASK, sizeof(int))

    int answer = 0;
    for (int i = 0; i < N; i++)
    {
        char temp[31]; scanf("%s", temp);
        int mask = str_to_bitmask(temp);
        //최대 두가지 영역에서만 다르면 친밀감을 느낌 → 같은 경우 / 1bit만 다를 경우 / 2bit만 다를 경우

        //같은 경우
        answer += freq[mask]; //2개 있으면 2쌍이 같은거니까 2를 더함

        //1bit만 다를 경우
        for (int i = 0; i < M; i++) {
            int flipped1 = mask ^ (1 << i); //XOR연산 (i번째 bit만 값을 반전)
            answer += freq[flipped1];
        }

        //2bit만 다를 경우
        for (int i = 0; i < M - 1; i++) {
            for (int j = i + 1; j < M; j++) {
                int flipped2 = mask ^ (1 << i) ^ (1 << j);
                answer += freq[flipped2];
            }
        }

        freq[mask]++; //현재 값이 있음을 저장
    }
    free(freq); //동적할당을 사용했을 때 꼭 사용

    printf("%d", answer);
    return 0;
}