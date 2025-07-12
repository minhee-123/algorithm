// 문제: https://www.acmicpc.net/problem/10868
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL); //이거 빼면 시간초과 문제 발생함

	int N, M;
	cin >> N >> M;

	int k = ceil(log2(N));
	int twoK = pow(2, k);
	
	vector<int> tree(twoK * 2, 2000000000);
	for (int i = twoK; i < twoK + N; i++) cin >> tree[i];
	for (int i = twoK - 1; i > 0; i--)
	{
		tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	} // 최소값 세그먼트 트리

	for (int i = 0; i < M; i++)
	{
		int S, E;
		cin >> S >> E;

		S += twoK - 1;
		E += twoK - 1;

		vector<int> choice;
		while (S <= E)
		{
			if (S % 2 == 1) choice.push_back(tree[S]); // start index가 홀수일때 선택
			if (E % 2 == 0) choice.push_back(tree[E]); // end index가 짝수일때 선택

			S = (S + 1) / 2;
			E = (E - 1) / 2;
		}

		sort(choice.begin(), choice.end());
		cout << choice[0] << '\n';
	}
	return 0;
}