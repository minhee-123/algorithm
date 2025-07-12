// 문제: https://www.acmicpc.net/problem/2042
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
	long long N, M, C;
	cin >> N >> M >> C;

	long long k = ceil(log2(N)); // ceil → 올림함수 (소숫점이 있으면 무조건 1 올림)
	long long twoK = pow(2, k);

	vector<long long> tree(twoK * 2, 0);
	for (long long i = twoK; i < twoK + N; i++) cin >> tree[i];
	for (long long i = twoK - 1; i > 0; i--) // index는 1부터 시작함 (0은 사용 안함)
	{
		tree[i] = tree[2 * i] + tree[2 * i + 1];
	} // 초기 구간합 세그먼트 트리

	for (long long i = 0; i < M + C; i++)
	{
		long long command, a, b;
		cin >> command >> a >> b;

		if (command == 1) // a번째 수를 b로 변경
		{
			long long index = a + twoK - 1;
			tree[index] = b;

			long long idx = index;
			while (idx > 0)
			{
				idx = idx / 2;
				tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
			} // 업데이트
		}
		else if (command == 2) // a번째 수부터 b번째 수까지 구간합
		{
			long long S = a + twoK - 1;
			long long E = b + twoK - 1;

			vector<long long> choice;
			while (S <= E)
			{
				if (S % 2 == 1) choice.push_back(tree[S]); //start index의 값이 홀수면 선택
				if (E % 2 == 0) choice.push_back(tree[E]); //end index의 값이 짝수면 선택

				S = (S + 1) / 2;
				E = (E - 1) / 2;
			}

			long long output = 0;
			for (long long i = 0; i < choice.size(); i++) output += choice[i];
			cout << output << '\n';
		}
	}
	return 0;
}