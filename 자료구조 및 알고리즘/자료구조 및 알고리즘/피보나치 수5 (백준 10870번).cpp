// 피보나치 수 5 (https://www.acmicpc.net/problem/10870)

#include <iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;

	int p0 = 0, p1 = 1;
	if (N == 0) cout << p0;
	else if (N == 1) cout << p1;
	else
	{
		int p2 = 0;
		for (int i = 2; i <= N; i++)
		{
			p2 = p0 + p1;
			p0 = p1;
			p1 = p2;
		}
		cout << p2;
	}
	return 0;
}