// 문제: https://www.acmicpc.net/problem/12867
// 알고리즘: 좌표압축 및 스위핑
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct INDEX
{
	int origin;
	int location;
	int compression; // M은 최대 50이므로 compression의 최대값도 50
};
vector<INDEX> M_index; // 여행계획에서 고른 좌표의 인덱스 값

int N, M; // N의 최대값은 10^9
int value[51]; // 현재 방문 위치 (시작점 100)
int history[51][51];  // 과거 방문 내역

bool comp_origin(INDEX A, INDEX B) { return A.origin < B.origin; }
bool comp_location(INDEX A, INDEX B) { return A.location < B.location; }

int main()
{
	cin >> N >> M;
	M_index.resize(M);

	for (int i = 0; i < M; i++)
	{
		cin >> M_index[i].origin;
		M_index[i].location = i;
	}
	sort(M_index.begin(), M_index.end(), comp_origin);

	// 차원 압축
	int idx = -1;
	int pre_num = -1;
	for (int i = 0; i < M; i++)
	{
		if (pre_num == M_index[i].origin) M_index[i].compression = idx;
		else
		{
			idx++;
			M_index[i].compression = idx;
			pre_num = M_index[i].origin;
		}
	}
	sort(M_index.begin(), M_index.end(), comp_location);

	// 정답 찾기
	int answer = 1;
	for (int i = 0; i < M; i++)
	{
		value[i] = 100;
		history[0][i] = 100; // 모든 차원의 시작 위치는 100
	}

	for (int i = 0; i < M; i++)
	{
		char command;
		cin >> command;

		int dimension = M_index[i].compression;
		int now_value = value[dimension];

		if (command == '+') now_value++;
		else now_value--;
		value[dimension] = now_value;

		// 과거에 방문한 적 있는 조합인지 확인
		for (int j = 0; j < i; j++)
		{
			bool visit = true;
			for (int k = 0; k < M; k++)
			{
				if (history[j][k] != value[k])
				{
					visit = false;
					break;
				}
			}

			if (visit)
			{
				answer = 0;
				break;
			}
		}

		if (answer == 0) break;
		for (int k = 0; k < M; k++) history[i + 1][k] = value[k]; // 초기값을 history[0]에 저장하고 있기 때문에 history[i+1]에 저장해야 함
	}

	cout << answer;
	return 0;
}

// 실버 2라는데 실화냐 너무 어려운데
// 만약 M의 범위가 5000정도만 되었어도 무조건 Map이나 Hash를 써야했을 거라고 함 (시간초과)
// 조합 중복 여부도 map을 이용 (key 값으로 vector를 사용해서, 나중에 find 하면 됨)
// ★ 이때 주의할 것은 hash는 key 값으로 vector를 사용할 수 없음 (hash는 복합 자료구조(vector, pair, struct)를 지원하지 않음)

// ★ map을 이용한 좌표압축 (map은 내부에서 자동 정렬 + 중복은 자동 제거)
// (1) 등장하는 모든 좌표를 map의 key 값으로 넣음 (value는 0으로)(중복은 map이 알아서 제거)
// (2) iterator를 이용해서 순회하며 번호매기기 (map 내부에서 자동 정렬되어서 순서대로 나옴)
//     (참고로 map<int, int>::iterator it; 선언하고 it->second = idx++; 이런식으로 넣어줘야 함)

// ★ hash(unordered_map)를 이용해서도 구현할 수 있음
// 단 hash는 내부에서 자동으로 정렬되지 않기 때문에 압축할 때 순서가 상관없다면 사용해야 함
// (1) 원하는 값이 hash 내에 있는지 확인 (hash_map.find(val) == hash_map.end())
// (2) 만약 없다면 현재 인덱스를 부여하고 증가 (iterator를 사용하지 않음, 어차피 오름차순으로 매길 수 없기 때문)