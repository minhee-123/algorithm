// 문제: https://www.acmicpc.net/problem/2164

#include <iostream>
#include <queue>
using namespace std;

int main()
{
	int N;
	cin >> N;

	queue<int> q;
	for (int i = 1; i <= N; i++)
	{
		q.push(i);
	}

	bool flag = true; //true일 때 한장 버리고, false일 때 맨 위에 있는 걸 아래에 놓음
	while (q.size() > 1)
	{
		if (flag)
		{
			q.pop();
			flag = false;
		}
		else
		{
			int card = q.front();
			q.pop();
			q.push(card);
			flag = true;
		}
	}

	cout << q.front() << '\n';
	return 0;
}