// ����: https://www.acmicpc.net/problem/9019
#include <iostream>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

// ������ Ǯ���� ���� �߿��� ������ ������ DFS�� Ǯ���� �� ���Ƽ� DFS�� ����
// BUT �ִܰŸ��� ã�� ���̱� ������ ������ BFS�� Ǫ�� �� ���ٰ� �� (�ڲ� ������ �߸��ϳ�!)
// �� ���� Ǫ�� ���� �� ��ã�ƾ� �� �� ���� ��!!

/* ���ｺ���� ���� CHECK */
// �Լ��� ���ڷ� �迭�� ����ϸ� �� ������ �״�� ������ (�����ؼ� ����ϰ� �ʹٸ� ���� ����)
// �Լ��� ���ڷ� ���͸� ����ϸ� �� �����ؼ� ������

int T;
bool visit[10000];

struct inform
{
	int nowA;
	string path;
};

void Solution()
{
	int A, B;
	cin >> A >> B;
	memset(visit, false, sizeof(visit)); // Ž�� ��θ� �����ϱ� ���� �湮�ߴ� ���� check (��湮 ����)

	queue<inform> que;
	que.push({ A, "" });
	visit[A] = true;

	string answer = "";

	while (!que.empty())
	{
		int nowA = que.front().nowA;
		string nowP = que.front().path;

		que.pop();
		if (nowA == B)
		{
			answer = nowP;
			break;
		}

		for (int k = 0; k < 4; k++)
		{
			int nextA = nowA;
			string nextP = nowP;

			if (k == 0)
			{
				nextA *= 2;
				if (nextA > 9999) nextA %= 10000;

				nextP += "D";
			}
			else if (k == 1)
			{
				// n���� 1�� �� ����� �������Ϳ� ����
				// �̶� n�� 0���� 9999���� ������ �� �����ϱ�
				// 1�� ���� �� n�� ������ �Ǹ� 9999�� �����϶�� ���� (���� ���� ���� 0�̸� 9999�� �ٲ��)
				nextA -= 1;
				if (nextA < 0) nextA = 9999;

				nextP += "S";
			}
			else if (k == 2)
			{
				int tempA[4];
				tempA[0] = nextA / 1000; nextA = nextA % 1000;
				tempA[1] = nextA / 100; nextA = nextA % 100;
				tempA[2] = nextA / 10; nextA = nextA % 10;
				tempA[3] = nextA;

				int temp = tempA[0];
				tempA[0] = tempA[1];
				tempA[1] = tempA[2];
				tempA[2] = tempA[3];
				tempA[3] = temp;
				
				/* ���� �迭�� �� ���� �Ʒ��� ���� ���� �������ε� ���� �� ���� */
				// nextA = (nextA % 1000) * 10 + (nextA / 1000);

				nextA = (tempA[0] * 1000) + (tempA[1] * 100) + (tempA[2] * 10) + tempA[3];
				nextP += "L";
			}
			else
			{
				int tempA[4];
				tempA[0] = nextA / 1000; nextA = nextA % 1000;
				tempA[1] = nextA / 100; nextA = nextA % 100;
				tempA[2] = nextA / 10; nextA = nextA % 10;
				tempA[3] = nextA;

				int temp = tempA[3];
				tempA[3] = tempA[2];
				tempA[2] = tempA[1];
				tempA[1] = tempA[0];
				tempA[0] = temp;

				/* ���� �迭�� �� ���� �Ʒ��� ���� ���� �������ε� ���� �� ���� */
				// nextA = (nextA % 10) * 1000 + (nextA / 10);

				nextA = (tempA[0] * 1000) + (tempA[1] * 100) + (tempA[2] * 10) + tempA[3];
				nextP += "R";
			}

			if (visit[nextA]) continue; // �̹� �湮�� ������ ��� pass
			
			visit[nextA] = true;
			que.push({ nextA, nextP });
		}
	}

	cout << answer << '\n';
}

int main()
{
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		Solution();
	}
	return 0;
}