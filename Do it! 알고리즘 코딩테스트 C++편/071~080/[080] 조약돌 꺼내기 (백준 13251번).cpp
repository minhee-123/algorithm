// 문제: https://www.acmicpc.net/problem/13251
#include <iostream>
using namespace std;

int M, K;
int Stone[51];
int Total = 0;

int main()
{
	cin >> M;
	for (int i = 0; i < M; i++)
	{
		cin >> Stone[i];
		Total += Stone[i];
	}
	cin >> K;

	double answer = 0;
	for (int i = 0; i < M; i++)
	{
		if (Stone[i] < K) continue;  // 색이 부족한 경우 제외

		double prob = 1.0;
		int temp_stone = Stone[i];
		int temp_total = Total;

		for (int j = 0; j < K; j++)
		{
			prob *= (double)temp_stone / temp_total;
			temp_stone--;
			temp_total--;
		}

		answer += prob;
	}

	cout << fixed;
	cout.precision(9);
	cout << answer;
	return 0;
}

// 처음에 조합으로 접근했다가 틀렸음
// 조합으로 접근해도 논리적으로 오류를 없을텐데 풀어지지가 않는다...
// 정석은 수학 풀이인 것 같음 (교재도 수학적으로 접근)

// 수학적으로 접근할 때 실수한 부분
// → 각 색의 조약돌이 K개보다 작을 수 있음 (확률에 포함하지 않음)