// ����: https://www.acmicpc.net/problem/1987

// ��Ʈ����ũ ���
// �� set�̳� �迭�� ����� ��� ť�� �ʹ� ���� ���� �׿��� �޸� ����
// �� ��Ʈ����ũ ����: https://kimtaesoo99.tistory.com/121

// �ƻԻ� �׷��� ���ʿ� DFS�� �����ؾ� �ϴ� ���̾���
// �� BFS�� �ִܰŸ��� Ưȭ
// �� �ش� ������ �ִ�Ÿ��� ���ϴ� ���̱� ������ DFS + ��Ʈ��ŷ ������ �ʿ�

// �� BFS�� DFS �� ��� �����ؾ� �ϴ��� �� ���� (�ִܰŸ� vs �ִ�Ÿ� or ��Ž)

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

int Map[20][20];
int N, M;

int max_cnt = 1;

void DFS(int R, int C, int visit, int cnt)
{
	if (cnt > max_cnt) max_cnt = cnt;

	for (int i = 0; i < 4; i++)
	{
		int NR = R + dr[i];
		int NC = C + dc[i];
		int value = Map[NR][NC];

		if (NR < 0 || NR >= N || NC < 0 || NC >= M) continue;
		if (visit & (1 << value)) continue; // value ��ġ�� ��Ʈ�� �����ִ��� Ȯ��

		int Nvisit = visit;
		Nvisit |= (1 << value); // value ��ġ�� ��Ʈ check

		DFS(NR, NC, Nvisit, cnt + 1);
	}
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		string temp;
		cin >> temp;
		for (int j = 0; j < M; j++) Map[i][j] = ((int)temp[j]) - 65; // ���ĺ��� ���ڷ� ġȯ (0���� 25)
	}

	int temp_visit = 0;
	temp_visit |= (1 << Map[0][0]); // Map[0][0]��° ��Ʈ check

	DFS(0, 0, temp_visit, 1);

	cout << max_cnt;
	return 0;
}