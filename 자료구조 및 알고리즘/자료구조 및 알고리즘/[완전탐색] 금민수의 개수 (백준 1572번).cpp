// 금민수의 개수 (https://www.acmicpc.net/problem/1527)
// 재귀(DFS)를 잘 이용하자
// 브루트포스는 재귀를 이용하는 경우가 많은 듯

// 범위 내의 모든 수가 금민수(4와 7로 이루어진 수)인지 살펴보면 시간초과 발생
// 반대로 생각해서 
// → 금민수를 만들고 해당 수가 범위 내에 있는지 체크 (금민수가 최대를 넘으면 재귀 종료)

//이때 범위가 너무 커서 오버플로가 발생할 수도 있음
//주어진 수의 최대가 너무 크다면 long long 사용 (혹시 모르니까)

#include <iostream>
#include  <string>
#include <cmath>
using namespace std;

long long int A, B;
long long int cnt = 0;

void gold_minsu(long long int num)
{
	if (num > B) return; //종료한다는 의미 (void니까 반환값은 없음)

	if (A <= num && num <= B) cnt++; //금민수가 범위 내에 있으면 count (범위 쓸 때 && 사용해야 함)

	gold_minsu(num * 10 + 4); //뒤로 4가 오는 금민수 생성
	gold_minsu(num * 10 + 7); //뒤로 7이 오는 금민수 생성
}

int main()
{
	cin >> A >> B;

	gold_minsu(4); //4로 시작하는 금민수 생성
	gold_minsu(7); //7로 시작하는 금민수 생성

	cout << cnt;
	return 0;
}