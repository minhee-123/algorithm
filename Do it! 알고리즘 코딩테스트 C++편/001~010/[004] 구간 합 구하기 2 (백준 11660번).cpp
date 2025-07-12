// 문제: https://www.acmicpc.net/problem/11660

#include <iostream>
using namespace std;

int Origin[1025][1025] = { 0 };
int Sum[1025][1025] = { 0 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	// 위 구문 안 넣으면 시간초과 문제가 발생함 (근소한 시간차 문제)

	int N, M;
	cin >> N >> M;

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			int temp; cin >> temp;
			Origin[i][j] = temp; // 0행은 0으로 채움
		}
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			Sum[i][j] = Sum[i - 1][j] + Sum[i][j - 1] - Sum[i - 1][j - 1] + Origin[i][j]; // 0행을 0으로 가져와서 처리하기 때문에 따로 예외처리를 하지 않아도 됨
		}
	}

	for (int test = 0; test < M; test++)
	{
		int X1, Y1, X2, Y2;
		cin >> X1 >> Y1 >> X2 >> Y2;

		int answer = Sum[X2][Y2] - Sum[X1 - 1][Y2] - Sum[X2][Y1 - 1] + Sum[X1 - 1][Y1 - 1];
		cout << answer << '\n';
	}
	return 0;
}