// 문제: https://www.acmicpc.net/problem/1920

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int N; cin >> N;
	vector<int> A(N, 0);
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}
	sort(A.begin(), A.end());

	int M; cin >> M;
	vector<int> F(M, 0);
	for (int i = 0; i < M; i++)
	{
		cin >> F[i];
	}

	for (int i = 0; i < M; i++)
	{
		bool flag = false;

		int start = 0;
		int end = N - 1;
		while (start <= end)
		{
			int mid = (start + end) / 2;

			if (A[mid] > F[i]) end = mid - 1;
			else if (A[mid] < F[i]) start = mid + 1;
			else //A[mid] == F[i]
			{
				flag = true;
				break;
			}
		}

		if (flag) cout << 1 << '\n';
		else cout << 0 << '\n';
	}
	return 0;
}