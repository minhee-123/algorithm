// 문제: https://www.acmicpc.net/problem/1010
#include <iostream>
using namespace std;

// 문제를 해석하면
// mCn을 구해야 함
// 순열이 아니라 조합인 이유 
// → 다리끼리는 겹칠 수 없음 (m개 중에서 n개를 고르면 순서는 자동으로 정해짐)
// → 순열로 구하면 오히려 중복 발생

int T;
int N, M;
int DP[31][31];

int main()
{
	for (int i = 0; i <= 30; i++)
	{
		DP[i][0] = 1;
		DP[i][1] = i;
		DP[i][i] = 1;
	}

	for (int i = 2; i <= 30; i++)
	{
		for (int j = 2; j < i; j++)
		{
			DP[i][j] = DP[i - 1][j] + DP[i - 1][j - 1];
			// i번째를 선택하지 않는 경우 + i번째를 선택하는 경우
		}
	}

	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> N >> M;
		cout << DP[M][N] << '\n';
	}
	return 0;
}