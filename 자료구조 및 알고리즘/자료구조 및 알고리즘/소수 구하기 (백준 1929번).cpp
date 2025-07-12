// 문제: https://www.acmicpc.net/problem/1929

// 에라토스테네스의 체 구현문제 (특정 범위 내에서 소수의 개수를 구할 때 유용)
// 에라토스테네스의 체: 시작 수부터 배수를 지워나감 (지워진 배수의 배수는 연산하지 않음 → 이미 지워졌음)
// 구현 자체는 O(n^2)이 되는데 실제로 바깥 루프에서 생략되는 경우가 많아서 실제 시간복잡도는 O(nlogn)
// 일반적인 소수 구하기보다는 계산이 빠름

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int start, end;
	cin >> start >> end;

	vector<int> A(end + 1, 0);
	for (int i = 2; i <= end; i++) A[i] = 1;
	for (int i = 2; i <= end; i++) //앞에부터 해야 앞에 값의 배수들이 지워짐 (소수 아닌 값들)
	{
		if (A[i] == 0) continue;

		for (int j = 2; j <= end / i; j++)
		{
			int del = i * j;
			A[del] = 0;
		}
	}

	for (int i = start; i <= end; i++)
	{
		if (A[i] == 1) cout << i << '\n';
	}
	return 0;
}