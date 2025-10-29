// ����: https://www.acmicpc.net/workbook/view/1833

// BFS�� Ǯ �� �ִ� �� ���� �ѵ� ����ȭ�ϰ� �;
// ���ͽ�Ʈ�� �����غ� (�߰��� �Ǽ��� ���� �ؼ� ���� �ɸ�)

/* ������� ���� �ɷȴ�! */
/*
(1) visit �迭�� 3�������� �ٷ��� �Ѵ�
    �� ���⿡ ���� cnt�� �޶���
	�� ���� ��Ʈ�� ���� �� �ִµ� �����ִ� cnt�� �޶����� ���⵵ visit ó���ؾ� ��
(2) �ٵ� ���ʿ� visit�� ���� �ʴ�
	�� ���ͽ�Ʈ�� �˰��򿡼� visit �迭�� ������� �ʴ´�
	�� dist �迭�� ����ؾ� �� (��� ���� INF�� �ʱ�ȭ / push�Ϸ��� ���� �� ������ üũ)
(3) ������ �߸� �ʱ�ȭ�ߴ�
	�� answer�� ó���� 200���� �ʱ�ȭ�ߴµ� �ִ밪�� 200�� �ƴϴ�...
	�� �ּ�/�ִ븦 ã�� �� �ʱ�ȭ�� �ش������� ����
*/

#include <iostream>
#include <queue>
using namespace std;

int N, M;
int dr[4] = { 0, 0, 1, -1 }; // �� �� �� ��
int dc[4] = { 1, -1, 0, 0 };
int Map[100][100]; 

int startR, startC, startDir;
int targetR, targetC, targetDir;

void Input()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) cin >> Map[i][j];
	}

	int tempR, tempC, tempDir;

	cin >> tempR >> tempC >> tempDir;
	startR = tempR - 1;
	startC = tempC - 1;
	startDir = tempDir - 1;

	cin >> tempR >> tempC >> tempDir;
	targetR = tempR - 1;
	targetC = tempC - 1;
	targetDir = tempDir - 1;
}

// ���� ���⿡�� Ÿ�� �������� �ٲٴ� �� �ʿ��� ����� ��
int turn_cnt(int now_dir, int target_dir)
{
	if (now_dir == target_dir) return 0;
	else
	{
		// ��(0), ��(1), ��(2), ��(3)
		if (now_dir == 0)
		{
			if (target_dir >= 2) return 1;
			else return 2;
		}
		else if (now_dir == 1)
		{
			if (target_dir >= 2) return 1;
			else return 2;
		}
		else if (now_dir == 2)
		{
			if (target_dir <= 1) return 1;
			else return 2;
		}
		else // now_dir == 3
		{
			if (target_dir <= 1) return 1;
			else return 2;
		}
	}
}

struct inform
{
	int R;
	int C;
	int dir;
	int cnt;

	bool operator()(inform A, inform B)
	{
		// cnt�� ���� ������ ����
		return A.cnt > B.cnt; // A.cnt�� Ŭ ��� �� ���� �켱������ ���� (��������)
	}
};
int answer = 1000000;
int dist[100][100][4];
// � �������� �����ߴ����� �߿�
// �� dist�� 3�������� �����ؾ� ��
// �� � ������ ���� �����ߴ����� ���� cnt�� �޶����� ���� (���� ��Ʈ�� ���� ���� ������ ������ cnt�� �޶���!!)

void Solution()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			for (int k = 0; k < 4; k++) dist[i][j][k] = 1000000;
		}
	}

	priority_queue<inform, vector<inform>, inform> pq;
	pq.push({ startR, startC, startDir, 0 });

	dist[startR][startC][startDir] = 0;

	/* �ִܰŸ��� Ȯ���� �����ϱ� ���ؼ� */
	// �� �켱���� ť ����
	// �� cnt�� ���� �ͺ��� ������ ������ (���ͽ�Ʈ�� ����)
	while (!pq.empty())
	{
		int R = pq.top().R;
		int C = pq.top().C;
		int dir = pq.top().dir;
		int cnt = pq.top().cnt;

		pq.pop();

		if (R == targetR && C == targetC)
		{
			int temp_answer = cnt + turn_cnt(dir, targetDir);
			if (temp_answer < answer) answer = temp_answer;
		}
		if (cnt > dist[R][C][dir]) continue; // �̹� �� ���� cnt�� ó���ߴٸ� pass

		for (int i = 0; i < 4; i++) // �ش� �������� 2ĭ, 3ĭ �̵��ϴ� �͵� ���
		{
			int NR = R + dr[i];
			int NC = C + dc[i];
			
			if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
			if (Map[NR][NC] == 1) continue;
			int Ncnt = cnt + 1 + turn_cnt(dir, i);
			if (Ncnt < dist[NR][NC][i])
			{
				dist[NR][NC][i] = Ncnt;
				pq.push({ NR, NC, i, Ncnt });
			}

			// 2ĭ �̵��ϴ� ���
			NR += dr[i];
			NC += dc[i];
			if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
			if (Map[NR][NC] == 1) continue;
			if (Ncnt < dist[NR][NC][i])
			{
				dist[NR][NC][i] = Ncnt;
				pq.push({ NR, NC, i, Ncnt });
			}

			// 3ĭ �̵��ϴ� ���
			NR += dr[i];
			NC += dc[i];
			if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
			if (Map[NR][NC] == 1) continue;
			if (Ncnt < dist[NR][NC][i])
			{
				dist[NR][NC][i] = Ncnt;
				pq.push({ NR, NC, i, Ncnt });
			}
		}
	}
	cout << answer;
}

int main()
{
	Input();
	Solution();
	return 0;
}