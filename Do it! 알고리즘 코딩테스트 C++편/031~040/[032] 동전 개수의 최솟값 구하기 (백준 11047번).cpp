// 문제: https://www.acmicpc.net/problem/11047

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int N, target;
	cin >> N >> target;
	
	vector<int> coin(N, 0);
	for (int i = 0; i < N; i++) cin >> coin[i];

	int cnt = 0;
	for (int i = N - 1; i >= 0; i--)
	{
		if (coin[i] > target) continue;

		cnt += target / coin[i];
		target = target % coin[i];

		if (target == 0) break;
	}

	cout << cnt;
	return 0;
}