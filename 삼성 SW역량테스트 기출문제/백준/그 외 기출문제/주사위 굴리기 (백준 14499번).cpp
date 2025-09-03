// 문제: https://www.acmicpc.net/problem/14499

/* 오랜만에 풀어서 더 그렇지만 문제 풀이가 오래 걸렸다 */
/*	1. 주사위를 회전시킬 때 전개도 위치가 변하지 않는다고 생각했음
	2. BUT 실제로는 주사위를 굴리다보면 앞면, 뒷면, 오른쪽면, 왼쪽면이 변함 → 이 부분을 반영해주어야 함 */

// (+) 문제도 꼼꼼하게 읽어야 한다 조건 하나 빼먹어서 디버깅 오래 걸림 (row랑 col도 헷갈리게 제시하고 있음)

#include <iostream>
using namespace std;

int Map[20][20];

int N, M, K;
int diceR, diceC; //현재 위치

int dr[5] = { 0, 0, 0, -1, 1 }; // 1부터 4까지 (인덱스 1부터 4까지 사용)
int dc[5] = { 0, 1, -1, 0, 0 }; // 동 서 북 남

int dice[6];
// 0 (윗면), 1 (아랫면), 2 (앞면), 3 (뒷면), 4 (오른쪽면), 5 (왼쪽면)

void rolling(int dir)
{
	int tmp[6];
	for (int i = 0; i < 6; i++) tmp[i] = dice[i];

	if (dir == 1) // 동
	{
		tmp[0] = dice[5];
		tmp[1] = dice[4];
		tmp[4] = dice[0];
		tmp[5] = dice[1];
	}
	if (dir == 2) // 서
	{
		tmp[0] = dice[4];
		tmp[1] = dice[5];
		tmp[4] = dice[1];
		tmp[5] = dice[0];
	}
	if (dir == 3) // 북
	{
		tmp[0] = dice[2];
		tmp[1] = dice[3];
		tmp[2] = dice[1];
		tmp[3] = dice[0];
	}
	if (dir == 4) // 남
	{
		tmp[0] = dice[3];
		tmp[1] = dice[2];
		tmp[2] = dice[0];
		tmp[3] = dice[1];
	}

	for (int i = 0; i < 6; i++) dice[i] = tmp[i];
}

int main()
{
	cin >> N >> M >> diceR >> diceC >> K;
	// diceR과 diceC가 x랑 y로 주어져있는데 문제에서 x를 row로 y를 col로 줌 (일반적인 x랑 y가 아님을 주의)
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) cin >> Map[i][j];
	}

	for (int T = 0; T < K; T++)
	{
		int dir;
		cin >> dir;

		int R = diceR + dr[dir];
		int C = diceC + dc[dir];

		if (R < 0 || R >= N || C < 0 || C >= M) continue;

		rolling(dir);

		if (Map[R][C] == 0) Map[R][C] = dice[1];
		else
		{
			dice[1] = Map[R][C];
			Map[R][C] = 0;
		}

		cout << dice[0] << '\n';
		
		diceR = R;
		diceC = C;
	}

	return 0;
}