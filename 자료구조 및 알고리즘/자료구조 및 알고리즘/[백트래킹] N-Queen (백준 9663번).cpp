// 문제: https://www.acmicpc.net/problem/9663
#include <iostream>
#include <cmath>
using namespace std;

// N x N 체스판 위에 퀸 N개를 서로 공격할 수 없게 배치하는 경우의 수
// 같은 행, 열, 대각선에 놓으면 안됨 → 각 행과 열에 하나의 퀸 (퀸의 대각선 라인에도 다른 퀸이 있으면 안됨)

// 2차원 배열로 백트래킹을 진행할 경우 시간초과가 발생할 수도 있음 (그리고 복잡)
// 1차원 배열로 수행하는 것이 효율적임 (각 행에 퀸이 하나밖에 없기 때문에 가능함)

int N;
int Row[14]; //각 행을 나타냄 → Row[2] = 3, 2번째 행에서 3번째 열에 퀸
int visit[14]; //열을 사용했는지 check (행은 순서대로 내려옴)

int cnt = 0;
void Queen(int depth) //depth → 현재 row
{
	if (depth == N)
	{
		cnt++;
		return;
	}

	for (int col = 0; col < N; col++)
	{
		if (visit[col]) continue; //같은 열에 있는지 check

		int flag = false;
		for (int row = 0; row < depth; row++) //대각선에 있는지 check
		{
			//(X, Y)의 대각선에 위치한 (A, B)는 |X-A| = |Y-B|를 만족함
			if (abs(row - depth) == abs(Row[row] - col))
			{
				flag = true;
				break;
			}
		}
		if (flag) continue;

		Row[depth] = col;
		visit[col] = true;
		Queen(depth + 1);
		visit[col] = false;
	}
}

int main()
{
	cin >> N;
	Queen(0);
	cout << cnt;
	return 0;
}
// 2차원 배열의 문제지만 각 행에 하나의 퀸만 배치한다는 점에서 1차원으로 해결 가능 (각 행에 하나 → 1차원 접근 가능)
// 대각선에 있는지 계산하는 법 숙지