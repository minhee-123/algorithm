// 문제: https://www.acmicpc.net/problem/1934

#include <iostream>
using namespace std;

int calculation(int A, int B)
{
	int big, small;
	if (A > B)
	{
		big = A;
		small = B;
	}
	else
	{
		big = B;
		small = A;
	}

	while (big % small != 0)
	{
		int temp = big;
		big = small;
		small = temp % small;
	}

	return (A * B) / small;
}

int main()
{
	int T; cin >> T;
	for (int i = 0; i < T; i++)
	{
		int A, B;
		cin >> A >> B;

		int num = calculation(A, B);
		cout << num << '\n';
	}
	return 0;
}