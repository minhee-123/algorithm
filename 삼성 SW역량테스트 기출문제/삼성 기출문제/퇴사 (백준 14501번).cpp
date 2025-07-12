// 문제: https://www.acmicpc.net/problem/14501

// N의 최대값이 15이므로 시간복잡도를 고려하지 않아도 됨
#include <iostream>
#include <vector>
using namespace std;

int N;
bool visit[15];
int T[15];
int P[15];

int cnt = 0;
void DFS(int index, int money)
{
	if (index + T[index] - 1 >= N) return;

	money += P[index];
	for (int i = index; i < index + T[index]; i++) visit[i] = true;

	for (int i = index + 1; i < N; i++)
	{
		if (!visit[i]) DFS(i, money);
	}
	cnt = max(cnt, money);

	for (int i = index; i < index + T[index]; i++) visit[i] = false;
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++) cin >> T[i] >> P[i];
	for (int i = 0; i < N; i++) DFS(i, 0);
	cout << cnt;
	return 0;
}