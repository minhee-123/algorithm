// 문제: https://www.acmicpc.net/problem/1253
// 투 포인터 알고리즘 사용

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int cnt = 0;
	int N;
	cin >> N;

	vector<int> A(N, 0);
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}
	sort(A.begin(), A.end()); //정렬하고

	for (int index = 0; index < N; index++) //투 포인터 알고리즘으로 좋은수 개수 세기
	{
		int start = 0;
		int end = N - 1; //음수를 포함하기 때문에 전체범위에서 확인해야 함

		while (start < end)
		{
			int sum = A[start] + A[end];
			int val = A[index];

			if (sum > val) end--;
			else if (sum < val) start++;
			else //sum == val
			{
				if (start == index) start++; //sum == val인데 start나 end가 자기자신일 경우 앞뒤로 움직임 (이 구문을 밖으로 빼면 풀이가 틀림)
				else if (end == index) end--;
				else
				{
					cnt++;
					break;
				}
			}
		}
	}
	cout << cnt << '\n';
	return 0;
}