// 문제: https://softeer.ai/practice/6270
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct RUN
{
    int len;
    int vel;
};

int main(void)
{
    int N, M; scanf("%d %d", &N, &M);

    struct RUN real[100];
    struct RUN test[100];
    for (int i = 0; i < N; i++) scanf("%d %d", &real[i].len, &real[i].vel);
    for (int i = 0; i < M; i++) scanf("%d %d", &test[i].len, &test[i].vel);

    int over = 0;
    int Rindex = 0;
    int Tindex = 0;
    while (Rindex < N && Tindex < M) //끝나는 지점(겹쳐지는 경계선)에서만 속도 비교
    {
        int cal = 0;

        if (real[Rindex].len > test[Tindex].len)
        {
            real[Rindex].len -= test[Tindex].len;
            test[Tindex].len = 0;
            cal = test[Tindex].vel - real[Rindex].vel;
        }
        else if (real[Rindex].len < test[Tindex].len)
        {
            test[Tindex].len -= real[Rindex].len;
            real[Rindex].len = 0;
            cal = test[Tindex].vel - real[Rindex].vel;
        }
        else // real[Rindex].len == test[Tindex].len
        {
            real[Rindex].len = 0;
            test[Tindex].len = 0;
            cal = test[Tindex].vel - real[Rindex].vel;
        }

        if (cal > over) over = cal;

        if (real[Rindex].len == 0 && Rindex < N) Rindex++;
        if (test[Tindex].len == 0 && Tindex < M) Tindex++;
    }

    printf("%d", over);
    return 0;
}