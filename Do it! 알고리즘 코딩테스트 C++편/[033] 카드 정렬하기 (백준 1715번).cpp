// 문제: https://www.acmicpc.net/problem/1715

#include <iostream>
#include <queue>
using namespace std;

int main()
{
	int N;
	priority_queue<long, vector<long>, greater<long>> pq;

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		long temp;
		cin >> temp;
		pq.push(temp);
	}

	if (pq.size() == 1) cout << 0; //비교 횟수가 답 (카드 묶음이 하나밖에 없다면 비교가 수행되지 않음)
	else
	{
		int answer = 0;
		while (pq.size() > 1)
		{
			long val1 = pq.top(); pq.pop();
			long val2 = pq.top(); pq.pop();

			answer += (val1 + val2);
			pq.push(val1 + val2);
		}
		cout << answer;
	}
	return 0;
}