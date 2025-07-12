// 문제: https://www.acmicpc.net/problem/1456

#include <iostream>
#include <cmath>
using namespace std;

#define max_num 10000001

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//거의 소수 → 소수의 제곱수를 구함
	//범위의 최대값이 10^14이므로 10^7(제곱이 10^14)까지의 소수를 구하면 됨
	//소수를 구할 때 범위 최대값의 제곱근까지만 탐색해도 됨 → 배수를 구하는 거니까, 제곱근 이후의 수는 소수라면 살아있고 아니라면 지워짐

	long A, B;
	cin >> A >> B;

	bool visit[max_num] = { false };
	visit[0] = true;
	visit[1] = true;

	for (int i = 2; i <= sqrt(max_num); i++)
	{
		if (visit[i]) continue;
		for (int j = i + i; j < max_num; j = j + i) visit[j] = true;
	}

	int cnt = 0;
	for (int i = 2; i < max_num; i++)
	{
		if (visit[i]) continue;

		long num = i;
		while ((double)i <= (double)B / (double)num) //나누기 수로 비교하니까 실수인 double 형태로 맞춤
		{
			if ((double)i >= (double)A / (double)num) cnt++; //오버플로우를 방지해서 N^(k-1)로 나눠서 비교함
			num *= i;
		}
	}

	cout << cnt;
	return 0;
}