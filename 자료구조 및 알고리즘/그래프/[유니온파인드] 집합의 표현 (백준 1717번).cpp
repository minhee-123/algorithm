// 문제: https://www.acmicpc.net/problem/1717
// 집합, 합집합의 개념이 나오면 → 유니온파인드

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<int> A;

int Find(int c) //특정 노드가 속한 집합의 대표 노드를 반환
{
	if (A[c] == c) return c;
	else return A[c] = Find(A[c]); //끝까지 탐색 후 돌아오면서 탐색한 모든 노드의 대표값을 동일한 대표 노드로 바꿈

}

void Union(int a, int b) //두 노드를 같은 집합으로 묶어줌 (가장 작은 수가 대표 노드)
{
	a = Find(a);
	b = Find(b);

	if (a != b) A[b] = a;
}

int main()
{
	ios::sync_with_stdio;
	cin.tie(NULL);
	cout.tie(NULL); //이걸 써야지 시간초과가 발생하지 않는 문제

	cin >> N >> M;

	A = vector<int>(N + 1, 0);
	for (int i = 1; i <= N; i++) A[i] = i; //자기자신이 대표 노드 (각 노드가 각각의 집합을 이룸)

	for (int i = 0; i < M; i++)
	{
		int command;
		cin >> command;

		int a, b;
		cin >> a >> b;
		if (a > b) swap(a, b);

		if (command == 0)
		{
			Union(a, b);
		}
		else //command == 1
		{
			int a_rp = Find(a);
			int b_rp = Find(b);

			if (a_rp == b_rp) cout << "YES" << '\n';
			else cout << "NO" << '\n';
		}
	}
	return 0;
}