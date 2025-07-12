// 문제: https://www.acmicpc.net/problem/11286

// 우선순위 큐에서 정렬 기준은 구조체(struct) 형이 들어감 → 우선순위 큐의 정렬기준은 struct로 선언
// 알고리즘 sort 함수에서 정렬 기준에 bool 함수를 사용하는 것과 혼동하지 않도록 주의

#include <iostream>
#include <queue>
using namespace std;

// 우선순위 큐의 정렬기준을 선언하는 방법 ↓ (기본은 내림차순)
struct comp
{
	bool operator()(int a, int b)
	{
		int abs_a = abs(a);
		int abs_b = abs(b);

		if (abs_a != abs_b) { return abs_a > abs_b; } //절댓값이 다르다면 절댓값이 작은 순으로
		else { return a > b; } //절댓값이 같다면 값이 작은 순으로
	} // → return a > b 로 해야 오름차순으로 정렬된다 (우선순위 큐의 비교함수는 두 값 중 어떤 값이 더 우선순위가 낮은가를 반환함)
	// sort의 정렬기준과 다름을 주의 (교재에 더 자세히 필기해둠)
};

int main()
{
	int N; cin >> N;

	priority_queue<int, vector<int>, comp> pq;

	for (int i = 0; i < N; i++)
	{
		int num; cin >> num;

		if (num == 0)
		{
			if (pq.empty())
			{
				cout << 0 << '\n';
			}
			else
			{
				cout << pq.top() << '\n';
				pq.pop();
			}
		}
		else
		{
			pq.push(num);
		}
	}

	return 0;
}