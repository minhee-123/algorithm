// 집합 표현하기
// 문제: https://www.acmicpc.net/problem/1717

// 유니온파인드는 집합을 만듬 (노드들로 그룹을 만듬)
// 유니온파인드(특히 find 연산)는 그래프를 정돈 + 시간복잡도를 감소 (경로 압축)

#include <iostream>
#include <vector>
using namespace std;

int N, M;
vector<int> parent;

int Find(int c)
{
	if (parent[c] == c) return c;
	else return parent[c] = Find(parent[c]);
}

void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);

	if (a == b) return; //같으면 생략
	if (a > b) swap(a, b);
	parent[b] = a; //대표노드로는 작은값을 사용
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	parent.resize(N + 1); //대표노드 기록
	for (int i = 0; i <= N; i++) parent[i] = i;

	for (int turn = 0; turn < M; turn++)
	{
		int order, a, b;
		cin >> order >> a >> b;

		if (order == 0) Union(a, b);
		else if (order == 1)
		{
			int A = Find(a);
			int B = Find(b);

			if (A == B) cout << "YES" << '\n';
			else cout << "NO" << '\n';
		}
	}
	return 0;
}