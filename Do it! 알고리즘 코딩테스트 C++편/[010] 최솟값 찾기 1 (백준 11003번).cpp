// 문제: https://www.acmicpc.net/problem/11003

#include <iostream>
#include <deque>
using namespace std;

typedef pair<int, int> Node;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, L;
	cin >> N >> L;

	deque<Node> dq;
	for (int i = 0; i < N; i++)
	{
		int now;
		cin >> now;

		while (!dq.empty() && dq.back().second > now) //비어있지 않고 덱의 맨마지막 값이 현재값보다 클 경우 반복
		{
			dq.pop_back();
		}
		dq.push_back({ i, now });

		if (i - dq.front().first >= L) dq.pop_front();

		cout << dq.front().second << ' ';
	}
	return 0;
}