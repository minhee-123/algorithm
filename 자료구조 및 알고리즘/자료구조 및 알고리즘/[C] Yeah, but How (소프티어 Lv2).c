// 문제: https://softeer.ai/practice/9498
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

int main(void)
{
    char str[200001];
    scanf("%s", str);
    char answer[500001];

    int index = 0;
    int len = strlen(str); 
    //strlen()의 시간복잡도는 O(N)이므로 중복으로 계속 호출할 경우 O(N^2)의 시간복잡도를 가져 시간초과가 발생할 수도 있음
    //한번만 호출해서 저장해두고 사용하기

    for (int i = 0; i < len - 1; i++) {
        answer[index++] = str[i];
        if (str[i] == '(' && str[i + 1] == ')') answer[index++] = '1';
        else if (str[i] == ')' && str[i + 1] == '(') answer[index++] = '+';
    }
    answer[index] = str[len - 1];

    printf("%s", answer);
    return 0;
}