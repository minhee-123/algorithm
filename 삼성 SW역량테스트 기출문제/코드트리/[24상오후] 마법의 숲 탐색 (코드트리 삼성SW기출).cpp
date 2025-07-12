// 코드트리 삼성 SW 역량테스트 2024 상반기 오후 1번 문제
// https://www.codetree.ai/training-field/frequent-problems/problems/magical-forest-exploration/description?page=1&pageSize=5

// 반례를 맞추느라 시간이 오래 걸렸다!
// (1) 방향 실수를 했었다 ★ 행렬 구분 잘하기 (우좌 이동, 상하 이동 구분), 문제에서 북쪽이 어디인지 남쪽이 어디인지 잘 구분하기 (북남을 반대로 사용해서 오래걸림)
// (2) 변수를 잘못 가져옴 ★ 코드가 워낙 길어지고 pair를 사용하다보니 first랑 second를 잘못 가져올 수도 있으니 주의 (이번에 그래서 오래걸림)


#include <iostream>
#include <vector>
#include <queue>
#include <cstring> //memset 사용
#include <algorithm>
using namespace std;

int R, C, K; //행, 열, 정령의 수
vector<pair<int, int>> pairy; //정령 (출발하는 열, 출구 방향 정보)

int dr[4] = { -1, 0, 1, 0 }; //북, 동, 남, 서
int dc[4] = { 0, 1, 0, -1 }; //상, 우, 하, 좌

int golem[80][80] = { 0 }; //골렘 위치 기록 → 3행 > 1행 (0, 1, 2행은 숲에 진입하기 전)
int golem_exit[80][80] = { 0 };
int BFS_visit[80][80] = { 0 };

int row_sum = 0; //정령들이 최종적으로 위치한 행의 총합

int BFS(int r, int c, int idx)
{
	int answer = r + 1;
	BFS_visit[r][c] = 1;

	queue<pair<int, int>> q;
	q.push({ r + dr[pairy[idx].second], c + dc[pairy[idx].second] });

	while (!q.empty())
	{
		int now_r = q.front().first;
		int now_c = q.front().second;

		answer = max(answer, now_r);
		BFS_visit[now_r][now_c] = 1;

		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int new_r = now_r + dr[i];
			int new_c = now_c + dc[i];

			if (new_r > R + 2 || new_r < 0 || new_c < 0 || new_c > C - 1) continue;
			if (BFS_visit[new_r][new_c] > 0) continue;
			if (golem[new_r][new_c] == 0) continue; 

			if (golem[new_r][new_c] == golem[now_r][now_c]) q.push({ new_r, new_c });
			else
			{
				if (golem_exit[now_r][now_c] > 0) q.push({ new_r, new_c });
			}
		}
	}

	memset(BFS_visit, 0, sizeof(BFS_visit));
	return answer;
}

void Move(int idx) //정령 하나 이동
{
	pair<int, int> g_d = { 2, pairy[idx].first };
	pair<int, int> g_h = { 0, pairy[idx].first };
	pair<int, int> g_r = { 1, pairy[idx].first + 1 };
	pair<int, int> g_l = { 1, pairy[idx].first - 1 };
	pair<int, int> g = { 1, pairy[idx].first };

	bool flag_l = true, flag_r = true, flag_d = true;

	while (1)
	{
 		if (g_l.second == 0) flag_l = false;
		if (g_r.second == C - 1) flag_r = false;
		if (g_d.first == R + 2) flag_d = false;

		//남쪽으로 한 칸 내려감
		if (flag_d && golem[g_d.first + 1][g_d.second] == 0 && golem[g_r.first + 1][g_r.second] == 0 && golem[g_l.first + 1][g_l.second] == 0)
		{
			g_d = { g_d.first + 1, g_d.second };
			g_h = { g_h.first + 1, g_h.second };
			g_r = { g_r.first + 1, g_r.second };
			g_l = { g_l.first + 1, g_l.second };
			g = { g.first + 1, g.second };
		}
		//서쪽 방향으로 회전하면서 내려감
		else if (flag_d && flag_l && golem[g_d.first][g_d.second - 1] == 0 && golem[g_d.first + 1][g_d.second - 1] == 0 && golem[g_l.first][g_l.second - 1] == 0 && golem[g_l.first + 1][g_l.second - 1] == 0 && golem[g_h.first][g_h.second-1] == 0)
		{
			pairy[idx].second = pairy[idx].second - 1;
			if (pairy[idx].second == -1) pairy[idx].second = 3;

			g_d = { g_d.first + 1, g_d.second - 1 };
			g_h = { g_h.first + 1, g_h.second - 1 };
			g_r = { g_r.first + 1, g_r.second - 1 };
			g_l = { g_l.first + 1, g_l.second - 1 };
			g = { g.first + 1, g.second - 1 };
		}
		//동쪽 방향으로 회전하면서 내려감
		else if (flag_d && flag_r && golem[g_d.first][g_d.second + 1] == 0 && golem[g_d.first + 1][g_d.second + 1] == 0 && golem[g_r.first][g_r.second + 1] == 0 && golem[g_r.first + 1][g_r.second + 1] == 0 && golem[g_h.first][g_h.second + 1] == 0)
		{
			pairy[idx].second = pairy[idx].second + 1;
			if (pairy[idx].second == 4) pairy[idx].second = 0;

			g_d = { g_d.first + 1, g_d.second + 1 };
			g_h = { g_h.first + 1, g_h.second + 1 };
			g_r = { g_r.first + 1, g_r.second + 1 };
			g_l = { g_l.first + 1, g_l.second + 1 };
			g = { g.first + 1, g.second + 1 };
		}
		else //움직일 수 없음
		{
			if (g_d.first < 3 || g_h.first < 3 || g_r.first < 3 || g_l.first < 3 || g.first < 3) //골렘의 몸 일부가 숲을 벗어난 상태
			{
				memset(golem, 0, sizeof(golem));
				memset(golem_exit, 0, sizeof(golem_exit));
				break;
			}
			else //골렘의 몸이 전부 숲 안에 있는 경우
			{
				//골렘의 위치 기록
				golem[g_d.first][g_d.second] = idx + 1;
				golem[g_h.first][g_h.second] = idx + 1;
				golem[g_r.first][g_r.second] = idx + 1;
				golem[g_l.first][g_l.second] = idx + 1;
				golem[g.first][g.second] = idx + 1;
				golem_exit[g.first + dr[pairy[idx].second]][g.second + dc[pairy[idx].second]] = idx + 1;

				row_sum += (BFS(g.first, g.second, idx) - 2);
				break;
			}

			flag_l = true, flag_r = true, flag_d = true;
		}
	}
}

int main()
{
	cin >> R >> C >> K;
	for (int i = 0; i < K; i++)
	{
		int temp1, temp2;
		cin >> temp1 >> temp2;
		pairy.push_back({ temp1 - 1, temp2});

		Move(i);
	}
	cout << row_sum;
	return 0;
}