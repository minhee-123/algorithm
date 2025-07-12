// 문제: https://www.acmicpc.net/problem/1940

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M;
	cin >> N >> M;

	vector<int> element(N, 0);
	for (int i = 0; i < N; i++)
	{
		int temp; cin >> temp;
		element[i] = temp;
	}
	sort(element.begin(), element.end());

	int cnt = 0;
	int start_index = 0;
	int end_index = N - 1;

	while (start_index < end_index)
	{
		if (element[start_index] + element[end_index] == M)
		{
			cnt++;
			start_index++;
			end_index--;
		}
		else if (element[start_index] + element[end_index] > M)
		{
			end_index--;
		}
		else if (element[start_index] + element[end_index] < M)
		{
			start_index++;
		}
	}
	cout << cnt << '\n';
	return 0;
}

// 무식하게 완전탐색하지 않고 이런식으로 정답이 될 수 있는 경우의 수만 탐색하면 더 효율적으로 답을 찾아냄
// 그래서 알고리즘을 쓰나봐