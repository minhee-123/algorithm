// 문제: https://softeer.ai/practice/6282
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N;
int map[25][25];
int visit[25][25];
int answer[1375]; //25x25=1375
int answer_len = 0;

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

int cnt = 0;
void DFS(int row, int col)
{
    if (visit[row][col] == 1 || map[row][col] == 0) return; //0일 경우 탐색진행 불가능
    visit[row][col] = 1;
    cnt++;

    for (int i = 0; i < 4; i++) {
        int new_row = row + dr[i];
        int new_col = col + dc[i];

        if (new_row < 0 || new_row >= N || new_col < 0 || new_col >= N) continue;
        if (visit[new_row][new_col] == 1 || map[new_row][new_col] == 0) continue;
        DFS(new_row, new_col);
    }
}

int comp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b; //양수가 나오면 자리를 바꾸고 음수가 나오면 자리유지
}

int main(void)
{
    scanf("%d", &N);

    char temp[25][25];
    for (int i = 0; i < N; i++) scanf("%s", temp[i]);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) map[i][j] = temp[i][j] - '0';
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cnt = 0;
            DFS(i, j);
            if (cnt > 0) answer[answer_len++] = cnt;
        }
    }
    qsort(answer, answer_len, sizeof(int), comp);

    printf("%d\n", answer_len);
    for (int i = 0; i < answer_len; i++) printf("%d\n", answer[i]);
    return 0;
}