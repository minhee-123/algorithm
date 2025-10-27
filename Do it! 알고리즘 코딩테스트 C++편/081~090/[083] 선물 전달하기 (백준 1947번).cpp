// 문제: https://www.acmicpc.net/problem/1947
#include <iostream>
using namespace std;

// 대회에 참가한 모든 사람이 하나의 선물을 준비
// 선물을 나누는 경우의 수 (모든 사람은 선물을 하나씩, 본인의 선물을 본인이 받는 경우는 없음)

// 답을 출력할 때 1000000000으로 나눈 나머지를 가져옴
// MOD 연산 적용

#define num 1000000000

int N;
long long D[1000001]; // N명일 때 선물을 교환할 수 있는 경우의 수 (본인의 선물을 본인이 받을 수는 없음)

int main()
{
	cin >> N;
	D[1] = 0; // 혼자 선물을 교환할 수 없음
	D[2] = 1; // 서로 선물을 교환하는 경우밖에 없음

	for (int i = 3; i <= N; i++)
	{
		// D[n] = (n-1) * (D[n-2] + D[n-1])
		// D[n-2] : A와 B가 서로 선물을 교환할 때 남는 경우의 수
		// D[n-1] : A만 B에서 선물을 줄때 남는 경우의 수
		// (n-1) : B는 n-1명이 될 수 있음 (A가 선물을 줄 수 있는 사람은 n-1명)

		long long value = ((D[i - 2] % num) + (D[i - 1] % num)) % num;
		D[i] = (((i - 1) % num) * (value % num)) % num; // 연산 중간 과정(곱셈)에서 오버플로우 발생 가능 → long long 사용
	}

	cout << D[N];
	return 0;
}

/*
* MOD 연산을 적용하는 경우 다루는 수가 매우 큼
* → 오버플로우를 방지하기 위해 웬만하면 long long 형을 사용
*/