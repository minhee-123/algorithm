// 문제: https://www.acmicpc.net/problem/14503
#include <iostream>
#include <vector>
using namespace std;

int dr[4] = {-1, 0, 1, 0}; //북, 동, 남, 서
int dc[4] = {0, 1, 0, -1};

int N, M, SR, SC, SD;
int MAP[50][50];

int back(int dir)
{
	if (dir == 0) return 2;
	else if (dir == 1) return 3;
	else if (dir == 2) return 0;
	else return 1;
}

int turn(int dir)
{
	if (dir == 0) return 3;
	else if (dir == 1) return 0;
	else if (dir == 2) return 1;
	else return 2;
}

int answer = 0; //청소하는 칸의 개수
void DFS(int row, int col, int dir)
{
	if (MAP[row][col] == 0)
	{
		MAP[row][col] = 2; //청소함
		answer++;
	}

	int cnt = 0;
	for (int i = 0; i < 4; i++)
	{
		if (MAP[row + dr[i]][col + dc[i]] >= 1) cnt++;
	}

	int direction, NR, NC;
	if (cnt == 4) //주변에 청소할 곳이 없음
	{
		direction = back(dir);
		NR = row + dr[direction];
		NC = col + dc[direction];

		if (NR < 0 || NR >= N || NC < 0 || NC >= M) return;
		if (MAP[NR][NC] == 1) return;

		DFS(NR, NC, dir);
	}
	else //주변에 청소할 곳이 있음
	{
		for (int i = 0; i < 4; i++)
		{
			dir = turn(dir);
			NR = row + dr[dir];
			NC = col + dc[dir];

			if (NR >= 0 && NR < N && NC >= 0 && NC < M && MAP[NR][NC] == 0) break;
		}
		DFS(NR, NC, dir);
	}
}

int main()
{
	cin >> N >> M >> SR >> SC >> SD;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) cin >> MAP[i][j];
	} // 0(청소되지 않은 빈칸), 1(벽)

	DFS(SR, SC, SD);
	cout << answer;
	return 0;
}