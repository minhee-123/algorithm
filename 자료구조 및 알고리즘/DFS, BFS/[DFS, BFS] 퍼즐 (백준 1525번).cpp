// 문제: https://www.acmicpc.net/problem/1525

// 어떻게 접근해야할지 감도 안 잡혀서 풀이를 참고했다
// 2차원 배열을 1차원으로, 배열이 아닌 string을 사용해서 접근
// 참고한 풀이: https://yabmoons.tistory.com/75

// 1차원의 index를 2차원 값으로 변환 (M은 열의 개수(columns))
// → row = index / M
// → col = index % M

// 2차원 값을 1차원 index로 변환 (M은 열의 개수(columns))
// → index = (row * M) + col

// string 방문 여부를 체크하기 위해 set을 활용했다!
// → 같은 string 상태 (같은 맵 상태)에 대해서 중복 체크하면 안됨
// → 2차원 visit으로는 해결 불가능
// → set을 활용 
// (set은 key와 value가 똑같은 map)
// (중복을 허용하지 않음 - 중복된 값이 들어오면 추가하지 않고 무시)
// (원소를 insert하면 자동으로 정렬해줌 - 자동으로 오름차순 정렬)

// ★ set은 find로 해서 원소가 있는지 확인할 때 많이 사용하니까 기억해두자!

#include <iostream>
#include <string>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

// 빈칸을 0이라고 한다면
// 맵에서 이동할 수 있는 건 0뿐이다
// → 수를 빈칸으로 이동할 수 있음 = 0과 인근의 수 자리를 바꿀 수 있음

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };
set<string> visit;
string answer_string = "123456780"; // 이걸 처음에 890 까지 했다 바보인가

int main()
{
	string Map = "";
	for (int i = 0; i < 9; i++)
	{
		int temp;
		cin >> temp;
		Map += to_string(temp);
	}

	queue<pair<string, int>> que;
	que.push({ Map, 0 });
	visit.insert(Map);

	while (!que.empty())
	{
		string now = que.front().first;
		int nowCNT = que.front().second;

		que.pop();

		if (now == answer_string)
		{
			cout << nowCNT;
			return 0; // 정답을 찾았으니 여기서 종료
		}

		int index = now.find('0'); // 문자가 있는 index 반환 (0의 위치 반환)
		int nowR = index / 3; // 열의 길이 3
		int nowC = index % 3;

		for (int i = 0; i < 4; i++)
		{
			int nextR = nowR + dr[i];
			int nextC = nowC + dc[i];
			string next = now;

			if (nextR < 0 || nextR >= 3 || nextC < 0 || nextC >= 3) continue;

			int nextIndex = nextR * 3 + nextC;
			swap(next[index], next[nextIndex]);

			if (visit.find(next) != visit.end()) continue; // 이미 방문한 Map인 경우 pass

			visit.insert(next);
			que.push({ next, nowCNT + 1 });
		}
	}
	cout << -1;
	return 0;
}