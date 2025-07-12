// 문제: https://www.acmicpc.net/problem/11659
// 구간 합 알고리즘

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M;
	cin >> N >> M;

	vector<int> S(N + 1, 0);
	cin >> S[1];
	for (int i = 2; i <= N; i++)
	{
		int temp;
		cin >> temp;

		S[i] = S[i - 1] + temp;
	}

	for (int index = 0; index < M; index++)
	{
		int i, j;
		cin >> i >> j;

		if (i == 1) cout << S[j] << '\n';
		else
		{
			cout << S[j] - S[i - 1] << '\n';
		}
	}
	return 0;
}