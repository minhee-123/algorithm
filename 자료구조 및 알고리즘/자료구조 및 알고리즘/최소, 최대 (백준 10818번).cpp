// 최소, 최대 (https://www.acmicpc.net/problem/10818)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int N;
	vector<int> number;

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int temp;
		cin >> temp;
		number.push_back(temp);
	}

	sort(number.begin(), number.end());
	cout << number[0] << " " << number[N-1];
	return 0;
}