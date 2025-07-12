// 쉽게 푸는 문제 (https://www.acmicpc.net/problem/1292)

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int op, ed;
	cin >> op >> ed;

	int cnt = 0, num = 1;
	vector<int> arr;

	while (cnt != ed)
	{
		for (int i = 1; i <= num; i++)
		{
			arr.push_back(num);
			cnt++;
			if (cnt == ed) break;
		}
		num++;
	}

	int sum = 0;
	for (int i = op - 1; i < ed; i++)
	{
		sum += arr[i];
	}
	cout << sum;
	return 0;
}

//메모리 생각 안하고 푼다고 하면 그냥 숫자 1000까지 수열로 만들어서 원하는 구간을 더하는 방법으로 하면 됨 (근데 이건 너무 무식하지 않나)