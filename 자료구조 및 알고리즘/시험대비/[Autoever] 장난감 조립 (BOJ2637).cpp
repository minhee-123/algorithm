// 문제: https://www.acmicpc.net/problem/2637
// 알고리즘: 트리? 그래프? + DP (위상정렬로 풀었음)
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N; //1부터 N-1까지 기본 부품이나 중간부품, N은 완제품
int M;
vector<pair<int, int>> part[101]; // 필요한 부품, 부품의 개수

vector<bool> mid_part; // false인 경우 기본 부품, true인 경우 중간or완제품
vector<int> indegree; // 진입차수
vector<int> part_cnt; // 사용된 부품 개수

int main()
{
	cin >> N >> M;
	mid_part.resize(N + 1, false);
	indegree.resize(N + 1, 0);
	part_cnt.resize(N + 1, 0);

	for (int i = 0; i < M; i++)
	{
		int X, Y, K;
		cin >> X >> Y >> K;

		part[X].push_back({ Y, K }); // X를 만드는 데 Y를 K개 사용
		mid_part[X] = true;
		indegree[Y]++;
	}

	queue<int> que;
	que.push(N); // 시작은 N, indegree[N] = 0
	part_cnt[N] = 1; // 완제품 1개를 만들고자 함

	while (!que.empty())
	{
		int now = que.front();
		int now_cnt = part_cnt[now];
		que.pop();

		for (int i = 0; i < part[now].size(); i++)
		{
			int next = part[now][i].first;
			int next_cnt = part[now][i].second;

			part_cnt[next] += next_cnt * now_cnt; // now를 만들기 위해 (now의 개수) * (now 1개 만드는데 필요한 next 개수)를 누적
			indegree[next]--;

			if (indegree[next] == 0) que.push(next);
		}
	}

	for (int i = 1; i <= N; i++)
	{
		if (!mid_part[i]) cout << i << ' ' << part_cnt[i] << '\n';
	}
	return 0;
}
