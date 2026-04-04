// 문제: https://www.acmicpc.net/problem/16562
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, K;
vector<pair<int, int>> A; // (cost, index)
int UF[10001];
int UF_cnt[10001]; // UF_cnt[i] = 대표노드 i 집합의 요소 수

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

	UF_cnt[a] += UF_cnt[b];
	UF_cnt[b] = 0;
}

int main()
{
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++)
	{
		int cost; cin >> cost;
		A.push_back({ cost, i });
	}
	sort(A.begin(), A.end()); // cost 오름차순

	for (int i = 0; i <= N; i++)
	{
		UF[i] = i;
		UF_cnt[i] = 1;
	}
	for (int i = 0; i < M; i++)
	{
		int a, b; cin >> a >> b;
		Union(a, b); // a와 b를 하나로 묶음
	}

	// 친구 비용 지불
	int now_cost = 0;
	for (int i = 0; i < N; i++)
	{
		int next_cost = A[i].first;
		int next = A[i].second;

		if (Find(0) == Find(next)) continue; // 이미 친구(친구의 친구)

		if (now_cost + next_cost > K) break; // 돈이 없음
		else
		{
			now_cost += next_cost;
			Union(0, next);

			if (UF_cnt[0] == N + 1) break; // 모든 학생과 친구가 됨
		}
	}

	if (UF_cnt[0] == N + 1) cout << now_cost;
	else cout << "Oh no";
	return 0;
}

/* 디버깅 수행 */
// UF를 적용한 그리디(최소 비용 순서로 따짐)로 풀었는데
// 아니다 이거 맞다! 최소 비용 순서대로 사용하면 되는데, 친구의 친구는 제외해야 됨! (이걸 안해서 처음에 틀렸음)