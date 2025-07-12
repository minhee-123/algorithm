// 문제: https://softeer.ai/practice/7703
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

int main(void)
{
    int N; scanf("%d", &N);

    char str1[1000001]; //동적할당 char* str1 = (char*)malloc(1000001*sizeof(char))을 쓰려고 했으나 시간초과 발생
    char str2[1000001]; //scanf에 문자열을 재사용해도 문제 없다 (문자열 전체를 새로운 값으로 바꿔줌)
    for (int i = 0; i < N; i++) {
        scanf("%s %s", str1, str2);

        int len = strlen(str1);
        int idx = 0;
        while (str1[idx] != 'x' && str1[idx] != 'X') idx++;

        if (str2[idx] >= 'a' && str2[idx] <= 'z') printf("%c", str2[idx] - 32);
        else printf("%c", str2[idx]);
    }

    return 0;
}