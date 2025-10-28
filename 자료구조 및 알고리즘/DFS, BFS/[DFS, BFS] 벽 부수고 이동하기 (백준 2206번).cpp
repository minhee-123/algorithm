// ����: https://www.acmicpc.net/problem/2206
#include <iostream>
#include <string>
#include <queue>
using namespace std;

// �ִܰŸ� �̵� ���� + �� �ϳ� �μŵ� �� (��ֹ� �ϳ� ���� ����)
int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

int N, M;
int Map[1000][1000]; // (0, 0)�� (N-1, M-1)�� �׻� 0 �� ��ֹ� ����
bool visit[1000][1000][2]; // 0�� ���� �μ� ����, 1�� ���� ���� �μ��� ���� ���� (���� �μ� ��ȸ�� 1)
int answer = -1;

struct inform
{
	int R;
	int C;
	int moveCNT;
	int chance;
};

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		string temp;
		cin >> temp;
		for (int j = 0; j < M; j++)
		{
			int num = temp[j] - '0';
			Map[i][j] = num;
		}
	}

	queue<inform> que;
	que.push({ 0, 0, 1, 1 }); // �����ϴ� ĭ�� ������ ĭ�� �����ؼ� count
	visit[0][0][1] = true; // ���� �ϳ����� �μ� �� ����

	while (!que.empty())
	{
		int R = que.front().R;
		int C = que.front().C;
		int moveCNT = que.front().moveCNT;
		int chance = que.front().chance; // ���� �μ� �� �ִ� ��ȸ

		que.pop();

		if (R == N - 1 && C == M - 1)
		{
			answer = moveCNT;
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			int NR = R + dr[i];
			int NC = C + dc[i];
			int Nchance = chance;

			if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
			if (Map[NR][NC] == 1)
			{
				if (Nchance == 0) continue; // �� �μ��� ��ȸ�� ���� ����
				else Nchance--; // �� �μ��� ��ȸ�� �ִ� ���� (���� �μ��� ����) 
			}
			if (visit[NR][NC][Nchance]) continue; // ���� ������ �ִܰŸ��� ����
			// �� �μ��⸦ ������ visit üũ �� ���� �μ� ��� ���� �μ� ���¿� �����ϱ� ���� (������ visit�� üũ�ϸ� ���� ���¸� �ߺ� Ž��)

			visit[NR][NC][Nchance] = true;
			que.push({ NR, NC, moveCNT + 1, Nchance });
		}
	}

	cout << answer;
	return 0;
}

/*
�ʹ� �������� Ǯ� ������ ���� �� ���ƿ��� ����
���̾��� �Ǽ��� �ʹ� ���� ��
������ ������ �ٽ�! ������ �ϳ��� �� ó���ϴ� �� �ٽ�!
*/