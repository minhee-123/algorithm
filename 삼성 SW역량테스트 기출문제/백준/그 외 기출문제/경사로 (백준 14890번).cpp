// 문제: https://www.acmicpc.net/problem/14890
#include <iostream>
#include <cstring>
using namespace std;

// 행 또는 열의 연속한 숫자들이 모두 같거나
// 연속할 때 -1씩 차이가 나는데 작은 숫자가 최소 L개 나와야 함 (카운트한 숫자는 중복해서 카운트 하지 않음 → 211112는 가능하지만 21112는 불가능)

int N, L;
int Map[100][100];
bool visit[100];

bool can_move_row(int row)
{
	memset(visit, false, sizeof(visit));

	int col = 0;
	while (col < N - 1)
	{
		int now = Map[row][col];
		int next = Map[row][col + 1];

		if (now == next) // 같은 경우
		{
			col++;
			continue;
		}
		else if (next - 1 == now) // 다음칸이 1 높은 경우
		{
			int cnt = 0; // 디버깅한 부분 (아래에도 모두 동일하게 적용)
			// cnt = 1로 하고 현재(혹은 다음)칸을 제외하고 그 다음칸부터 계산했는데
			// visit을 확실히 적용하기 위해서는 무조건 현재칸부터 for문을 돌려야 됨
			for (int i = col; i >= 0; i--)
			{
				if (Map[row][i] == now && visit[i] == false)
				{
					cnt++;
					visit[i] = true;

					if (cnt == L) break;
				}
				else break;
			}

			if (cnt == L)
			{
				col++;
				continue;
			}
			else return false;
		}
		else if (next + 1 == now) // 다음칸이 1 낮은 경우
		{
			int cnt = 0;
			for (int i = col + 1; i < N; i++)
			{
				if (Map[row][i] == next && visit[i] == false)
				{
					cnt++;
					visit[i] = true;

					if (cnt == L) break;
				}
				else break;
			}

			if (cnt == L)
			{
				col += L;
				continue;
			}
			else return false;
		}
		else return false; // 칸의 차이가 2 이상인 경우
	}
	return true;
}

bool can_move_col(int col)
{
	memset(visit, false, sizeof(visit));

	int row = 0;
	while (row < N - 1)
	{
		int now = Map[row][col];
		int next = Map[row + 1][col];

		if (now == next) // 같은 경우
		{
			row++;
			continue;
		}
		else if (next - 1 == now) // 다음칸이 1 높은 경우
		{
			int cnt = 0;
			for (int i = row; i >= 0; i--)
			{
				if (Map[i][col] == now && visit[i] == false)
				{
					cnt++;
					visit[i] = true;

					if (cnt == L) break;
				}
				else break;
			}

			if (cnt == L)
			{
				row++;
				continue;
			}
			else return false;
		}
		else if (next + 1 == now) // 다음칸이 1 낮은 경우
		{
			int cnt = 0;
			for (int i = row + 1; i < N; i++)
			{
				if (Map[i][col] == next && visit[i] == false)
				{
					cnt++;
					visit[i] = true;

					if (cnt == L) break;
				}
				else break;
			}

			if (cnt == L)
			{
				row += L;
				continue;
			}
			else return false;
		}
		else return false; // 칸의 차이가 2 이상인 경우
	}
	return true;
}

int main()
{
	cin >> N >> L;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) cin >> Map[i][j];
	}
	int answer = 0;

	for (int i = 0; i < N; i++)
	{
		if (can_move_row(i)) answer++;
		if (can_move_col(i)) answer++;
	}
	cout << answer;
	return 0;
}