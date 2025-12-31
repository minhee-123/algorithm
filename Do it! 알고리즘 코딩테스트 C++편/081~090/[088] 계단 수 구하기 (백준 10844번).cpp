// 문제: https://www.acmicpc.net/problem/10844
#include <iostream>
using namespace std;

int N;
long long D[101][10]; // [a][b] = a자리 수의 숫자중 b로 끝나는 수의 개수

int main()
{
	cin >> N;
	D[1][0] = 0;
	for (int i = 1; i <= 9; i++) D[1][i] = 1;

	for (int n = 2; n <= N; n++)
	{
		for (int i = 0; i <= 9; i++)
		{
			if (i == 0) D[n][i] = D[n - 1][i + 1] % 1000000000;
			else if (i == 9) D[n][i] = D[n - 1][i - 1] % 1000000000;
			else D[n][i] = (D[n - 1][i - 1] + D[n - 1][i + 1]) % 1000000000;
		}
	}

	long long answer = 0;
	for (int i = 0; i <= 9; i++) answer = (answer + D[N][i]) % 1000000000;

	cout << answer;
	return 0;
}
// if, else if, else는 잘 구분해서 사용해야 함!!