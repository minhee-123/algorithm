// DFS와 BFS (https://www.acmicpc.net/problem/1260)

// DFS → 결과까지 직행 → 재귀함수 or 스택으로 구현
// BFS → 가는 도중 갈 수 있는 곳을 탐색하며 진행 → 큐로 구현

// 그래프 표현 방식 → 인접 행렬 or 인접 리스트
// 인접 행렬 → 2차원 배열(행렬)
// 인접 리스트 → 벡터와 같은 배열 → 성능은 이게 더 좋음

// 1. DFS와 BFS를 수행하기 위해서는 그래프와 방문기록 필요
// 2. 인접행렬, 방문기록, 정점, 간선, 시작번호 전역 선언
// 3. 입력받고, 두 정점이 만나는 곳(연결됨)에 1을 넣어줌
// 4. DFS를 수행하고 순서대로 출력
// 5. 방문기록을 초기화 (memset 이용)
// 6. BFS를 수행하고 순서대로 출력

#include <iostream>
#include <vector>
#include <queue>
#include <string.h> //memset 사용 (0 또는 1, false 또는 true로 초기화)
#include <algorithm>
using namespace std;

#define MAX 10000

int N, M, V; //정점의 개수, 간선의 개수, 탐색을 시작할 정점의 번호
bool visited[MAX]; //방문기록 (전역으로 선언했기 때문에 false로 초기화되어 있음)

vector<int> gra[MAX]; //그래프 (인접리스트)
vector<int> answer_dfs;
vector<int> answer_bfs;

void DFS(int start)
{
	visited[start] = true; //정점 기록
	answer_dfs.push_back(start);

	for (int i = 0; i < gra[start].size(); i++) //연결된 정점의 수만큼 반복
	{
		int next = gra[start][i];
		if (!visited[next]) DFS(next); //연결된 정점 중 들리지 않은 곳이 있다면 그곳으로 이동
	}
}

void BFS(int start)
{
	queue<int> q; //BFS에 사용하는 큐

	visited[start] = true;
	q.push(start);

	while (!q.empty()) //큐가 비어있을 때까지 반복 (큐가 비어있다면 모든 정점을 탐색한 것)
	{
		int now = q.front();
		q.pop();
		answer_bfs.push_back(now);

		for (int i = 0; i < gra[now].size(); i++)
		{
			int next = gra[now][i];
			if (!visited[next])
			{
				visited[next] = true;
				q.push(next);
			}
		}
	}
}

int main()
{
	cin >> N >> M >> V;
	for (int i = 1; i <= M; i++) //간선이 연결하는 두 정점의 번호 저장 (양방향 간선)
	{
		int temp1, temp2;
		cin >> temp1 >> temp2;
		gra[temp1].push_back(temp2);
		gra[temp2].push_back(temp1); //양방향
	}
	for (int i = 1; i <= N; i++)
	//문제에서 차례대로 원소 방문할 것을 요구함 (그래서 정렬 진행)
	//★정점의 범위는 1부터 N까지인 것을 주의 (0부터 N-1로 하면 틀림)
	{
		sort(gra[i].begin(), gra[i].end()); 
	}

	DFS(V);
	memset(visited, false, sizeof(visited)); //배열 memset 사용방법
	BFS(V);

	for (int i = 0; i < answer_dfs.size(); i++) cout << answer_dfs[i] << " ";
	cout << '\n';
	for (int i = 0; i < answer_bfs.size(); i++) cout << answer_bfs[i] << " ";
	return 0;
}