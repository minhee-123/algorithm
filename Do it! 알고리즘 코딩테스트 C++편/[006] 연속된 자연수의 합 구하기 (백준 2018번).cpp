// 문제: https://www.acmicpc.net/problem/2018

#include <iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;

	int start_index = 1;
	int end_index = 1;
	int sum = 1; int cnt = 1; //N 하나인 경우 미리 count

	while (end_index != N)
	{
		if (sum < N) //오른쪽 늘리고
		{
			end_index++;
			sum += end_index;
		}
		else if (sum > N) //왼쪽 줄이고
		{
			sum -= start_index;
			start_index++;
		}
		else if (sum == N) //cnt 하나 세고 오른쪽 늘리고
		{
			cnt++;
			end_index++;
			sum += end_index;
		}
	}
	cout << cnt << '\n';
	return 0;
}