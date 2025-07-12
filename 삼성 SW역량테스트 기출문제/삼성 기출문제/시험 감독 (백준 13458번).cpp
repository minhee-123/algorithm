// 문제: https://www.acmicpc.net/problem/13458

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int N; cin >> N;
	vector<int> test(N, 0);
	for (int i = 0; i < N; i++) cin >> test[i];

	int B, C;
	cin >> B >> C;

	long long cnt = 0; //수가 매우 커질 수 있음 (오버플로우 주의)
	for (int i = 0; i < N; i++)
	{
		test[i] -= B;
		cnt++;
		if (test[i] > 0)
		{
			cnt += test[i] / C;
			if (test[i] % C > 0) cnt++;
		}
	}

	cout << cnt;
	return 0;
}