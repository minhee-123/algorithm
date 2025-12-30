// 문제: https://www.acmicpc.net/problem/2193
#include <iostream>
using namespace std;

int N;
long long D[91]; // D[i] = i자리 이친수의 개수

int main()
{
	cin >> N;
	D[0] = 0; 
	D[1] = 1; // 1
	D[2] = 1; // 10
	D[3] = 2; // 100, 101
	D[4] = 3; // 1000, 1001, 1010 → 뒤가 0으로 끝나는 수가 2개, 뒤가 1로 끝나는 수가 1개
	D[5] = 5; // 뒤가 0으로 끝나는 수가 3개, 뒤가 1로 끝나는 수가 2개
	D[6] = 8; // 5개, 3개
	D[7] = 13; // 8개, 5개

	for (int i = 8; i <= N; i++) D[i] = D[i - 2] * 2 + D[i - 3];
	cout << D[N];
	return 0;
}