// 문제: https://www.acmicpc.net/problem/1744

#include <iostream>
#include <queue>
using namespace std;

int main()
{
	int N; cin >> N;

	priority_queue<int, vector<int>> plus; //최대힙
	priority_queue<int, vector<int>, greater<int>> minus; //최소힙 (-1000 < -1)
	bool zero_flag = false;
	int one_cnt = 0;
	for (int i = 0; i < N; i++)
	{
		int temp; cin >> temp;
		if (temp == 0) zero_flag = true;
		else if (temp == 1) one_cnt++; //1의 경우 누구와 묶지 않고 더해져야 무조건 이득
		else if (temp > 0) plus.push(temp);
		else minus.push(temp);
	}

	int answer = one_cnt;

	while (plus.size() > 1)
	{
		int val1 = plus.top(); plus.pop();
		int val2 = plus.top(); plus.pop();
		answer += val1 * val2;
	}
	if (plus.size() == 1) answer += plus.top();

	while (minus.size() > 1)
	{
		int val1 = minus.top(); minus.pop();
		int val2 = minus.top(); minus.pop();
		answer += val1 * val2;
	}
	if (minus.size() == 1 && !zero_flag) answer += minus.top();

	cout << answer;
	return 0;
}