// 문제: https://www.acmicpc.net/problem/1722
// 최대 20! 값을 이용하기 때문에 변수형 long 사용
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 배열에서 1번째 자리는 가장 오른쪽 자리로 생각 (순열의 가장 왼쪽(앞)이 N번째 배열)
long N, command;
long F[21] = { 0 }; // 자릿수에 따른 경우의 수

bool visit[21];

int main()
{
	cin >> N >> command;

	F[0] = 1;
	for (int i = 1; i <= N; i++) F[i] = F[i - 1] * i;

	long k;
	vector<long> permu(N + 1);

	if (command == 1) // k번째 순열 구하기
	{
		cin >> k;

		int index = N;

		while (index >= 2)
		{
			for (int cnt = 1; cnt < 100; cnt++)
			{
				if (k <= F[index - 1] * cnt) // (현재자리-1)에서 만들 수 있는 수랑 비교
				{
					int temp = 0;
					for (int j = 1; j <= N; j++)
					{
						if (visit[j]) continue;
						temp++;

						if (temp == cnt)
						{
							permu[index] = j; // 남은 수 중에서 cnt 수를 채움
							visit[j] = true;
							break;
						}
					}

					k = k - (F[index - 1] * (cnt - 1)); 
					// 이 부분은 확실하지는 않은데
					// 남은 자릿수 순열에서 몇 번째 순열을 구해야 하는지 업데이트하는 것 같음

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

	else if (command == 2) // 임의의 순열이 몇번째인지 맞추기
	{
		for (long i = N; i >= 1; i--) cin >> permu[i];
		k = 1;

		for (int i = N; i >= 1; i--)
		{
			int num = permu[i];
			visit[num] = true; // 사용한 수는 visit 처리

			int cnt = 0;
			for (int j = 1; j < num; j++)
			{
				if (visit[j]) continue;
				cnt++; // 사용하지 않은 작은 수의 개수 체크
			}

			k += (cnt * F[i - 1]); // 사용하지 않은 작은 수의 개수 * (현재자리-1) 경우의 수를 더함
		}

		cout << k;
	}

	return 0;
}