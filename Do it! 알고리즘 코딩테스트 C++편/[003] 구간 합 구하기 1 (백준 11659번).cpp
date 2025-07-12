// 문제: https://www.acmicpc.net/problem/11659

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	// 위 구문을 제거하면 시간초과 문제가 발생함
	// C++의 연산속도가 빨라지도록 할 수 있는 구문 (근소한 차이로 시간초과가 발생할 때 해결됨)

	int data_cnt, testcase;
	vector<int> data_sum;

	int sum = 0;
	cin >> data_cnt >> testcase;
	for (int i = 0; i < data_cnt; i++)
	{
		int temp; cin >> temp;
		sum += temp;
		data_sum.push_back(sum);
	}

	for (int t = 0; t < testcase; t++)
	{
		int i, j;
		cin >> i >> j;
		i = i - 1;
		j = j - 1;

		if (i == 0) cout << data_sum[j] << '\n';
		else cout << data_sum[j] - data_sum[i - 1] << '\n';
	}
	return 0;
}