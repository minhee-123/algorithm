// 문제: https://www.acmicpc.net/problem/2162
#include <iostream>
using namespace std;

int N;
int UF[3001]; // UF[i] = i번째 선분이 속한 집합의 대표값

// Union-Find 함수(그룹 관리)
int Find(int c)
{
	if (UF[c] == c) return c;
	else return UF[c] = Find(UF[c]);
}
void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);
	if (a == b) return;

	if (a > b) swap(a, b);
	UF[b] = a;
}

// CCW == 0인 경우(일직선 상에 있는 경우) 교차 여부 판단
bool Check_One_Line(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	if (min(x1, x2) <= max(x3, x4) && min(x3, x4) <= max(x1, x2) && min(y1, y2) <= max(y3, y4) && min(y3, y4) <= max(y1, y2)) return true;
	else return false;
}

// CCW 계산을 통한 교차 여부 판단 (CCW: 세 점의 위치 관계를 파악하는 공식)
int Change_CCW(int CCW)
{
	if (CCW > 0) return 1;
	else if (CCW < 0) return -1;
	else return 0;
}
bool Check_Cross(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) // 선분 A-B, C-D
{
	// A-B 기준으로 C와 D 판별
	int CCW1 = (x1 * y3 + x3 * y2 + x2 * y1) - (x1 * y2 + x2 * y3 + x3 * y1); // A-C-B CCW
	CCW1 = Change_CCW(CCW1);
	int CCW2 = (x1 * y4 + x4 * y2 + x2 * y1) - (x1 * y2 + x2 * y4 + x4 * y1); // A-D-B CCW
	CCW2 = Change_CCW(CCW2);
	// (CCW1 * CCW2)가 음수면 교차, 양수면 교차X, 0이면 일직선

	// C-D 기준으로 A와 B 판별
	int CCW3 = (x3 * y1 + x1 * y4 + x4 * y3) - (x3 * y4 + x4 * y1 + x1 * y3); // C-A-D CCW
	CCW3 = Change_CCW(CCW3);
	int CCW4 = (x3 * y2 + x2 * y4 + x4 * y3) - (x3 * y4 + x4 * y2 + x2 * y3); // C-B-D CCW
	CCW4 = Change_CCW(CCW4);
	// (CCW3 * CCW4)가 음수면 교차, 양수면 교차X, 0이면 일직선

	// A-B와 C-D가 일직선 상에 있는 경우
	if (CCW1 * CCW2 == 0 && CCW3 * CCW4 == 0) return Check_One_Line(x1, y1, x2, y2, x3, y3, x4, y4);
	// A-B와 C-D가 교차하는 경우
	else if (CCW1 * CCW2 <= 0 && CCW3 * CCW4 <= 0) return true;
	// A-B와 C-D가 교차하지 않는 경우
	else return false;
}

// 정답 그룹의 수와 가장 크기가 큰 그룹에 속한 선분의 개수를 출력
int Answer[3001]; // 전역변수 → 자동 0으로 초기화
pair<int, int> Find_Answer()
{
	for (int i = 1; i <= N; i++) Answer[Find(i)]++;
	// 바로 UF[i]를 넣지 않고 꼭 Find(i)를 해줘야 함
	// UF[i]가 현재 집합의 최종 대표값을 가지고 있다는 보장이 없음 → UF[i] 값을 이용할 때는 최신화(Find) 필수

	int group_cnt = 0;
	int max_line_cnt = 0;

	for (int i = 1; i <= N; i++)
	{
		if (Answer[i] > 0)
		{
			group_cnt++;
			max_line_cnt = max(max_line_cnt, Answer[i]);
		}
	}

	return { group_cnt, max_line_cnt };
}

struct INFORM
{
	int x1;
	int y1;
	int x2;
	int y2;
};
INFORM line[3001];

int main()
{
	cin >> N;
	for (int i = 1; i <= N; i++) UF[i] = i;

	for (int i = 1; i <= N; i++)
	{
		cin >> line[i].x1 >> line[i].y1 >> line[i].x2 >> line[i].y2;

		if (i == 1) continue;
		else
		{
			for (int j = 1; j <= i; j++)
			{
				// 선분이 만나는(교차하는) 경우
				if (Check_Cross(line[j].x1, line[j].y1, line[j].x2, line[j].y2, line[i].x1, line[i].y1, line[i].x2, line[i].y2))
				{
					Union(j, i); // 같은 그룹으로 묶음
				}
			}
		}
	}
	pair<int, int> answer = Find_Answer();

	cout << answer.first << '\n' << answer.second;
	return 0;
}