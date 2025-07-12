// 설탕 배달 (https://www.acmicpc.net/problem/2839)

#include <iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;

	int cnt_5 = N / 5;
	while (1)
	{
		if ((N - 5 * cnt_5) % 3 == 0) break;
		else cnt_5--;

		if (cnt_5 < 0) break;
	}

	if (cnt_5 < 0) cout << -1;
	else
	{
		int cnt_3 = (N - 5 * cnt_5) / 3;
		cout << cnt_3 + cnt_5;
	}
	return 0;
}