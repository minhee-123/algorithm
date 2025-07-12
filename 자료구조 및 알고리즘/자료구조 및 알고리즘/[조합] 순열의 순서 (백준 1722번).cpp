// 문제: https://www.acmicpc.net/problem/1722

// next_permutation 사용할 때 주의할 점 → 순열로 만들 배열이 오름차순으로 정렬되어 있어야 함
// 모든 순열을 구해서 푸는 방법은 메모리 초과 발생 (최악의 경우 20!을 저장함)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, command;
long F[21] = { 0 }; //최대 20!을 저장하기 때문에 long 변수형 사용
long S[21] = { 0 };
bool visit[21];

int main()
{
	cin >> N >> command;
	F[0] = 1;
	for (int i = 1; i <= N; i++) F[i] = F[i - 1] * i; //자릿수에 따른 순열의 수를 이용하는게 문제의 키포인트

	if (command == 1) //K번째 순열 구하기 (시작은 1번째)
	{
		long K;
		cin >> K;

		for (int i = 1; i <= N; i++) //F[0] = 1로 저장해두었기 때문에 N까지 해도 문제없음
		{
			for (int j = 1, cnt = 1; j <= N; j++)
			{
				if (visit[j]) continue;

				if (K <= cnt * F[N - i]) //순열의 시작을 N번째 자리라고 생각 (팩토리얼을 그렇게 저장함)
				{
					K = K - (F[N - i] * (cnt - 1));
					S[i] = j; //실제로 출력할 때 순열의 시작은 1번째 자리니까 → 저장은 1번째부터
					visit[j] = true;
					break;
				}
				else cnt++;
			}
		}

		for (int i = 1; i <= N; i++) cout << S[i] << " ";
	}
	else //주어진 순열이 몇번째 순열인지 구하기
	{
		long K = 1;

		for (int i = 1; i <= N; i++)
		{
			cin >> S[i];
			long cnt = 0;

			for (int j = 1; j < S[i]; j++)
			{
				if (!visit[j]) cnt++;
			}
			K += cnt * F[N - i];
			visit[S[i]] = true;
		}

		cout << K;
	}
	return 0;
}