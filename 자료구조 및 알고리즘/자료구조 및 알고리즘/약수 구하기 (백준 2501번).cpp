// 약수 구하기 (https://www.acmicpc.net/problem/2501)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int N, K;
	cin >> N >> K;

	vector<int> divisor;
	for (int i = 1; i <= N; i++)
	{
		int div = N % i;
		if (div == 0) divisor.push_back(i);
	}
	sort(divisor.begin(), divisor.end());


	if (K > divisor.size()) cout << 0;
	else cout << divisor[K - 1];
	return 0;
}