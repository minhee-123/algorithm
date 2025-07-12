// 문제: https://softeer.ai/practice/6269
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int M, N, K; scanf("%d %d %d", &M, &N, &K);

    int menu[100];
    for (int i = 0; i < M; i++) scanf("%d", &menu[i]); //window size: M
    int button[100];
    for (int i = 0; i < N; i++) scanf("%d", &button[i]);

    int flag = 0;
    int S = 0;
    while (S + M <= N) //슬라이딩 윈도우
    {
        int index = S;
        int flag_window = 0;
        for (int i = 0; i < M; i++)
        {
            if (button[index++] != menu[i])
            {
                flag_window = 1;
                break;
            }
        }

        if (flag_window == 1) S++; //시작점은 한칸씩 옮겨야 함 (test하는 구간 사이에 menu[0]이 있을수도 있음)
        else
        {
            flag = 1;
            break;
        }
    }

    if (flag == 1) printf("secret");
    else printf("normal");
    return 0;
}