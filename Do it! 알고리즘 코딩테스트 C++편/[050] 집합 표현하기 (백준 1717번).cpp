// 문제: https://www.acmicpc.net/problem/1717

#include <iostream>
using namespace std;

int n, m;
int num[1000001];

int Find(int c)
{
	if (num[c] == c) return c;
	else return num[c] = Find(num[c]);
}

void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);

	if (a == b) return;
	else
	{
		if (a > b) swap(a, b); //이 과정을 없애도 문제는 없음 (가장 작은 노드가 대표가 되긴 하더라)
		num[b] = a; 
	} //대표노드는 가장 작은 값
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i <= n; i++) num[i] = i;

	for (int i = 0; i < m; i++)
	{
		int command, a, b;
		cin >> command >> a >> b;

		if (command == 0) Union(a, b);
		else //command == 1
		{
			a = Find(a);
			b = Find(b);

			if (a == b) cout << "YES" << '\n';
			else cout << "NO" << '\n';
		}
	}
	return 0;
}