// 최소 신장 트리 구하기
// 문제: https://www.acmicpc.net/problem/1197

// 최소 신장 트리: 그래프에서 모든 노드를 연결할 때 에지의 가중치를 최소로 하는 트리 (트리는 사이클이 존재하지 않는 방향 그래프, 부모-자식 관계가 성립함)
// 에지 리스트 (에지 위주로 정보 저장) + 유니온파인드 (사이클 여부 판별) 로 구현함
// 에지 리스트를 구현할 때 우선순위 큐를 활용 (최소값을 계속해서 사용하기 때문)

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct edge
{
	int a;
	int b;
	int w;

	bool operator()(edge A, edge B) { return A.w > B.w; } //오름차순으로 정렬 (sort에서 리턴값과 반대로 생각)
	//우선순위 큐의 정렬함수는 struct 내부함수로 구현 (내부에 변수를 선언해서 사용 중이어도 상관 없는 듯)
};

int V, E;
vector<int> UF; //유니온파인드 배열
priority_queue<edge, vector<edge>, edge> pq;

int cnt = 0;
int answer = 0; //사용한 가중치 누적

int Find(int c)
{
	if (UF[c] == c) return c;
	else return UF[c] = Find(UF[c]);
}

void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);

	if (a > b) swap(a, b); //대표노드로 작은 값을 사용
	UF[b] = a;
}

int main()
{
	cin >> V >> E;
	for (int i = 0; i < E; i++)
	{
		int A, B, C;
		cin >> A >> B >> C;
		pq.push({ A, B, C });
	}

	UF.resize(V + 1);
	for (int i = 1; i <= V; i++) UF[i] = i;

	while (cnt < V - 1) //사용한 에지가 V-1개가 되면 break
	{
		int a = pq.top().a;
		int b = pq.top().b;
		int w = pq.top().w;
		pq.pop();

		if (Find(a) == Find(b)) continue; //대표노드가 같음 → 연결할 경우 사이클이 생김
		Union(a, b);

		answer += w;
		cnt++;
	}

	cout << answer;
	return 0;
}