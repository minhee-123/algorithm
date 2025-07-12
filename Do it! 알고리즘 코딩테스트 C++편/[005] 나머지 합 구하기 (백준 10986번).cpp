// 문제: https://www.acmicpc.net/problem/10986

// (A + B) % C == ((A % C) + (B % C)) % C 수식을 이용해서 품

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M;
	cin >> N >> M;

	vector<long> S(N, 0); //0으로 채운 N개의 배열 생성 (합 배열)
	vector<long> Cnt(M, 0); //0으로 채운 M개의 배열 생성 (같은 나머지 개수를 count)

	cin >> S[0];
	for (int i = 1; i < N; i++)
	{
		long temp;
		cin >> temp;
		S[i] = S[i - 1] + temp;
	}

	long answer = 0; // 큰 수를 다루니까 long 사용 (오버플로우 예방)
	for (int i = 0; i < N; i++)
	{
		long temp = S[i] % M;
		
		if (temp == 0) answer++;
		Cnt[temp]++;
	}

	for (int i = 0; i < M; i++)
	{
		answer += (Cnt[i] * (Cnt[i] - 1)) / 2;
	}
	cout << answer << '\n';
	return 0;
}