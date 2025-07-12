// 문제: https://www.acmicpc.net/problem/11003
// deque를 잘 사용하면 슬라이딩 윈도우 && 정렬을 구현할 수 있음
// deque의 앞뒤로 삽입, 삭제 기능을 잘 활용하자

#include <iostream>
#include <deque>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, L;
	cin >> N >> L;
	deque<pair<int, int>> A;

	for (int i = 1; i <= N; i++)
	{
		int val;
		cin >> val;

		while (!A.empty() && A.back().second > val)
		{
			A.pop_back();
		}

		A.push_back({ i, val }); //여기서 집어넣어야지 아니면 비어있는 경우에 아래 while에서 오류 발생

		while (i - A.front().first >= L)
		{
			A.pop_front();
		}

		cout << A.front().second << ' ';
	}
	return 0;
}