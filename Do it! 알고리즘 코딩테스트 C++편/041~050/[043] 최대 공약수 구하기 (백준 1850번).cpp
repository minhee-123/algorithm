// 문제: https://www.acmicpc.net/problem/1850

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

long gcd(long A, long B) //유클리드 호제법
{
	if (A % B == 0) return B;
	else return gcd(B, A % B);
}

int main()
{
	long A, B; cin >> A >> B;
	if (A < B) swap(A, B);

	long C = gcd(A, B);
	string answer = "";
	for (long i = 0; i < C; i++) answer += "1";

	cout << answer;
	return 0;
}