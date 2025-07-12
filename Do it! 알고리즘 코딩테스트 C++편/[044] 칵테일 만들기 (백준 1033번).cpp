// 문제: https://www.acmicpc.net/problem/1033

// (1) 두 비율의 최소공배수를 누적해서 곱함
// (2) 곱한 값을 임의의 시작점에 저장 → DFS를 돌면서 비율에 맞게 재료무게 저장
// (3) 재료 무게의 합이 최소값이어야 하므로 모든 재료의 최소공약수를 구해서, 합을 공약수로 나눈 값 출력

// 오버플로우가 발생하면 백준 채점에서 시간초과가 발생한다
// 곱하는 수가 많다, 수가 커질 것 같다 → 혹시 모르니 무조건 long 사용

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct inform
{
	int index;
	int ratio1;
	int ratio2;
};

int N;
vector<inform> graph[10];
long ingre[10] = { 0 };
bool visit[10];

long gcd(long a, long b)
{
	if (a < b) swap(a, b);
	if (a % b == 0) return b;
	else return gcd(b, a % b);
}

void DFS(int index)
{
	if (visit[index]) return;
	visit[index] = true;

	for (int i = 0; i < graph[index].size(); i++)
	{
		int next = graph[index][i].index;

		if (visit[next]) continue;
		ingre[next] = ingre[index] * graph[index][i].ratio2 / graph[index][i].ratio1; //나누기 부분을 괄호로 처리하게 되면, 안 나눠지는 경우 0이 곱해지는 상황이 발생할 수 있음 (오류)
		DFS(next);
	}
}

int main()
{
	cin >> N;
	long lcm = 1;
	for (int i = 0; i < N - 1; i++)
	{
		int index1, index2, ratio1, ratio2;
		cin >> index1 >> index2 >> ratio1 >> ratio2;

		graph[index1].push_back({ index2, ratio1, ratio2 }); //index2 = index1 * (ratio2 / ratio1)
		graph[index2].push_back({ index1, ratio2, ratio1 });

		//if (i == 0) min_mul = (ratio1 * ratio2) / gcd(ratio1, ratio2);
		//else
		//{
		//	int mul = ratio1 * ratio2 / gcd(ratio1, ratio2);
		//	min_mul = min_mul * mul / gcd(min_mul, mul);
		//} //모든 비율 숫자들의 최소공배수를 찾으면 DFS 재료무게를 업데이트하는 부분에서 소수가 발생할 수도 있음 (강제 정수형으로 변환해서 오답 발생)
		lcm *= ratio1 * ratio2 / gcd(ratio1, ratio2); //곱한 값을 누적 (최소공배수를 계속해서 곱함, 소수가 발생하는 문제 방지)
	}

	ingre[0] = lcm;
	DFS(0); //사이클 없이 모두 이어져있는 형태, DFS를 한번만 출발하면 재귀형태로 모든 노드를 방문함

	long mgcd = gcd(ingre[0], ingre[1]); //최소공약수
	for (int i = 2; i < N; i++)
	{
		mgcd = gcd(mgcd, ingre[i]);
	}

	for (int i = 0; i < N; i++) cout << ingre[i] / mgcd << ' ';
	return 0;
}