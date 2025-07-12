// 문제: https://www.acmicpc.net/problem/1260
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

int N, M, V;
int map[1001][1001] = { 0 };
int visit[1001] = { 0 };

void DFS(int index)
{
	if (visit[index] == 1) return;
	visit[index] = 1;

	printf("%d ", index);
	for (int i = 1; i <= N; i++)
	{
		if (visit[i] == 0 && map[index][i]) DFS(i);
	}
}

void BFS(int index)
{
	int front = 0;
	int cnt = 0;

	int queue[1001] = { 0 };
	queue[0] = index;
	visit[index] = 1;
	cnt++;

	while (front < cnt)
	{
		int pop = queue[front];
		front++;

		printf("%d ", pop);
		for (int i = 1; i <= N; i++)
		{
			if (visit[i] == 0 && map[pop][i] == 1)
			{
				queue[cnt] = i;
				cnt++;
				visit[i] = 1;
			}
		}
	}
}

int main()
{
	scanf("%d %d %d", &N, &M, &V);
	for (int i = 1; i <= M; i++)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		map[x][y] = 1;
		map[y][x] = 1;
	}

	DFS(V);
	memset(visit, 0, (N + 1) * sizeof(int));
	printf("\n");
	BFS(V);
	return 0;
}