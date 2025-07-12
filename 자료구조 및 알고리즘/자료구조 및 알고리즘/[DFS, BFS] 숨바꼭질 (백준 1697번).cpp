// 숨바꼭질 (https://www.acmicpc.net/problem/1697)

#include <iostream>
#include <queue>
using namespace std;

int cnt = 0;
bool visit[100005]; //중복방문을 피하지 않으면 메모리초과 발생

int main()
{
	int N, K;
	cin >> N >> K;
	
	queue<int> q;
	queue<int> t;
	q.push(N);
	t.push(0);
	visit[N] = true;

	while (1)
	{
		int now = q.front();
		int now_time = t.front();
		q.pop();
		t.pop();

		if (now == K)
		{
			cnt = now_time;
			break;
		}

		int next_time = now_time + 1;
		int next1 = now - 1;
		int next2 = now + 1;
		int next3 = now * 2;

		if (next1 >= 0 && next1 <= 100000 && !visit[next1])
		{
			q.push(next1);
			t.push(next_time);
			visit[next1] = true;
		}
		if (next2 >= 0 && next2 <= 100000 && !visit[next2])
		{
			q.push(next2);
			t.push(next_time);
			visit[next2] = true;
		}
		if (next3 >= 0 && next3 <= 100000 && !visit[next3])
		{
			q.push(next3);
			t.push(next_time);
			visit[next3] = true;
		}
	}

	cout << cnt;
	return 0;
}