// 소수 구하기 (정수론 - 에라토스테네스의 체)
// 문제: https://www.acmicpc.net/problem/1929
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 약수 구하기 → 1을 제외하고 자기자신 이하의 수로 나누었을 때 나머지 0을 만족하는 수
// 소수 구하기 → 1과 자기자신을 제외하고 약수가 없어야 함
//			   → 빠르게 소수를 구하는 방법: 에라토스테네스의 체
// 최대공약수 구하기 → 유클리드 호제법 or 손수 구하기
//					 → 유클리드 호제법은 큰 수를 작은 수로 나머지 연산 반복 (작은 수가 다음 큰 수, 나머지가 다음 작은 수가 됨)(나머지가 0이 되었을 때 작은 수가 최대공약수)
// 최소공배수 구하기 → 최소공배수 = (A * B) / 최대공약수

// 에라토스테네스의 체를 수행할 때 TIP
// N까지 범위 중에서 소수를 찾으라고 했을 때 → N의 제곱근까지만 탐색해도 OK
// → N = a * b라고 했을 때 a와 b중에서 루트N보다 큰 게 있다면 하나는 루트N보다 작음 (무조건)
// → N보다 작고 소수가 아닌 수는 무조건 루트N보다 작은 수로 나누어짐
// → N의 제곱근(루트N)까지만 탐색해도 소수가 아닌 수는 모두 지워짐

int main()
{
	int M, N;
	cin >> M >> N;

	vector<bool> num(N + 1, true);
	num[0] = false;
	num[1] = false; //소수가 아니니까 false로 미리 처리해야 함

	int rootN = sqrt(N);

	for (int i = 2; i <= rootN; i++)
	{
		if (!num[i]) continue;

		for (int j = i; j <= N / i; j++) //i이하의 배수는 이미 삭제됨 (i이하의 수에 의해)
		{
			num[i * j] = false;
		} //i의 배수이면 소수가 아니니까 지움 (i가 약수가 됨)
	}

	for (int i = M; i <= N; i++)
	{
		if (num[i]) cout << i << '\n';
	}
	return 0;
}