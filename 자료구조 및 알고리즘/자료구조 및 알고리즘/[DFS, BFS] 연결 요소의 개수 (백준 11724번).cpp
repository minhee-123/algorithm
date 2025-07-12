// 연결 요소의 개수 (https://www.acmicpc.net/problem/11724)

#include <iostream>
#include <vector>
using namespace std;

vector<int> graph[1005];
bool visit[1005]; //디폴트 false

int N, M;
int cc = 0;
vector<int> check;

void Find(int start)
{
	if (visit[start]) return;

	visit[start] = true;
	check.push_back(start);

	for (int i = 0; i < graph[start].size(); i++)
	{
		int next = graph[start][i];
		if (!visit[next]) Find(next);
	}
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int temp1, temp2;
		cin >> temp1 >> temp2;
		graph[temp1].push_back(temp2);
		graph[temp2].push_back(temp1); //무방향 그래프
	}

	for (int i = 1; i <= N; i++)
	{
		check.clear();
		Find(i);

		if (check.size() > 0) cc++;
	}
	cout << cc;
	return 0;
}