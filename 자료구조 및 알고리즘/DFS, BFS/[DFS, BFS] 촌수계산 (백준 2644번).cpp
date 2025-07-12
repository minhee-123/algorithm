// 촌수계산 (https://www.acmicpc.net/problem/2644)

#include <iostream>
#include <vector>
using namespace std;

int N; //전체 인원 수
int P; //부모 자식간의 관계수
int A, B;
vector<int> family[101];

bool visit[101];
int answer = -1;
void DFS(int index, int end, int cnt)
{
	if (index == end)
	{
		answer = cnt;
		return;
	}

	for (int i = 0; i < family[index].size(); i++)
	{
		int next = family[index][i];
		if (visit[next]) continue;

		visit[next] = true;
		DFS(next, end, cnt + 1);
	}
}

int main()
{
	cin >> N;
	cin >> A >> B;
	cin >> P;

	for (int i = 0; i < P; i++)
	{
		int parent, children;
		cin >> parent >> children;
		family[parent].push_back(children);
		family[children].push_back(parent); //양방향으로 해야 함 (한방향으로 하면 탐색 불가능)
	}

	DFS(A, B, 0);

	cout << answer << '\n';
	return 0;
}