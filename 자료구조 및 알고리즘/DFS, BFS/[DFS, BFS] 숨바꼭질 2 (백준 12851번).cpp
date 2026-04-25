// 문제: https://www.acmicpc.net/problem/12851
#include <iostream>
#include <queue>
using namespace std;

int visit[100001];
int main()
{
	int S, E;
	cin >> S >> E;

	queue<pair<int, int>> que;
	que.push({ S, 0 }); // 현재 번호, 이동횟수
	visit[S] = true;

	int answerCNT = -1; // 최단 이동횟수
	int answerWAY = -1; // 최단 이동횟수 방법 수
	for (int i = 0; i <= 100000; i++) visit[i] = -1; // 이동횟수를 저장 (같은 이동횟수로 도착하는 경로가 여럿일 경우)

	while (!que.empty())
	{
		int now = que.front().first;
		int cnt = que.front().second;
		que.pop();

		if (now == E)
		{
			if (answerCNT == -1)
			{
				answerCNT = cnt;
				answerWAY = 1;
			}
			else if (answerCNT == cnt) answerWAY++;
			else if (answerCNT < cnt) continue;
			else // answerCNT > cnt (정상적으로 동작할 경우 들어올 일 없음)
			{
				answerCNT = cnt;
				answerWAY = 1;
			}
		}
		if (answerCNT != -1 && cnt > answerCNT) continue;

		// X * 2
		int next = now * 2;
		if (next >= 0 && next <= 100000)
		{
			if (visit[next] == -1 || visit[next] >= cnt + 1)
			{
				visit[next] = cnt + 1;
				que.push({ next, cnt + 1 });
			}
		}

		// X + 1
		next = now + 1;
		if (next >= 0 && next <= 100000)
		{
			if (visit[next] == -1 || visit[next] >= cnt + 1)
			{
				visit[next] = cnt + 1;
				que.push({ next, cnt + 1 });
			}
		}

		// X - 1
		next = now - 1;
		if (next >= 0 && next <= 100000)
		{
			if (visit[next] == -1 || visit[next] >= cnt + 1)
			{
				visit[next] = cnt + 1;
				que.push({ next, cnt + 1 });
			}
		}
	}

	cout << answerCNT << '\n' << answerWAY;
	return 0;
}

// 놓쳤던 부분
// 현재 문제의 중요한 부분은 최단 경로의 방법이 몇 가지인지도 함께 찾아야 함!!
// (1) 동일한 번호에 동일한 이동횟수로 방문하는 경우가 있음
// (2) 이 경우 경로가 2개가 되는 것임 → visit 배열에 이동횟수를 저장해야 함