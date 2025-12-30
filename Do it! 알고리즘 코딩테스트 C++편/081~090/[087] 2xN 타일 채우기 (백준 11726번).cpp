// 문제: https://www.acmicpc.net/problem/11726
#include <iostream>
using namespace std;

int N;
long long D[1001]; // 2xN 크기의 직사각형을 1x2와 2x1 타일로 채우는 방법의 수

int main()
{
	cin >> N;
	D[0] = 0;
	D[1] = 1;
	D[2] = 2;
	D[3] = 3;
	
	for (int i = 4; i <= N; i++) D[i] = (D[i - 1] + D[i - 2]) % 10007;

	cout << D[N];
	return 0;
}

// 경우를 하나씩 생각해보면 식이 도출됨
// 이전 경우에서 어떻게 현재 경우로 올 수 있을까를 생각해보면 식이 나오는 듯