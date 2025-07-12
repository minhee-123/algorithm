// 문제: https://www.acmicpc.net/problem/1389
#include <iostream>
using namespace std;

int N, M;
int D[101][101];
int kevin[101] = { 0 };

int main()
{
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (i == j) D[i][j] = 0;
			D[i][j] = 1000;
		}
	}

	for (int i = 0; i < M; i++)
	{
		int A, B;
		cin >> A >> B;
		D[A][B] = 1;
		D[B][A] = 1; //무방향 그래프
	}

	for (int K = 1; K <= N; K++)
	{
		for (int S = 1; S <= N; S++)
		{
			for (int E = 1; E <= N; E++) D[S][E] = min(D[S][E], D[S][K] + D[K][E]); //무한대값을 1000으로 뒀기 때문에 오버플로우 문제 없음
		}
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++) kevin[i] += D[i][j];
	}

	int min_index = 1;
	for (int i = 1; i <= N; i++)
	{
		if (kevin[min_index] > kevin[i]) min_index = i;
	}

	cout << min_index;
	return 0;
}