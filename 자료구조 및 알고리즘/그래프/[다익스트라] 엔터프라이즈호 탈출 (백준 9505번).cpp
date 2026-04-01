// 문제: https://www.acmicpc.net/problem/9505
#include <iostream>
#include <queue>
#include <string>
#include <cstring>
#include <map>
using namespace std;

int T, K, W, H;
map<char, int> Kling; // 클링온 전투선의 정보

int Map[1000][1000];
int Dist[1000][1000];
bool visit[1000][1000];

int SR, SC; // 엔터프라이즈 호의 시작 위치

void Input()
{
	cin >> K >> W >> H;
	Kling.clear();
	memset(Map, 0, sizeof(Map));
	memset(visit, 0, sizeof(visit));

	for (int i = 0; i < K; i++)
	{
		char Name; int Time;
		cin >> Name >> Time;
		Kling[Name] = Time;
	}

	for (int i = 0; i < H; i++)
	{
		string temp;
		cin >> temp;
		for (int j = 0; j < W; j++)
		{
			Dist[i][j] = 1000000000;

			char ch = temp[j];
			if (ch == 'E')
			{
				SR = i;
				SC = j;
				continue;
			}
			else Map[i][j] = Kling[ch];
		}
	}
}

struct INFORM
{
	int R;
	int C;
	int Time;
	bool operator()(INFORM A, INFORM B) { return A.Time > B.Time; } // 오름차순 정렬
};

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

void Solution()
{
	Input();

	priority_queue<INFORM, vector<INFORM>, INFORM> que;
	que.push({ SR, SC, 0 });

	while (!que.empty())
	{
		int R = que.top().R;
		int C = que.top().C;
		int Time = que.top().Time;
		que.pop();

		if (visit[R][C]) continue;
		visit[R][C] = true;

		if (R == 0 || C == 0 || R == H - 1 || C == W - 1) // 탈출 조건은 테두리 (H-1이랑 W-1도 포함해야 함!!)
		{
			cout << Time << '\n';
			return;
		}

		for (int i = 0; i < 4; i++)
		{
			int NR = R + dr[i];
			int NC = C + dc[i];
			
			if (NR < 0 || NR >= H || NC < 0 || NC >= W) continue;
			if (Dist[NR][NC] > Time + Map[NR][NC])
			{
				Dist[NR][NC] = Time + Map[NR][NC];
				que.push({ NR, NC, Dist[NR][NC] });
			}
		}
	}
}

int main()
{
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		Solution();
	}
	return 0;
}