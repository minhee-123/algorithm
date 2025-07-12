// 문제: https://softeer.ai/practice/9657
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

int map[101][101];
int N, M, attack1, attack2, trash, cnt = 0;

int main(void)
{
    //INPUT
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%d", &map[i][j]);
            if (map[i][j] == 1) cnt++;
        }
    }
    scanf("%d %d", &attack1, &trash);
    scanf("%d %d", &attack2, &trash);

    //ATTACK1
    for (int i = attack1; i < attack1 + 5; i++) {
        for (int j = 1; j <= M; j++) {
            if (map[i][j] == 1) {
                map[i][j] = 0;
                cnt--;
                break;
            }
        }
    }

    for (int i = attack2; i < attack2 + 5; i++) {
        for (int j = 1; j <= M; j++) {
            if (map[i][j] == 1) {
                map[i][j] = 0;
                cnt--;
                break;
            }
        }
    }

    printf("%d", cnt);
    return 0;
}