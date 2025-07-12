// 문제: https://www.acmicpc.net/problem/11050
#include <iostream>
using namespace std;

// 이항계수 → 조합의 개수
// (n k) = nCk

int main()
{
	int n, k;
	cin >> n >> k;

	int DP[11][11];
	
	for (int i = 0; i <= n; i++) // DP테이블 초기화
	{
		DP[i][0] = 1;
		DP[i][1] = i;
		DP[i][i] = 1;
	} // 미리 알 수 있는 값들을 채워놓음 

	for (int i = 2; i <= n; i++)
	{
		for (int j = 2; j < i; j++)
		{
			DP[i][j] = DP[i - 1][j] + DP[i - 1][j - 1]; 
			// i번째를 선택한 경우 + i번째를 선택하지 않은 경우
			// (i번째 앞에 있는 애들은 이미 선택이 되었다고 생각하는 것)
		}
	}

	cout << DP[n][k];
	return 0;
}