// 문제: https://www.acmicpc.net/problem/14888
// 모든 경우를 계산하더라도 시간복잡도를 넘지는 않음

#include <iostream>
#include <vector>
using namespace std;

long long max_val = -1000000001;
long long min_val = 1000000001;

int N;
int num[11];

void DFS(int index, long long sum, int calculation, vector<int> cal)
{
	cal[calculation]--;
	if (calculation == 0) sum = sum + num[index];
	else if (calculation == 1) sum = sum - num[index];
	else if (calculation == 2) sum = sum * num[index];
	else sum = sum / num[index];

	for (int i = 0; i < 4; i++)
	{
		if (cal[i] != 0) DFS(index + 1, sum, i, cal);
	}

	if (index == N - 1)
	{
		max_val = max(max_val, sum);
		min_val = min(min_val, sum);
	}
}

int main()
{
	cin >> N;
	vector<int> cal(4, 0);
	for (int i = 0; i < N; i++) cin >> num[i];
	for (int i = 0; i < 4; i++) cin >> cal[i];

	for (int i = 0; i < 4; i++)
	{
		if (cal[i] != 0) DFS(1, num[0], i, cal);
	}

	cout << max_val << '\n' << min_val << '\n';
	return 0;
}