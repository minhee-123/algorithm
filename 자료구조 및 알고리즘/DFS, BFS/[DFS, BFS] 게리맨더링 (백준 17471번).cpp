// 문제: https://www.acmicpc.net/problem/17471
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

int N; // 1번부터 N번까지 존재
int all_people; // 모든 인구 수
vector<int> people;
vector<int> zone[11];

bool visit[11];
bool visit2[11];

int chunk = 0; // 선거구가 처음 몇개로 나누어져있는지
int chunk_people = 0; // 해당 덩어리에 속한 인구수
void DFS_chunk(int num, bool group)
{
	if (visit[num]) return;
	visit[num] = true;

	chunk_people += people[num];
	for (int i = 0; i < zone[num].size(); i++)
	{
		int next = zone[num][i];
		if (visit[next] || visit2[next] != group) continue;
		DFS_chunk(next, group);
	}
}

bool check_group(bool group)
{
	// 그룹 형성이 가능한지 확인
	int S = -1, people_cnt = 0;
	for (int i = 1; i <= N; i++)
	{
		if (visit2[i] == group)
		{
			if (S == -1) S = i;
			people_cnt += people[i];
		}
	}
	if (S == -1) return false;

	memset(visit, false, sizeof(visit));
	chunk_people = 0;
	DFS_chunk(S, group);

	if (chunk_people == people_cnt) return true;
	else return false;
}

int min_answer = 10000; // 두 선거구의 최소 인구수 차이
void make_group(int num) // 조합을 만든다
{
	if (num == N + 1)
	{
		bool flag1 = check_group(true);
		bool flag2 = check_group(false);

		if (flag1 && flag2)
		{
			int peopleA = 0;
			for (int i = 1; i <= N; i++)
			{
				if (visit2[i]) peopleA += people[i];
			}
			int peopleB = all_people - peopleA;

			min_answer = min(min_answer, abs(peopleA - peopleB));
		}

		return;
	}

	visit2[num] = true; // num을 1번과 같은 그룹으로
	make_group(num + 1);

	visit2[num] = false; // num을 1번과 다른 그룹으로
	make_group(num + 1);
}

int main()
{
	cin >> N;
	people.resize(N + 1);
	for (int i = 1; i <= N; i++)
	{
		cin >> people[i];
		all_people += people[i];
	}
	for (int i = 1; i <= N; i++)
	{
		int num; cin >> num;
		for (int j = 0; j < num; j++)
		{
			int temp; cin >> temp;
			zone[i].push_back(temp);
		}
	}

	// 선거구가 처음 어떻게 주어지는지
	vector<int> chunk_cnt;
	for (int i = 1; i <= N; i++)
	{
		chunk_people = 0;
		DFS_chunk(i, false); // 두번째 인자는 아래에서 사용, 현재는 무의미
		// DFS_chunk에서 두번째 인자도 조건으로 넣고 있어서 false를 넣어야 현재는 무사히 넘어감

		if (chunk_people > 0)
		{
			chunk++;
			chunk_cnt.push_back(chunk_people);
		}
	}
	if (chunk >= 3)
	{
		cout << -1;
		return 0;
	}
	else if (chunk == 2)
	{
		int p1 = chunk_cnt[0];
		int p2 = chunk_cnt[1];

		cout << abs(p2 - p1);
		return 0;
	}

	// 선거구가 하나로 연결되어 있는 경우
	// 1번과 같은 구역에 속하는 선거구 vs 1번과 다른 구역에 속하는 선거구
	visit2[1] = true; // visit2로 구역 구분
	make_group(2); // 2번 노드부터 결정

	if (min_answer == 10000) cout << -1;
	else cout << min_answer;
	return 0;
}

// 디버깅 포인트
// 분기형 구조로 생각을 했는데 만약 1번 구역이 중앙에 있고 2번과 3번이 1번과만 연결되어 있다면
// 기존 코드로는 1 → 2 방문 후 2와 연결된 노드로만 가려고 함 (1, 2, 3을 하나의 그룹으로 묶지 못함)

// 방식을 바꿔야 함
// → 1번을 기준으로 조합을 만들어야 함 (1번에 포함, 포함되지 않음)
// → 두 그룹이 연결되고 있는지 확인 (연결이 된다면 min_answer 업데이트 수행)

// 만약 다시 푼다면
// → chunk 부분을 없애도 됨 (어차피 모든 조합을 보고있기 때문에 무의미)
// → 모든 조합을 보는 것으로 깔끔하게 작성