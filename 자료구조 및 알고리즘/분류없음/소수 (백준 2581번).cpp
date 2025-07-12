// 소수 (https://www.acmicpc.net/problem/2581)

#include <iostream>
#include <vector>
using namespace std;

bool decimal(int num)
{
	int cnt = 0;
	for (int i = 1; i <= num; i++)
	{
		if (num % i == 0) cnt++;
	}
	
	if (cnt == 2) return true;
	else return false;
}

int main()
{
	int M, N;
	cin >> M >> N;

	vector<int> DEC;
	for (int i = M; i <= N; i++)
	{
		if (decimal(i)) DEC.push_back(i);
	}

	int sum = 0;
	if (DEC.size() > 0)
	{
		for (int i = 0; i < DEC.size(); i++)
		{
			sum += DEC[i];
		}
		cout << sum << '\n' << DEC[0];
	}
	else cout << -1;

	return 0;
}