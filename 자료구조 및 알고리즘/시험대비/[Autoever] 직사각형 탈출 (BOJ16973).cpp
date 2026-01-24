// 문제: https://www.acmicpc.net/problem/16973
// 알고리즘: 그래프
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N, M, H, W;
int Map[1001][1001];
int visit[1001][1001];

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

struct BOX
{
	int SR; // 가장 왼쪽 위칸 ROW
	int SC; // 가장 왼쪽 위칸 COL
	int ER; // 가장 오른쪽 아래칸 ROW
	int EC; // 가장 오른쪽 아래칸 COL
};
int SSR, SSC, EER, EEC;

bool check_wall(int SR, int SC, int ER, int EC)
{	
	for (int C = SC; C <= EC; C++)
	{
		if (Map[SR][C] == 1) return true;
		if (Map[ER][C] == 1) return true;
	}
	for (int R = SR; R <= ER; R++)
	{
		if (Map[R][SC] == 1) return true;
		if (Map[R][EC] == 1) return true;
	}
	return false;
}

int main()
{
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++) cin >> Map[i][j];
	}
	cin >> H >> W >> SSR >> SSC >> EER >> EEC;

	queue<BOX> que;
	que.push({ SSR, SSC, SSR + H - 1, SSC + W - 1});

	memset(visit, -1, sizeof(visit));
	visit[SSR][SSC] = 0;

	while (!que.empty())
	{
		int SR = que.front().SR;
		int SC = que.front().SC;
		int ER = que.front().ER;
		int EC = que.front().EC;
		que.pop();

		bool finish = false;

		for (int i = 0; i < 4; i++)
		{
			int NSR = SR + dr[i];
			int NSC = SC + dc[i];
			int NER = ER + dr[i];
			int NEC = EC + dc[i];

			if (NSR <= 0 || NSR > N || NSC <= 0 || NSC > M) continue;
			if (NER <= 0 || NER > N || NEC <= 0 || NEC > M) continue;
			if (visit[NSR][NSC] >= 0) continue;
			if (check_wall(NSR, NSC, NER, NEC)) continue;

			visit[NSR][NSC] = visit[SR][SC] + 1;
			que.push({ NSR, NSC, NER, NEC });

			if (NSR == EER && NSC == EEC)
			{
				finish = true;
				break;
			}
		}
		if (finish) break;
	}

	cout << visit[EER][EEC];
	return 0;
}

// 현재는 시간초과 문제가 발생하지 않지만
// 만약 N, M, H, W의 범위가 커서 check_wall을 할 때 시간초과가 발생할 수 있다면
// → 2차원 누적 합을 이용하면 됨
// → Sum[i][j]를 (1,1)부터 (i,j)까지의 벽(1)의 개수 합으로 만듬
// → 직사각형 내부(SR,SC ~ ER, EC)의 벽의 개수 = Sum[ER][EC] - Sum[SR-1][EC] - Sum[ER][SC-1] + Sum[SR-1][SC-1]