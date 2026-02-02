// 문제: https://www.acmicpc.net/problem/17386
// 알고리즘: 기하학(선분 교차 판정)
// 선분 교차 판단은 CCW라는 알고리즘을 활용한다!
#include <iostream>
using namespace std;

long long X1, Y1; // L1의 양끝점 A
long long X2, Y2; // B
long long X3, Y3; // L2의 양끝점 C
long long X4, Y4; // D

// 문제에서는 세 점이 일직선 위에 있는 경우가 없다고 하나 (CCW != 0)
// 전체 적용이 가능하게 일직선인 경우도 포함하여 풀이함

int CCW(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3)
{
	long long ccw = (x1 * y2 + x2 * y3 + x3 * y1) - (x1 * y3 + x3 * y2 + x2 * y1);

	if (ccw > 0) return 1; // 반시계 방향
	else if (ccw < 0) return -1; // 시계 방향
	else return 0; // 직선
}

bool check_cross(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3, long long x4, long long y4)
{
	int abc = CCW(x1, y1, x2, y2, x3, y3); // A-B하고 C
	int abd = CCW(x1, y1, x2, y2, x4, y4); // A-B하고 D
	int cda = CCW(x3, y3, x4, y4, x1, y1); // C-D하고 A
	int cdb = CCW(x3, y3, x4, y4, x2, y2); // C-D하고 B (교차 검증 필요)

	// 한 선분과 양끝점의 방향이 같을 경우 교차하지 않음 (다를 경우 교차함)
	// 모든 CCW에서 0이 나온다면 (직선 위에 있다면) → 모든 각 선분의 min 값이 다른 선분의 max 값 이하라면 교차 (반대로 하나라도 min값이 max보다 크면 교차 X)
	
	if (abc * abd == 0 && cda * cdb == 0)
	{
		if (min(x1, x2) <= max(x3, x4) && min(x3, x4) <= max(x1, x2) && min(y1, y2) <= max(y3, y4) && min(y3, y4) <= max(y1, y2)) return true;
		else return false;
	}
	else if (abc * abd <= 0 && cda * cdb <= 0) return true; // 한 점이 선분 위에 있다면 한쪽에서만 CCW가 0이 나올거임(그림으로 생각해보면)
	return false;
}

int main()
{
	cin >> X1 >> Y1 >> X2 >> Y2;
	cin >> X3 >> Y3 >> X4 >> Y4;

	if (check_cross(X1, Y1, X2, Y2, X3, Y3, X4, Y4)) cout << 1;
	else cout << 0;
	return 0;
}
// 계산식상 오버플로우 발생 가능성이 매우 높음 → 이때 계산 중간에 오버플로우가 나는 것이기 때문에 변수형도 long long으로 선언해야 함