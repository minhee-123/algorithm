// 문제: https://www.acmicpc.net/problem/23288
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int dr[4] = { 0, 1, 0, -1 }; // 동 남 서 북
int dc[4] = { 1, 0, -1, 0 };

int N, M, K;
int answer = 0;
int Map[21][21];

int R = 1, C = 1; // 시작점 (1, 1)
int dir = 0; // 시작 방향은 동쪽

// 입력
void Input()
{
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++) cin >> Map[i][j];
	}
}

// 주사위
int dice[6] = { 1, 3, 5, 4, 2, 6 }; // 윗면(0), 동(1), 남(2), 서(3), 북(4), 아랫면(5)
void rolling(int dir) // dir 방향으로 주사위가 굴러감
{
	int temp[6];
	for (int i = 0; i < 6; i++) temp[i] = dice[i];

	if (dir == 0) // 동쪽
	{
		dice[0] = temp[3];
		dice[5] = temp[1];
		dice[1] = temp[0];
		dice[3] = temp[5];
	}
	else if (dir == 1) // 남쪽
	{
		dice[0] = temp[4];
		dice[5] = temp[2];
		dice[2] = temp[0];
		dice[4] = temp[5];
	}
	else if (dir == 2) // 서쪽
	{
		dice[0] = temp[1];
		dice[5] = temp[3];
		dice[1] = temp[5];
		dice[3] = temp[0];
	}
	else // 북쪽
	{
		dice[0] = temp[2];
		dice[5] = temp[4];
		dice[2] = temp[5];
		dice[4] = temp[0];
	}
}

// 게임 (한 턴)
bool visit[21][21];
int move_cnt = 0;

void DFS(int NR, int NC)
{
	if (visit[NR][NC]) return;
	visit[NR][NC] = true;
	move_cnt++;

	for (int i = 0; i < 4; i++)
	{
		int NNR = NR + dr[i];
		int NNC = NC + dc[i];

		if (NNR < 1 || NNR > N || NNC < 1 || NNC > M) continue; // 격자 나가는 범위를 잘못 설정해서 디버깅 수행 (M을 N으로 적음!! 정신차리자!!)
		if (visit[NNR][NNC]) continue;
		if (Map[NR][NC] != Map[NNR][NNC]) continue;

		DFS(NNR, NNC);
	}
}

void Game()
{
	int NR = R + dr[dir];
	int NC = C + dc[dir];
	if (NR < 1 || NR > N || NC < 1 || NC > M)
	{
		dir += 2;
		if (dir >= 4) dir -= 4;

		NR = R + dr[dir];
		NC = C + dc[dir];
	}
	rolling(dir); // 해당 방향으로 주사위가 굴러감

	memset(visit, false, sizeof(visit));
	move_cnt = 0;
	DFS(NR, NC);

	answer += (Map[NR][NC] * move_cnt); // 주사위가 도착한 칸에 대한 점수 획득

	// 다음 이동 방향 결정
	if (dice[5] > Map[NR][NC])
	{
		dir++;
		if (dir >= 4) dir = 0;
	}
	else if (dice[5] < Map[NR][NC])
	{
		dir--;
		if (dir <= -1) dir = 3;
	}
	// dice[5] == Map[NR][NC]인 경우 변화 없음

	R = NR;
	C = NC;
}

void Solution()
{
	Input();
	for (int i = 0; i < K; i++) Game();
	cout << answer;
}

int main()
{
	Solution();
	return 0;
}