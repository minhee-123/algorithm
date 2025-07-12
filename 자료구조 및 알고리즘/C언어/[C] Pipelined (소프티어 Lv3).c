// 문제: https://softeer.ai/practice/9496
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//이것도 한양 어쩌구 문제처럼 독해문제라고 합니다
//왜 자꾸 독해문제를 내는 걸까요 (실제 시험에서 이러지는 않겠지만)
int main(void)
{
    //모든 자동차가 작업 슬롯을 거쳐 생산될 때까지 걸리는 최소 시간
    //결국 모든 프로세스를 한번씩은 만드는게 최소 시간이므로
    //배열 S의 최대값 + 배열 S의 길이 - 1이 정답 
    //(주어진 순서대로 넣지 않아도 되기 때문에 성립됨)
    //(하나씩 넣어야 하기 때문에 두 자동차 사이에 1초의 delay → 배열 S의 길이 - 1)

    int N; scanf("%d", &N);
    int max_s = 0;
    for (int i = 0; i < N; i++)
    {
        int s; scanf("%d", &s);
        if (s > max_s) max_s = s;
    }

    int answer = max_s + N - 1;
    printf("%d", answer);
    return 0;
}