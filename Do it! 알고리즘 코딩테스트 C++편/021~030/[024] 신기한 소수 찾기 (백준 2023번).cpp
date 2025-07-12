// 문제: https://www.acmicpc.net/problem/2023
// DFS의 원리를 가장 심플하면서도 명확하게 사용하는 문제
// DFS는 한 노드를 끝까지 탐색(한 분기를 탐색 완료)하고 다음 노드를 끝까지 탐색함

#include <iostream>
using namespace std;

int N;

bool sosu(int num)
{
	for (int i = 2; i <= num / 2; i++)
	{
		if (num % i == 0) return false; //소수X
	}
	return true; //소수
}

void special_sosu(int num, int jarisu)
{
	if (jarisu == N)
	{
		if (sosu(num)) cout << num << '\n';
		return;
	}

	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0) continue; //일의 자리가 짝수인 경우 무조건 2를 약수로 가짐 (소수X)
		if (sosu(num * 10 + i)) special_sosu(num * 10 + i, jarisu + 1);
	}
}

int main()
{
	cin >> N;

	special_sosu(2, 1); //한자리수 소수로 출발 (2, 3, 5, 7 소수)
	special_sosu(3, 1);
	special_sosu(5, 1);
	special_sosu(7, 1);
	
	return 0;
}