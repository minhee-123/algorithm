// 문제: https://www.acmicpc.net/problem/17472
#include <iostream>
#include <queue>
using namespace std;

struct island
{
	int index1;
	int index2;
	int bridge_len;
};

struct comp
{
	bool operator()(island a, island b)
	{
		return a.bridge_len > b.bridge_len; //오름차순 정렬
	}
};

int N, M;
int UF[10]; //Union-Find 배열
int mount_cnt = 0; //총 섬의 개수
int map[10][10]; //map 정보 저장 (숫자로 섬 구분)
priority_queue<island, vector<island>, comp> edges; //에지리스트

int dr[4] = { 1, -1, 0, 0 }; //row 이동
int dc[4] = { 0, 0, 1, -1 }; //col 이동

bool visit[10][10]; //DFS용 방문 배열
int cnt = 0; //DFS용 count
int label = 1; //숫자로 섬을 구분하기 위해서 사용
void DFS(int row, int col)
{
	if (map[row][col] == 0) return;
	if (visit[row][col]) return;

	map[row][col] = label;
	visit[row][col] = true;
	cnt++;

	for (int i = 0; i < 4; i++)
	{
		int next_row = row + dr[i];
		int next_col = col + dc[i];

		if (next_row < 0 || next_row >= N || next_col < 0 || next_col >= M) continue;
		if (map[next_row][next_col] == 0) continue;
		if (visit[next_row][next_col]) continue;
		DFS(next_row, next_col);
	}
}

int Find(int c)
{
	if (UF[c] == c) return c;
	else return UF[c] = Find(UF[c]);
}

void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);
	if (a != b) UF[b] = a;
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) cin >> map[i][j];
	}

	// (1) 섬의 정보 파악
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cnt = 0;
			DFS(i, j);

			if (cnt > 0)
			{
				mount_cnt++;
				label++;
			}
		}
	}
	for (int i = 1; i <= mount_cnt; i++) UF[i] = i; //Union-Find 배열 초기화

	// (2) 다리 길이로 에지리스트 생성
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j] == 0) continue;
			int idx1 = map[i][j];

			for (int k = 0; k < 4; k++)
			{
				int idx2 = idx1;
				int bridge_cnt = 0;

				int next_r = i + dr[k];
				int next_c = j + dc[k];

				while (1)
				{
					if (next_r < 0 || next_r >= N || next_c < 0 || next_c >= M) break;
					if (map[next_r][next_c] == idx1) break;

					if (map[next_r][next_c] == 0) bridge_cnt++;
					else //다른 섬에 도착
					{
						idx2 = map[next_r][next_c];
						break;
					}

					next_r += dr[k];
					next_c += dc[k];
				}

				if (bridge_cnt > 1 && idx1 != idx2) edges.push({ idx1, idx2, bridge_cnt });
			}
		}
	}

	// (3) 최소 신장 트리 수행 (다리 길이를 최소로 해서 모든 섬을 연결)
	int answer = 0;
	int connect = 0;
	while (connect < mount_cnt - 1)
	{
		if (edges.empty()) break; //edges가 비어있다면 break;
		island temp = edges.top();
		edges.pop();

		if (Find(temp.index1) == Find(temp.index2)) continue;
		else
		{
			Union(temp.index1, temp.index2);
			answer += temp.bridge_len;
			connect++;
		}
	}

	// (4) 결과
	if (connect < mount_cnt - 1) cout << -1; //연결이 되지 못한 경우
	else cout << answer;
	return 0;
}