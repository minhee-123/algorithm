// 문제: https://www.acmicpc.net/problem/20058
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int N, len, Q;
vector<vector<int>> A;
vector<int> cmd;

void Input()
{
	cin >> N >> Q;
	len = pow(2, N);

	A.resize(len);
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			int temp; cin >> temp;
			A[i].push_back(temp);
		}
	}

	for (int i = 0; i < Q; i++)
	{
		int temp; cin >> temp;
		cmd.push_back(temp);
	}
}

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

void FireStorm()
{
	for (int i = 0; i < Q; i++) //파이어스톰 Q번 실행
	{
		int L = cmd[i];
		int partLen = pow(2, L);

		vector<vector<int>> copyA = A;
		int LR = 0; //좌측상단 R좌표
		int LC = 0; //좌측상단 C좌표

		while (1)
		{
			int RR = LR + partLen - 1; //우측하단 R좌표
			int RC = LC + partLen - 1; //우측하단 C좌표

			for (int i = LR; i <= RR; i++)
			{
				for (int j = LC; j <= RC; j++)
				{
					int orig_i = LR + (RC - j);
					int orig_j = LC + (i - LR);
					copyA[i][j] = A[orig_i][orig_j]; //회전
				}
			}

			if (RR == len - 1 && RC == len - 1) break; //모두 회전되었다면 break
			
			if (LC + partLen >= len)
			{
				LR = LR + partLen;
				LC = 0;
			}
			else LC = LC + partLen; //좌표 이동
		}
		A = copyA; //회전한 내용으로 업데이트

		vector<vector<int>> copyB = A; //얼음양은 한번에 감소됨 → 연쇄적인 영향을 피하기 위해 copy 사용
		for (int i = 0; i < len; i++) //얼음양 체크
		{
			for (int j = 0; j < len; j++)
			{
				if (A[i][j] == 0) continue;

				int cnt = 0;
				for (int dir = 0; dir < 4; dir++)
				{
					int row = i + dr[dir];
					int col = j + dc[dir];

					if (row < 0 || row >= len || col < 0 || col >= len) continue;
					if (A[row][col] > 0) cnt++;
				}

				if (cnt < 3) copyB[i][j]--;
			}
		}
		A = copyB; //얼음이 감소한 양으로 업데이트
	}
}

int total_ice = 0;
int Combi = 0;
int maxCombi = 0;
bool visit[65][65];

void DFS(int R, int C)
{
	if (visit[R][C] || A[R][C] == 0) return;
	
	visit[R][C] = true;
	Combi++;

	for (int i = 0; i < 4; i++)
	{
		int nextR = R + dr[i];
		int nextC = C + dc[i];

		if (nextR < 0 || nextR >= len || nextC < 0 || nextC >= len) continue;
		if (visit[nextR][nextC] || A[nextR][nextC] == 0) continue;

		DFS(nextR, nextC);
	}
}

void Result()
{
	for (int R = 0; R < len; R++)
	{
		for (int C = 0; C < len; C++)
		{
			total_ice += A[R][C]; //총 얼음 수 계산

			Combi = 0;
			DFS(R, C);

			maxCombi = max(maxCombi, Combi); //덩어리 계산
		}
	}

	cout << total_ice << '\n';
	cout << maxCombi;
}

int main()
{
	Input();
	FireStorm();
	Result();

	return 0;
}

// (1)
// 얼음을 연쇄적으로 녹이면 안된다 → 얼음을 연쇄적으로 녹여서 오답 발생
// 카피 부분을 만들거나 녹아야 하는 얼음을 기록해둬서 "한번에" 녹여야 함 (업데이트해야 함)
// (2)
// 얼음 덩어리는 얼음이 있는 곳끼리만 연결된다 → 얼음 여부를 생각하지 않음
// 얼음이 있을 경우에만 DFS를 계속 수행하도록 해야 함
// (3)
// 회전을 제대로 구현하지 못했음 → LR과 LC가 업데이트 되는 부분을 잘못 구현
// 회전이 제대로 이루어지지 않아 계속해서 오류가 발생함
// ★ 회전이 포함된 문제에서 오답이 발생한다면 회전 부분을 꼭 점검 (출력하면서 점검!!)