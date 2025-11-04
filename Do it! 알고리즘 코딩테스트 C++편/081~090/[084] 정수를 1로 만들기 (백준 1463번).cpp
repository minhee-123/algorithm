// 문제: https://www.acmicpc.net/problem/1463
#include <iostream>
using namespace std;

int N;
int DP[1000001]; // 최대값 1000000

int main()
{
	cin >> N;
	DP[0] = 0;
	DP[1] = 0;

	for (int num = 2; num <= N; num++)
	{
		DP[num] = DP[num - 1] + 1; // 1을 빼는 연산
		if (num % 2 == 0) DP[num] = min(DP[num], DP[num / 2] + 1); // 2로 나눌 수 있다면 둘 중 최소인 것으로 고름
		if (num % 3 == 0) DP[num] = min(DP[num], DP[num / 3] + 1); // 3으로 나눌 수 있다면 둘 중 최소인 것으로 고름

		// 연산 방법이 다양하니까
		// 다른 연산이 가능하다면 최소가 되는 연산을 수행하는 방향으로 가야 함 (모든 연산을 돌려서 선택)
	}

	cout << DP[N];
	return 0;
}