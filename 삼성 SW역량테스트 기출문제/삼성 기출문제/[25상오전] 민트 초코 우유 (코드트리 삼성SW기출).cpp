// 코드트리 삼성 SW 역량테스트 2025 상반기 오전 1번 문제
// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/mint-choco-milk/description

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

struct Student
{
	int row = 0;
	int col = 0;
	int B = 0; //신앙심

	bool T = false; //민트 선호 여부
	bool C = false; //초코 선호 여부
	bool M = false; //우유 선호 여부
	string F = ""; //신봉하는 음식
};

int N, T;
Student Map[50][50];
bool visit[50][50];

vector<vector<Student>> Group;
vector<Student> Attacker;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void Update_F(int row, int col) //신봉하는 음식 업데이트
{
	bool flagT = Map[row][col].T;
	bool flagC = Map[row][col].C;
	bool flagM = Map[row][col].M;

	if (flagT && !flagC && !flagM) Map[row][col].F = "T";
	else if (!flagT && flagC && !flagM) Map[row][col].F = "C";
	else if (!flagT && !flagC && flagM) Map[row][col].F = "M";
	else if (flagT && flagC && !flagM) Map[row][col].F = "TC";
	else if (flagT && !flagC && flagM) Map[row][col].F = "TM";
	else if (!flagT && flagC && flagM) Map[row][col].F = "CM";
	else Map[row][col].F = "TCM";
}


// 1. 입력

void Input()
{
	cin >> N >> T;

	for (int i = 0; i < N; i++)
	{
		string temp;
		cin >> temp;

		for (int j = 0; j < N; j++)
		{
			char tp = temp[j];
			
			if (tp == 'T') Map[i][j] = { i, j, 0, true, false, false, "T" };
			else if (tp == 'C') Map[i][j] = {i, j, 0, false, true, false, "C"};
			else if (tp == 'M') Map[i][j] = {i, j, 0, false, false, true, "M"};
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) cin >> Map[i][j].B;
	}
}


// 2. 그룹 형성 + 대표자 선정 + 대표자 순서 결정

vector<Student> temp;
void DFS(int R, int C)
{
	if (visit[R][C]) return;

	visit[R][C] = true;
	temp.push_back(Map[R][C]); //그룹 합류

	for (int i = 0; i < 4; i++)
	{
		int nextR = R + dr[i];
		int nextC = C + dc[i];

		if (nextR < 0 || nextR >= N || nextC < 0 || nextC >= N) continue;
		if (visit[nextR][nextC]) continue;

		if (Map[R][C].F == Map[nextR][nextC].F) DFS(nextR, nextC);
	}
}

bool comp_group (Student A, Student B)
{
	if (A.B != B.B) return A.B > B.B;
	else
	{
		if (A.row != B.row) return A.row < B.row;
		else return A.col < B.col;
	}
}

bool comp_attacker(Student A, Student B)
{
	bool A1 = false, A2 = false, A3 = false;
	bool B1 = false, B2 = false, B3 = false;

	if (A.F == "T" || A.F == "C" || A.F == "M") A1 = true;
	else if (A.F == "TM" || A.F == "TC" || A.F == "CM") A2 = true;
	else A3 = true;

	if (B.F == "T" || B.F == "C" || B.F == "M") B1 = true;
	else if (B.F == "TM" || B.F == "TC" || B.F == "CM") B2 = true;
	else B3 = true;

	// 단일, 이중, 삼중 소속이 다를 경우
	if (A1 && !B1) return true;
	if (!A1 && B1) return false;
	if (A2 && !B2) return true;
	if (!A2 && B2) return false;

	// 단일, 이중, 삼중 소속이 같을 경우
	if (A.B != B.B) return A.B > B.B;
	else
	{
		if (A.row != B.row) return A.row < B.row;
		else return A.col < B.col;
	}
}

void Make_group()
{
	memset(visit, false, sizeof(visit));
	Group.clear();
	Attacker.clear();

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			temp.clear();
			DFS(i, j);

			if (temp.empty()) continue; //비어있으면 패스 (그룹형성X)
			else Group.push_back(temp);
		}
	}

	for (int i = 0; i < Group.size(); i++)
	{
		sort(Group[i].begin(), Group[i].end(), comp_group); //그룹대표 선정
		
		int R = Group[i][0].row;
		int C = Group[i][0].col;
		
		Map[R][C].B += Group[i].size();
		Attacker.push_back(Map[R][C]); //대표자로 넣어둠
	}

	sort(Attacker.begin(), Attacker.end(), comp_attacker);
}


// 3. 전파 + 맵 업데이트 + 정답 출력
void Attack()
{
	memset(visit, false, sizeof(visit));
	for (int i = 0; i < Attacker.size(); i++)
	{
		int R = Attacker[i].row;
		int C = Attacker[i].col;
		if (visit[R][C]) continue; //전파를 당했다면 전파 불가능

		int X = Map[R][C].B - 1;
		int dir = Map[R][C].B % 4;
		Map[R][C].B = 1;

		int NR = R;
		int NC = C;

		while (1)
		{
			NR += dr[dir];
			NC += dc[dir];
			if (NR < 0 || NR >= N || NC < 0 || NC >= N) break; //격자 밖으로 나가는 경우
			if (Map[NR][NC].F == Map[R][C].F) continue; //같은 신봉자면 전파를 수행하지 않음

			int Y = Map[NR][NC].B;
			if (X > Y) //강한 전파
			{
				X -= (Y + 1);
				Map[NR][NC].B++;

				Map[NR][NC].T = Map[R][C].T;
				Map[NR][NC].C = Map[R][C].C;
				Map[NR][NC].M = Map[R][C].M; //같은 음식을 선호

				Update_F(NR, NC);
				visit[NR][NC] = true;
			}
			else //약한 전파
			{
				Map[NR][NC].B += X;
				X = 0;

				Map[NR][NC].T = Map[R][C].T || Map[NR][NC].T;
				Map[NR][NC].C = Map[R][C].C || Map[NR][NC].C;
				Map[NR][NC].M = Map[R][C].M || Map[NR][NC].M;

				Update_F(NR, NC);
				visit[NR][NC] = true;
			}

			if (X <= 0) break; //간절함이 0이 되면 종료
		}
	}
}

vector<int> answer;
void Update_map()
{
	answer.clear();
	answer.resize(7, 0);
	// TCM, TC, TM, CM, M, C, T

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{ 
			int B = Map[i][j].B;
			string F = Map[i][j].F;

			if (F == "TCM") answer[0] += B;
			else if (F == "TC") answer[1] += B;
			else if (F == "TM") answer[2] += B;
			else if (F == "CM") answer[3] += B;
			else if (F == "M") answer[4] += B;
			else if (F == "C") answer[5] += B;
			else if (F == "T") answer[6] += B;
		}
	}

	for (int i = 0; i < 7; i++) cout << answer[i] << " ";
	cout << '\n';
}


// Main solution

int main()
{
	Input();
	for (int i = 0; i < T; i++)
	{
		Make_group();
		Attack();
		Update_map();
	}
	return 0;
}


// 디버깅 메모
// (1)
// AND로 처리해야 하는 것을 OR로 처리해서 디버깅이 오래 걸렸음
// 정신 차리자...

// ★★★ 나중에는 비트마스크를 활용해보자
// TCM 관리는 비트마스크를 사용하면 편리함
// → 비트 3개(000)로 관리하면 됨 (OR 연산을 쓰면 바로 110으로 바꿔서 관리할 수 있음)