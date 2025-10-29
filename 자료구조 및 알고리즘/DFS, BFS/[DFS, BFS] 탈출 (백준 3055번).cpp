// ����: https://www.acmicpc.net/problem/3055
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

// ����ġ�� ���� �ð��� ���� �� ������ ĭ���� �̵��� �� ���ٴ� ����
// �� �ش� ������ �������� �� ���� Ǯ���� �� ����
// �� ���� ������ �� ����
// �� ���̶� ����ġ�� ���ÿ� �̵��ϱ� ������ ���� ���Ŀ��� ���� ����ġ�� �̵��� �� ����
// �� �� ������ ����� ������ �ȵǴµ� �� �����ִ� ����? (���� �ð��̶�°� �׳� ���� �̵��� ���ѵ�)

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

int N, M;
int Map[50][50];
// 0: �������
// 1: ��
// 2: ��
// 3: ����� �� (������)

int DR, DC; // ����� �� ��ġ
int SR, SC; // ����ġ�� ��ġ
vector<pair<int, int>> water; // ���� ��ġ

void Input()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		string temp;
		cin >> temp;

		for (int j = 0; j < M; j++)
		{
			char tp = temp[j];
			if (tp == '.') Map[i][j] = 0;
			else if (tp == '*')
			{
				Map[i][j] = 1;
				water.push_back({ i, j });
			}
			else if (tp == 'X') Map[i][j] = 2;
			else if (tp == 'D')
			{
				Map[i][j] = 3;
				DR = i;
				DC = j;
			}
			else if (tp == 'S')
			{
				SR = i;
				SC = j;
			}
		}
	}
}

struct inform
{
	int R;
	int C;
	int turn; // ���� ���° ������ (���� �����ϸ� �� Ȯ��)
};
bool visit[50][50];

int main()
{
	Input();

	queue<inform> que;
	que.push({ SR, SC, 0 });

	visit[SR][SC] = true;
	int nowTurn = -1;

	while (!que.empty())
	{
		int R = que.front().R; // ����ġ�� ���� ��ġ R
		int C = que.front().C; // ����ġ�� ���� ��ġ C
		int turn = que.front().turn;

		que.pop();

		if (R == DR && C == DC) // ����� ���� Ȯ��
		{
			std::cout << turn;
			return 0;
		}
		
		if (turn > nowTurn) // �� Ȯ�� ����
		{
			int water_size = water.size();
			for (int i = 0; i < water_size; i++)
			{
				int wr = water[i].first;
				int wc = water[i].second;

				for (int j = 0; j < 4; j++)
				{
					int nwr = wr + dr[j];
					int nwc = wc + dc[j];

					if (nwr < 0 || nwr >= N || nwc < 0 || nwc >= M) continue;
					if (Map[nwr][nwc] >= 1) continue;

					Map[nwr][nwc] = 1;
					water.push_back({ nwr, nwc });
				}
			}
			nowTurn = turn;
		}

		for (int i = 0; i < 4; i++)
		{
			int NR = R + dr[i];
			int NC = C + dc[i];

			if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
			if (visit[NR][NC]) continue;
			if (Map[NR][NC] == 1 || Map[NR][NC] == 2) continue;

			visit[NR][NC] = true;
			que.push({ NR, NC, turn + 1 });
		}
	}
	std::cout << "KAKTUS";
	return 0;
}