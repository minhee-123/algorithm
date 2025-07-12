// 문제: https://www.acmicpc.net/problem/1197
// 최소 스패닝 트리 == 최소 신장 트리

// 최소 신장 트리: 그래프에서 모든 노드를 연결할 때 사용된 에지들의 가중치의 합을 최소로 하는 트리
// 사이클을 포함하지 않음
// N개의 노드가 있으면 최소신장 트리를 구성하는 에지의 개수는 항상 N-1개
// → 에지 리스트 (에지를 기준으로 함) / 유니온파인드 활용 (사이클을 형성하지 않도록 함)

// 사이클을 형성하지 않고 트리를 구성하는 에지의 개수가 N-1개가 되면 → 모든 노드를 연결하게 됨
// 집합으로 묶는다 → 무방향(양방향) 그래프라고 생각해야 할 듯

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge
{
	int weight;
	int node1;
	int node2;
};

int V, E;
vector<edge> A; //주어진 정보 저장
vector<int> UF; //대표 노드 저장

int edge_num = 0;
int weight_sum = 0;

int Find(int c)
{
	if (UF[c] == c) return c;
	else return UF[c] = Find(UF[c]);
}

void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);

	if (a != b) UF[b] = a;
}

bool comp(edge a, edge b)
{
	if (a.weight != b.weight) return a.weight < b.weight;
	else
	{
		if (a.node1 != b.node1) return a.node1 < b.node1;
		else return a.node2 < b.node2;
	}
}

int main()
{
	cin >> V >> E;
	A = vector<edge> (E, {0, 0, 0}); //에지 리스트 (최소신장트리는 에지를 위주로 알고리즘이 진행됨)
	UF = vector<int>(V + 1, 0);

	for (int i = 0; i < E; i++) cin >> A[i].node1 >> A[i].node2 >> A[i].weight;
	for (int i = 1; i <= V; i++) UF[i] = i;

	sort(A.begin(), A.end(), comp); //오름차순
	int index = 0;
	while (1)
	{
		int node1 = A[index].node1; int UF_1 = Find(node1);
		int node2 = A[index].node2; int UF_2 = Find(node2);

		if (UF_1 == UF_2) index++;
		else //UF_1 != UF_2
		{
			Union(node1, node2);
			weight_sum += A[index].weight;
			index++;
			edge_num++;
		}

		if (edge_num == V - 1) break;
	}

	cout << weight_sum << '\n';
	return 0;
}

// edge 구조체에 operator를 넣어두고
// 우선순위 큐에 값들을 저장해서 가중치를 오름차순으로 꺼내도 됨