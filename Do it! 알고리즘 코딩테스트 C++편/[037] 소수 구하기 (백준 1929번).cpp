// 문제: https://www.acmicpc.net/problem/1929

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int M, N;
	cin >> M >> N;

	vector<bool> visit(N + 1, false);
	visit[0] = true;
	visit[1] = true;

	for (int i = 2; i < N; i++) //2의 배수부터 판별해야되고, N은 끝수이므로 N의 배수는 판별대상이 아님
	{
		if (visit[i]) continue;
		for (int j = 2; j <= N / i; j++)
		{
			visit[i * j] = true;
		}
	}

	for (int i = M; i <= N; i++)
	{
		if (!visit[i]) cout << i << '\n';
	}
	return 0;
}