// 문제: https://www.acmicpc.net/problem/1068
#include <iostream>
#include <vector>
using namespace std;

// 처음에 놓쳤던 부분
// 1. 루트노드가 삭제되는 노드인 경우
// 2. 리프노드가 삭제되는 경우 → 리프노드의 부모노드가 리프노드가 됨

vector<vector<int>> tree;
vector<bool> visit;

int root; //루트노드 번호
int delet; //삭제되는 노드 번호
int answer = 0;

void DFS(int now)
{
	if (visit[now]) return;
	visit[now] = true;
	
	int cnt = 0;
	for (int i = 0; i < tree[now].size(); i++)
	{
		int next = tree[now][i];
		if (visit[next]) continue;
		
		cnt++; //자식 노드가 있다면 cnt++
		DFS(next);
	}

	if (cnt == 0) answer++; //자식 노드가 없는 경우
}

int main()
{
	int N;
	cin >> N;

	tree.resize(N);
	visit.resize(N);

	for (int i = 0; i < N; i++)
	{
		int parent;
		cin >> parent;

		if (parent == -1) root = i;
		else tree[parent].push_back(i); //리프노드를 찾기 쉽게 한방향 그래프로 만듬
	}

	cin >> delet;
	visit[delet] = true;

	DFS(root);
	cout << answer;

	return 0;
}