// 문제: https://www.acmicpc.net/problem/14502
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

// 주어지는 N과 M의 최대크기가 8 → 완전탐색
// 머리가 안 돌아가서 최적화는 못함 (조합 + 모든 경우에 탐색 + 전체 루프돌며 갯수 check 등등)
int N, M;
int maxA = 0;

vector<vector<int>> Map;
vector<vector<int>> Map_test;
bool visit[8][8];

vector<pair<int, int>> virus;
vector<pair<int, int>> Empty;
vector<vector<int>> wall_index;

vector<int> Label;
void combination(int depth, int next) //조합 함수 (자주 사용된다! 잘 기억해두자!)
{
	if (depth == 3) //벽의 개수는 3
	{
		wall_index.push_back(Label);
		return;
	}

	for (int i = next; i < Empty.size(); i++)
	{
		Label.push_back(i);
		combination(depth + 1, i + 1);
		Label.pop_back();
	}
}

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

void DFS(int NR, int NC)
{
	if (visit[NR][NC]) return;
	visit[NR][NC] = true;

	for (int i = 0; i < 4; i++)
	{
		int nextR = NR + dr[i];
		int nextC = NC + dc[i];

		if (nextR < 0 || nextR >= N || nextC < 0 || nextC >= M) continue;
		if (visit[nextR][nextC]) continue;
		if (Map_test[nextR][nextC] > 0) continue;

		Map_test[nextR][nextC] = 2;
		DFS(nextR, nextC);
	}
}

int main()
{
	cin >> N >> M;

	Map.resize(N);
	Map_test.resize(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			int temp;
			cin >> temp;
			Map[i].push_back(temp);
			Map_test[i].push_back(temp);

			if (Map[i][j] == 0) Empty.push_back({ i, j });
			if (Map[i][j] == 2) virus.push_back({ i, j });
		}
	}

	combination(0, 0);

	for (int i = 0; i < wall_index.size(); i++)
	{
		Map_test = Map; //맵 초기화
		memset(visit, false, sizeof(visit)); //visit 초기화

		for (int j = 0; j < 3; j++) //벽 세우기
		{
			int R = Empty[wall_index[i][j]].first;
			int C = Empty[wall_index[i][j]].second;
			Map_test[R][C] = 1;
		}

		for (int k = 0; k < virus.size(); k++) DFS(virus[k].first, virus[k].second); //바이러스 전염

		int Area = 0;
		for (int n = 0; n < N; n++)
		{
			for (int m = 0; m < M; m++)
			{
				if (Map_test[n][m] == 0) Area++;
			}
		}
		maxA = max(maxA, Area);
	}

	cout << maxA;
	return 0;
}