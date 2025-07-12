// 문제: https://www.acmicpc.net/problem/1300

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int N, K;
	cin >> N >> K;

	int s = 1;
	int e = K; //B[K]는 K 이하 (N의 배수 배열이니까)
	// B[K]는 해당값보다 작거나 같은 수의 개수가 K인 값

	int answer = 0;
	while (s <= e)
	{
		int m = (s + e) / 2;
		
		int cnt = 0;
		for (int i = 1; i <= N; i++)
		{
			int val = min(N, m / i); //i번째 행에서 중앙값보다 작은 수의 개수 = 중앙값보다 작은 i 배수의 개수 (그래서 m / i)(이때 i행의 최대 길이가 N이므로 min)
			cnt += val;

			if (val == 0) break;
		}

		if (cnt < K) s = m + 1;
		else // cnt >= K
		{
			answer = m; //마지막에 저장되는 값은 cnt == K일 때임
			e = m - 1;
		}
	}

	cout << answer << '\n';
	return 0;
}