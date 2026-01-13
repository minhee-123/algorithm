// 문제: https://www.acmicpc.net/problem/2866
// 알고리즘: 문자열 + 자료구조
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// DP가 아닌 것 같은데 혹시 DP인가 싶어서 알고리즘 유형을 확인해버림
// 좌표압축에서도 활용했지만 map, hash, set 의 특성을 이해하고 있어야 함
// → 중복된 key 값을 허용하지 않음 (중복된 값을 거를 수 있다!)
// → 값이 중복되는지를 따지는 문제에서는 map, hash, set을 유용하게 사용할 수 있다!

int R, C;
char Map[1000][1000];

bool check_duple(int k) // k행까지 지웠다면
{
	unordered_map<string, int> hm;
	for (int col = 0; col < C; col++)
	{
		string st = "";
		for (int row = k + 1; row < R; row++) st += Map[row][col];

		if (hm.find(st) != hm.end()) return false; // 중복 발생
		hm[st] = 0;
	}
	return true;
}

int main()
{
	cin >> R >> C;
	for (int i = 0; i < R; i++)
	{
		string st;
		cin >> st;
		for (int j = 0; j < C; j++) Map[i][j] = st[j];
	}

	int s = 0;
	int e = R - 1;

	while (s <= e)
	{
		int mid = (s + e) / 2;
		bool check = check_duple(mid); // mid행까지 지울 수 있는가

		if (check) s = mid + 1; // k행까지 지울 수 있음 (더 지우는 것을 시도)
		else e = mid - 1; // k행까지 지울 수 없음 (덜 지우는 것을 시도)
	} // s행까지 지울 수 있음 (0부터 R-1까지 범위)

	cout << s; // count는 결국 몇행까지 지울 수 있냐와 같음 (시작이 0행이라는 전제하에)
	return 0;
}

// 첫시도 → 시간초과 발생
// 문제에서 제시한 그대로 시뮬레이션했는데
// while문을 돌리고 그 안에서 문자열을 매번 만들어서 해시맵에 넣음
// → 최악의 경우 10^3 * 10^3 * 10^3 = 10^9 의 시간복잡도 발생

// 이렇게 시간이 터지겠다 싶은 건 이분탐색을 도입해야 함!
// 이분탐색은 log의 시간복잡도를 가짐 → 배열값이든 인덱스든 오름차순으로 있다면 사용가능
// 현재 문제도 생각해보면 k행까지 지웠을 때 중복이 없다면 k-1행까지 지워도 중복이 없음
// → 이런 점을 이용하면 시간을 확 단축할 수 있음 (mid개의 행을 지웠을 때 중복이 있는가)

// 이분탐색: s와 e 중에서 무엇을 정답으로 가져와야 하는가
// s(start)는 해당 값까지 중복이 없을 가능성이 있는 최소 경계 (중복이 발생하는 지점에서 멈춤)
// e(end)는 해당 값까지 중복이 없을 가능성이 있는 최대 경계 (중복이 없는 최대 지점에서 멈춤)
// s = e + 1 일때 끝남 → 정의대로라면 e가 정답이어야 하지만 check_dupl에서 k+1부터 검사(k행까지 지웠다고 따짐)하기 때문에 s가 정답이 됨

// 보통 e는 조건을 만족하는 최대값(성공한 최대값), s는 조건을 만족하지 않는 첫번째 값(실패한 최소값)을 나타내서
// e가 정답인 경우가 많음 BUT 내가 어떻게 푸냐, 문제에서 정확히 요구하는게 뭐냐에 따라 달라짐
// → 헷갈린다면 answer 변수를 따로 만들어서 관리하거나 최소/최대 경계 케이스로 따져보기