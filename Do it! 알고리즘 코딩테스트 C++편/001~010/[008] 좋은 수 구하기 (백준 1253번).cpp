// 문제: https://www.acmicpc.net/problem/1253

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N;
	cin >> N;

	vector<int> num(N, 0);
	for (int i = 0; i < N; i++)
	{
		cin >> num[i];
	}
	sort(num.begin(), num.end());

	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		int target = num[i];

		int start_index = 0;
		int end_index = N - 1;

		while (start_index < end_index)
		{
			if (num[start_index] + num[end_index] == target)
			{
				if (start_index == i) start_index++;
				else if (end_index == i) end_index--;
				else
				{
					cnt++;
					break;
				}
			}
			else if (num[start_index] + num[end_index] > target) end_index--;
			else if (num[start_index] + num[end_index] < target) start_index++;
		}
	}

	cout << cnt << '\n';
	return 0;
}
