// 문제: https://www.acmicpc.net/problem/20040
#include <iostream>
#include <vector>
using namespace std;

// 유니온 파인드에서 사이클을 판별할 수 있다
// ★ 사이클의 판별 원리: 이미 같은 집합에 속해있는 두 노드를 다시 연결하려 하는가?
// ★ 이미 같은 집합에 속해있는 두 노드를 연결한다면 사이클이 생성됨

// 이때 생각할 점은(문제에서 그렇게 내는 경우는 없겠지만) 두 노드가 다른 경로로 연결되어 있는데 두 노드 사이를 새롭게 연결할 때 사이클이 생긴다는 것
// → 두 노드가 이미 직접 연결되어 있는데 또 연결한다고 사이클이 생기지는 않음 (해당 부분은 보통 문제 조건에서 막을 것)

int N, M;
int UF[500000];

int Find(int c)
{
	if (UF[c] == c) return c;
	else return UF[c] = Find(UF[c]);
}

void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);

	if (a == b) return;
	else if (a > b) swap(a, b);
	UF[b] = a;
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++) UF[i] = i;

	for (int i = 1; i <= M; i++)
	{
		int A, B; cin >> A >> B;

		if (Find(A) == Find(B)) // 이미 집합인데 또 묶으려고 할 경우 → 사이클 생성
		{
			cout << i;
			return 0; // 종료
		}
		else Union(A, B);
	}

	cout << 0;
	return 0;
}