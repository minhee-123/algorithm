// 문제: https://www.acmicpc.net/problem/21568
// 채점 준비 중인 문제로 채점을 받을 수 없음 (따라서 아래 코드에 오류가 있을 수도 있음)

// 확장 유클리드 호제법 
// → 방정식의 정수해를 구하는 방법

#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

stack<long> sk; //몫만 사용하니까 몫만 저장
// 마지막에 넣은 값부터 다시 꺼내야하므로 stack 사용

long X = 1; //이전 시작값
long Y = 0;

long gcd(long a, long b)
{
	//if (a < b) swap(a, b); → 그냥 공약수를 구하는 문제가 아니어서 이 부분이 들어가면 안된다 (a와 b의 순서가 바뀌면 안됨)
	// 공약수를 구할 때도 굳이 안 넣어도 됨 (넣으면 계산 횟수를 단축해주지만 그래봤자 1회 단축임)
	sk.push(a / b);

	if (a % b == 0) return b;
	else return gcd(b, a % b);
}

void Find()
{
	if (sk.empty()) return;

	long X_past = X;
	long Y_past = Y;

	X = Y_past; // X = Y'
	Y = X_past - (Y_past * sk.top()); // Y = X' - Y' * 몫
	sk.pop();

	Find();
}

int main()
{
	long A, B, C;
	cin >> A >> B >> C;

	long mgcd = gcd(A, B);
	if (C % mgcd == 0)
	{
		long K = C / mgcd;
		Find();
		cout << K * X << ' ' << K * Y;
	}
	else cout << -1;

	return 0;
}