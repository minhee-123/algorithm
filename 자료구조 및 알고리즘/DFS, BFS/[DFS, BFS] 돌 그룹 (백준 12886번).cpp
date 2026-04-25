// 문제: https://www.acmicpc.net/problem/12886
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// 규칙에 의하면 어떤 두 그룹이 돌을 주고받아도 S = A + B + C는 변하지 않음
// 총합 S가 3으로 나누어 떨어지지 않으면 애초에 같게 만들 수 없음 → 0을 출력

// visit[A][B]라는 배열을 만들어 이미 확인했던 숫자 조합인지 체크 → 숫자 조합의 중복 체크를 방지
// A와 B만 저장하고 다니면 C는 자동으로 가지고 다니게 된다

int A, B, C, S;
bool visit[1501][1501]; // visit[A][B] = A와 B 조합을 이미 확인

int main()
{
	cin >> A >> B >> C;
	S = A + B + C;

	if (S % 3 != 0)
	{
		cout << 0;
		return 0;
	}

	vector<int> num(3);
	num[0] = A; num[1] = B; num[2] = C;
	sort(num.begin(), num.end());

	queue<pair<int, int>> que;
	que.push({ num[0], num[2] });
	visit[num[0]][num[2]] = true;
	
	while (!que.empty())
	{
		// 크기는 항상 A <= B <= C
		int nowA = que.front().first;
		int nowC = que.front().second;
		int nowB = S - (nowA + nowC);
		que.pop();

		if (nowA == nowB && nowA == nowC && nowB == nowC)
		{
			cout << 1;
			return 0;
		}

		for (int i = 0; i < 3; i++)
		{
			int nextA = nowA;
			int nextB = nowB;
			int nextC = nowC;

			if (i == 0) // A와 B 조합
			{
				nextA += nowA;
				nextB -= nowA;
			}
			else if (i == 1) // A와 C 조합
			{
				nextA += nowA;
				nextC -= nowA;
			}
			else // B와 C 조합
			{
				nextB += nowB;
				nextC -= nowB;
			}
			if (nextA <= 0 || nextB <= 0 || nextC <= 0) continue;

			num[0] = nextA; num[1] = nextB; num[2] = nextC;
			sort(num.begin(), num.end());

			if (!visit[num[0]][num[2]])
			{
				visit[num[0]][num[2]] = true;
				que.push({ num[0], num[2] });
			}
		}
	}
	cout << 0;
	return 0;
}