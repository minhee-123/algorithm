// 문제: https://www.acmicpc.net/problem/1747

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#define MAX 10000000

bool panrind(int num)
{
	string number = to_string(num);
	
	int start = 0;
	int end = number.size() - 1;
	
	bool flag = true;
	while (start <= end)
	{
		if (number[start] != number[end])
		{
			flag = false;
			break;
		}
		else
		{
			start++;
			end--;
		}
	}

	if (flag) return true; //팬린드롬 수가 맞음
	else return false; //팬린드롬 수가 아님
}

int main()
{
	int N; cin >> N;

	bool visit[MAX + 1] = { false };
	visit[0] = true;
	visit[1] = true;

	for (int i = 2; i <= sqrt(MAX); i++)
	{
		if (visit[i]) continue;
		for (int j = i + i; j <= MAX; j = j + i) visit[j] = true;
	}

	int answer = 0;
	for (int num = N; num <= MAX; num++)
	{
		if (visit[num]) continue;

		bool flag = panrind(num);
		if (flag)
		{
			answer = num;
			break;
		}
	}
	
	cout << answer;
	return 0;
}