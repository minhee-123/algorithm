// ����: https://www.acmicpc.net/problem/1722
// �ִ� 20! ���� �̿��ϱ� ������ ������ long ���
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// �迭���� 1��° �ڸ��� ���� ������ �ڸ��� ���� (������ ���� ����(��)�� N��° �迭)
long N, command;
long F[21] = { 0 }; // �ڸ����� ���� ����� ��

bool visit[21];

int main()
{
	cin >> N >> command;

	F[0] = 1;
	for (int i = 1; i <= N; i++) F[i] = F[i - 1] * i;

	long k;
	vector<long> permu(N + 1);

	if (command == 1) // k��° ���� ���ϱ�
	{
		cin >> k;

		int index = N;

		while (index >= 2)
		{
			for (int cnt = 1; cnt < 100; cnt++)
			{
				if (k <= F[index - 1] * cnt) // (�����ڸ�-1)���� ���� �� �ִ� ���� ��
				{
					int temp = 0;
					for (int j = 1; j <= N; j++)
					{
						if (visit[j]) continue;
						temp++;

						if (temp == cnt)
						{
							permu[index] = j; // ���� �� �߿��� cnt ���� ä��
							visit[j] = true;
							break;
						}
					}

					k = k - (F[index - 1] * (cnt - 1)); 
					// �� �κ��� Ȯ�������� ������
					// ���� �ڸ��� �������� �� ��° ������ ���ؾ� �ϴ��� ������Ʈ�ϴ� �� ����

					break;
				}
			}
			index--;
		}

		for (int i = 1; i <= N; i++)
		{
			if (!visit[i])
			{
				permu[1] = i;
				break;
			}
		}

		for (int i = N; i >= 1; i--) cout << permu[i] << ' ';
	}

	else if (command == 2) // ������ ������ ���°���� ���߱�
	{
		for (long i = N; i >= 1; i--) cin >> permu[i];
		k = 1;

		for (int i = N; i >= 1; i--)
		{
			int num = permu[i];
			visit[num] = true; // ����� ���� visit ó��

			int cnt = 0;
			for (int j = 1; j < num; j++)
			{
				if (visit[j]) continue;
				cnt++; // ������� ���� ���� ���� ���� üũ
			}

			k += (cnt * F[i - 1]); // ������� ���� ���� ���� ���� * (�����ڸ�-1) ����� ���� ����
		}

		cout << k;
	}

	return 0;
}