//문제: https://www.acmicpc.net/problem/1182
//원래 백트래킹 문제긴 한데...
//백트래킹을 사용하지 않았을 때 더 간단해서 그냥 간단하게 풀어봄
#include <iostream>
#include <vector>
using namespace std;

int N, S;
vector<int> element;

int cnt = 0;
void Find (int num, int sum)
{
	if (num == N)
	{
		if (sum == S) cnt++;
		return;
	}
	Find(num + 1, sum);
	Find(num + 1, sum + element[num]);
}

int main()
{
	cin >> N >> S;

	element.resize(N);
	for (int i = 0; i < N; i++) cin >> element[i];

	Find(0, 0);
	if (S == 0) cnt--; //공집합(아무것도 선택하지 않음)의 경우 제외

	cout << cnt;
	return 0;
}