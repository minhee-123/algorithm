// 소수 찾기 (https://www.acmicpc.net/problem/1978)

#include <iostream>
#include <vector>
using namespace std;

int div_num(int num)
{
	int cnt = 0;
	for (int i = 1; i <= num; i++)
	{
		if (num % i == 0) cnt++;
	}
	return cnt;
}

int main()
{
	int N, count = 0;

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int temp; cin >> temp;
		if (div_num(temp) == 2) count++;
	}
	
	cout << count;
	return 0;
}