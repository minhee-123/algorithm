// 문제: https://www.acmicpc.net/problem/11689

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	long n; cin >> n;
	long result = n;

	for (long i = 2; i <= sqrt(n); i++)
	{
		if (n % i != 0) continue;

		result = result - result / i;
		while (n % i == 0) n = n / i; //소인수 업데이트
	}
	if (n != 1) result = result - result / n; //n은 마지막 소인수 (1인 경우 제외)

	cout << result;
	return 0;
}