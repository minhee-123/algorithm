// 문제: https://www.acmicpc.net/problem/2343

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
int s = 0;
int e = 0;
vector<int> lesson;

int group(int len)
{
	int cnt = 1;
	int stock = 0;
	for (int i = 0; i < N; i++)
	{
		stock += lesson[i];

		if (stock > len)
		{
			cnt++;
			stock = lesson[i];
		}
	}
	return cnt;
}

int main()
{
	cin >> N >> M;

	lesson = vector<int>(N, 0);
	for (int i = 0; i < N; i++)
	{
		cin >> lesson[i];

		s = max(s, lesson[i]);
		e += lesson[i];
	}

	int min_value = 0;
	while (s <= e)
	{
		int mid = (s + e) / 2;
		int value = group(mid);

		if (value <= M)
		{
			min_value = mid;
			e = mid - 1;
		}
		else s = mid + 1;
	}
	cout << min_value << '\n';
}