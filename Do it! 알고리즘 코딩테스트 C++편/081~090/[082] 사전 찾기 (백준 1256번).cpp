// 문제: https://www.acmicpc.net/problem/1256
// 문제 풀이의 핵심은 N+M개에서 N(or M)개를 선택하는 것
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// 조합은 점화식으로 구현함 (DP가 기본)
// D[i][j] = D[i-1][j] + D[i-1][j-1]
// → i개 중에서 j개를 뽑는 조합 
//	  = 한 원소를 포함시키지 않고 뽑는 경우 + 한 원소를 포함시켜서 뽑는 경우 

// 현재 자리를 a로 선택할 경우 남은 문자로 만들 수 있는 모든 경우의 수 T
// → T가 K보다 작을 경우 z로 선택하고 K = K - T (T만큼 순서를 넘어감)

int N, M, K;
int D[201][201]; // 조합 점화식

int main()
{
	cin >> N >> M >> K;
	D[0][0] = 1;
	D[1][0] = 1;
	D[1][1] = 1;

	for (int i = 2; i <= N + M; i++)
	{
		D[i][0] = 1; // i개 중에서 0개를 뽑는 경우의 수 = 1
		for (int j = 1; j <= i; j++)
		{
			D[i][j] = D[i - 1][j] + D[i - 1][j - 1];
			if (D[i][j] > 1000000000) D[i][j] = 1000000000; // overflow 방지 (K는 10^9 이하이므로 10^9 이상 값들은 고정 / 조합 수는 10^58 이상까지 가기 때문)
		}
	}

	string answer = "";
	int nm = N + M;
	int m = M;

	if (D[nm][m] < K) cout << -1;
	else
	{
		while (nm > 0)
		{
			int T = D[nm - 1][m]; // a로 선택했을 때 남은 문자로 만드는 경우의 수

			if (T >= K) // K 이상인 경우 (만드는 경우의 수 중에 답이 있음)
			{
				answer += "a";
				nm--;
			}
			else // K보다 작은 경우 (만드는 경우의 수 중에 답이 없음 → 현재 자리가 a인 경우를 넘겨야 됨)
			{
				answer += "z";
				K = K - T;

				nm--;
				m--; // z를 하나 사용
			}

			if (nm == 0) break;
		}

		cout << answer;
	}
	return 0;
}