// 문제: https://www.acmicpc.net/problem/13023

#include <iostream>
#include <vector>
using namespace std;

int N, M;
vector<int> P[2001];
bool visit[2001];
bool arrive = false;

void DFS(int index, int cnt)
{
	if (cnt == 5 || arrive) //문제에서 요구하는 것은 결국 깊이가 5인 분기가 있는지
	{
		arrive = true;
		return;
	}

	visit[index] = true;
	for (int i = 0; i < P[index].size(); i++)
	{
		int next = P[index][i];

		if (visit[next]) continue;
		DFS(next, cnt + 1);
	}
	visit[index] = false; //방문 체크의 초기화 (방문 순서에 따라서 깊이가 달라짐)
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int temp1, temp2;
		cin >> temp1 >> temp2;

		P[temp1].push_back(temp2);
		P[temp2].push_back(temp1);
	}

	for (int i = 0; i < N; i++)
	{
		DFS(i, 1);
		if (arrive) break;
	}

	if (arrive) cout << 1;
	else cout << 0;
	return 0;
}