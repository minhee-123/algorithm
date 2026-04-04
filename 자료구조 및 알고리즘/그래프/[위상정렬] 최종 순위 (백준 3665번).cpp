// 문제: https://www.acmicpc.net/problem/3665
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

// 작년 순위와 작년에 비해 상대적 순위가 바뀐 팀의 목록만 공개 (순위가 바뀐 애들만)
// 본부에서 발표한 정보를 가지고 확실한 순위를 만들지 못하거나 잘못된 정보인 경우도 있음

int T, N, M;
vector<int> old_ranking;
vector<int> new_ranking_inform[501];

int indegree[501];
bool reverse_check[501][501];

void Ranking()
{
	// Input
	old_ranking.clear();
	for (int i = 0; i <= 500; i++) new_ranking_inform[i].clear();
	memset(indegree, 0, sizeof(indegree));
	memset(reverse_check, false, sizeof(reverse_check));

	cin >> N;
	old_ranking.resize(N + 1);
	for (int i = 1; i <= N; i++) cin >> old_ranking[i];

	cin >> M;
	for (int i = 0; i < M; i++)
	{
		// 해당 부분을 실수함
		// 입력으로 들어오는 쌍이 작년과 달리 순위가 뒤집혔다는 의미지 승패를 의미하는 것은 아님
		int A, B; cin >> A >> B;
		reverse_check[A][B] = true;
		reverse_check[B][A] = true; // 올해는 승패가 바뀜
	}

	for (int i = 1; i <= N - 1; i++)
	{
		int win = old_ranking[i];
		for (int j = i + 1; j <= N; j++)
		{
			int lose = old_ranking[j];

			if (reverse_check[win][lose]) // 승패가 바뀐 경우
			{
				new_ranking_inform[lose].push_back(win);
				indegree[win]++; // 올해는 win 번호가 lose한테 졌음
			}
			else
			{
				new_ranking_inform[win].push_back(lose);
				indegree[lose]++; // 올해도 lose 번호가 win한테 졌음
			}
		}
	}

	// Ranking
	queue<int> que;

	// 큐에 들어가있는 번호가 2개 이상일 경우 정확한 순위를 알 수 없음 = ?
	// 최종적인 answer에 모든 번호가 있지 않다면 = IMPOSSIBLE

	for (int i = 1; i <= N; i++)
	{
		if (indegree[i] == 0) que.push(i);
		if (que.size() > 1) // 순위를 알 수 없음
		{
			cout << "?\n";
			return; // 종료
		}
	}

	vector<int> answer;
	bool wrong_inform = false;

	while (!que.empty())
	{
		int now = que.front();
		que.pop();

		answer.push_back(now);
		for (int i = 0; i < new_ranking_inform[now].size(); i++)
		{
			int next = new_ranking_inform[now][i];
			indegree[next]--;

			if (indegree[next] == 0)
			{
				if (que.size() >= 1) // 순위를 정할 수 없음
				{
					cout << "?\n";
					return; // 종료
				}
				else que.push(next);
			}
			else if (indegree[next] < 0) // 데이터가 잘못 되었음
			{
				wrong_inform = true;
				break;
			}
		}
		if (wrong_inform) break;
	}

	if (answer.size() != N) cout << "IMPOSSIBLE\n"; // 데이터가 잘못된 경우 answer에는 n개의 답이 있을 수 없음
	else
	{
		for (int i = 0; i < N; i++) cout << answer[i] << ' ';
		cout << '\n';
	}
}

int main()
{
	cin >> T;
	for (int i = 0; i < T; i++) Ranking();
	return 0;
}