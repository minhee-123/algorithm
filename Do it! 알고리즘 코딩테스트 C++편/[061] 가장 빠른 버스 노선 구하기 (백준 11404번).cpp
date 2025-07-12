// 문제: https://www.acmicpc.net/problem/11404
#include <iostream>
#include <limits.h>
#include <algorithm>
using namespace std;

int N, M;
int D[101][101]; //도시번호는 1부터 N

int main()
{
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (i == j) D[i][j] = 0;
			else D[i][j] = INT_MAX;
		}
	}

	for (int i = 0; i < M; i++)
	{
		int s, e, w;
		cin >> s >> e >> w;
		D[s][e] = min(D[s][e], w); //시작도시에서 도착도시로 가는 노선이 2개 이상일 수 있음 (최단비용으로 저장)
	}

	//플로이드-워셜
	for (int K = 1; K <= N; K++)
	{
		for (int S = 1; S <= N; S++)
		{
			for (int E = 1; E <= N; E++)
			{
				if (D[S][K] == INT_MAX || D[K][E] == INT_MAX) continue; //둘중 하나라도 무한대 값이면 업데이트 되지 않음 (연산중 오버플로우가 발생하니 따로 빼주기)
				D[S][E] = min(D[S][E], D[S][K] + D[K][E]); //S에서 E, S에서 K를 들렸다가 K에서 E → 전체 경로의 최단거리는 부분 경로의 최단거리의 조합으로 이루어짐
			}
		}
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (D[i][j] == INT_MAX) cout << 0 << " ";
			else cout << D[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}