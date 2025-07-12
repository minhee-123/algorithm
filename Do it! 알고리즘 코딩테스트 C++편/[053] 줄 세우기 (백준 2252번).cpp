// 문제: https://www.acmicpc.net/problem/2252

// 대표적인 위상정렬 구현 문제
// 사이클이 없으니까 visit은 체크하지 않아도 됨 (다시 되돌아 올 일이 없음)
// visit이랑 answer 큐를 만들었을 때는 틀렸음 → 아마 이 부분에서 꼬인 거 아닐까

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
vector<int> student[32001];
queue<int> line;
int D[32001] = { 0 };

int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int s1, s2;
		cin >> s1 >> s2;
		
		student[s1].push_back(s2);
		D[s2]++;
	}

	for (int i = 1; i <= N; i++) //진입차수가 0인 노드 먼저 큐에 넣어주고
	{
		if (D[i] == 0) line.push(i);
	}

	while (!line.empty()) //변형된 BFS 수행 (진입차수가 0이되면 큐에 노드 추가)
	{
		int now = line.front();
		line.pop();

		cout << now << ' ';

		for (int i = 0; i < student[now].size(); i++)
		{
			int next = student[now][i];
			D[next]--;
			if (D[next] == 0) line.push(next);
		}
	}

	return 0;
}