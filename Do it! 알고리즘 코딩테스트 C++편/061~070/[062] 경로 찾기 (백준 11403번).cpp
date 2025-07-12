// 문제: https://www.acmicpc.net/problem/11403
#include <iostream>
#include <limits.h>
using namespace std;

int N;
int D[100][100];

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) cin >> D[i][j];
	}

	for (int K = 0; K < N; K++)
	{
		for (int S = 0; S < N; S++)
		{
			for (int E = 0; E < N; E++)
			{
				if (D[S][K] == 1 && D[K][E]) D[S][E] = 1; //플로이드-워셜 점화식 수정 (K를 경유하는 경로가 있다면 1)
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) cout << D[i][j] << " ";
		cout << "\n";
	}
	return 0;
}