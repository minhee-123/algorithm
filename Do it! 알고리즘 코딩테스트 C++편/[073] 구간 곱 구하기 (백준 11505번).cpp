// 문제: https://www.acmicpc.net/problem/11505
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
// 구간 곱이고 문제에서 나머지를 정답으로 도출하라고 함 → MOD 연산 필수!!

int main()
{
	int N, M, C;
	cin >> N >> M >> C;

	int k = ceil(log2(N));
	int twoK = pow(2, k);

	vector<long long> tree(twoK * 2, 1); 
	for (int i = twoK; i < twoK + N; i++) cin >> tree[i];
	for (int i = twoK - 1; i > 0; i--)
	{
		tree[i] = (tree[2 * i] % 1000000007) * (tree[2 * i + 1] % 1000000007) % 1000000007;
	} // 초기 세그먼트 트리

	for (int i = 0; i < M + C; i++)
	{
		int command, a, b;
		cin >> command >> a >> b;

		if (command == 1)
		{
			int index = a + twoK - 1;
			tree[index] = b;

			int idx = index / 2;
			while (idx > 0)
			{
				tree[idx] = (tree[2 * idx] % 1000000007) * (tree[2 * idx + 1] % 1000000007) % 1000000007;
				idx = idx / 2;
			}
		}
		else if (command == 2)
		{
			int S = a + twoK - 1;
			int E = b + twoK - 1;

			vector<long long> choice;
			while (S <= E)
			{
				if (S % 2 == 1) choice.push_back(tree[S]);
				if (E % 2 == 0) choice.push_back(tree[E]);

				S = (S + 1) / 2;
				E = (E - 1) / 2;
			}

			long long output = 1;
			for (int i = 0; i < choice.size(); i++) output = (output % 1000000007) * (choice[i] % 1000000007) % 1000000007;
			cout << output << '\n';
		}
	}
	return 0;
}