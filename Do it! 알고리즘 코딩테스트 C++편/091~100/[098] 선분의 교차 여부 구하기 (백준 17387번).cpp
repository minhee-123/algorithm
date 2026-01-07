// 문제: https://www.acmicpc.net/problem/17387
// CCW를 활용하는 방법 → 선분 교차 여부를 판별할 수 있어서 꽤 유용할지도
#include <iostream>
using namespace std;

long long x1, y1; // A
long long x2, y2; // B
long long x3, y3; // C
long long x4, y4; // D
// A-B 선분과 C-D 선분

long long CCW1; // A C B의 CCW
long long CCW2; // A D B의 CCW
long long CCW3; // C A D의 CCW
long long CCW4; // C B D의 CCW
// 교차 검증이 꼭 필요함 → 기하 문제는 교차검증 여부에 따라 정답이 달라지기도

int main()
{
	cin >> x1 >> y1 >> x2 >> y2;
	cin >> x3 >> y3 >> x4 >> y4;

	CCW1 = (x1 * y3 + x3 * y2 + x2 * y1) - (x1 * y2 + x2 * y3 + x3 * y1);
	if (CCW1 > 0) CCW1 = 1;
	else if (CCW1 < 0) CCW1 = -1;
	else CCW1 = 0;
	CCW2 = (x1 * y4 + x4 * y2 + x2 * y1) - (x1 * y2 + x2 * y4 + x4 * y1);
	if (CCW2 > 0) CCW2 = 1;
	else if (CCW2 < 0) CCW2 = -1;
	else CCW2 = 0;

	CCW3 = (x3 * y1 + x1 * y4 + x4 * y3) - (x3 * y4 + x4 * y1 + x1 * y3);
	if (CCW3 > 0) CCW3 = 1;
	else if (CCW3 < 0) CCW3 = -1;
	else CCW3 = 0;
	CCW4 = (x3 * y2 + x2 * y4 + x4 * y3) - (x3 * y4 + x4 * y2 + x2 * y3);
	if (CCW4 > 0) CCW4 = 1;
	else if (CCW4 < 0) CCW4 = -1;
	else CCW4 = 0;

	if (CCW1 * CCW2 == 0 && CCW3 * CCW4 == 0) // 일직선 상에 있는 경우
	{
		// 교차하지 않는 경우는
		// → 한 선분의 min 값이 다른 선분의 max 값보다 클때
		// → 다르게 생각하면 한 선분의 min 값이 다른 선분의 max 값보다 작거나 같아야 교차함
		if (min(x1, x2) <= max(x3, x4) && min(x3, x4) <= max(x1, x2) && min(y1, y2) <= max(y3, y4) && min(y3, y4) <= max(y1, y2)) cout << 1;
		else cout << 0;

		// 이해가 잘 안된다면 선분을 상자로 생각!
		// A-B와 C-D를 대각선으로 갖는 직사각형 상자
		// min(x1, x2)와 max(x1,x2)는 A-B 상자가 가로로 차지하는 영역
		// min(x3, x4)와 max(x3, x4)는 C-D 상자가 가로로 차지하는 영역
		// 두 선분이 겹친다면 상자도 반드시 겹쳐야 함 → BUT 한 상자의 min이 다른 상자의 max보다 크다면 겹칠 수 없음
		// y(세로)에 대해서도 똑같이 적용
	}
	else if (CCW1 * CCW2 <= 0 && CCW3 * CCW4 <= 0) cout << 1; // 검증에 따라 하나는 일직선상으로 나올 수도 있지만 한쪽이 교차로 나오면 (일직선 + 교차)
	else cout << 0;
	return 0;
}

// CCW == 0일 때 간과한 부분 (디버깅 수행)
// (1) A-B 선상에 C나 D가 있는지만 확인했었는데
// (2) C-D 안에 A-B가 있는 경우도 있다 (C -- A -- B -- D 등등)
// (3) 겹치지 않는 경우는 → 한 선분의 min 값이 다른 선분의 max 값보다 클 때
// (4) 다르게 생각하면 한 선분의 min 값이 다른 선분의 max값보다 작거나 같으면 겹친다

// 추가로 상호검증이 필요함
// A-B를 기준으로 C와 D를 판별 + C-D를 기준으로 A와 B를 판별
// 이해는 잘 안되는데 필요하다고 한다 (기준에 따라 달라지니까) → 기하 문제는 상호검증 유무가 정답을 가리기도 함

// 추가로 오버플로우 조심해야 함
// 다루는 숫자가 너무 크다 long long을 써도 오버플로우 날 수 있나봄
// CCW를 서로 곱하는 순간 오버플로우 가능