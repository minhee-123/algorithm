// 백준 20056번 마법사 상어와 파이어볼
// 문제: https://www.acmicpc.net/problem/20056
// 문제풀이: https://yabmoons.tistory.com/600

#include <iostream>
#include <vector>

// freopen을 사용해서 발생하는 C4996 경고를 무시 (freopen 함수가 C++11 이후의 표준에서 사용하지 않는 것을 권장하기 때문에 에러 발생)
//#pragma warning(disable: 4996)

#define MAX 55 // N <= 50이지만 입력받는 데이터의 행렬이 1로 시작, 프로그램은 index가 0으로 시작하기 때문에 여유공간 필요
#define endl "\n"
using namespace std;

struct FIREBALL
{
	int x;
	int y;
	int Massive;
	int Speed;
	int Dir;
}; // 파이어볼을 관리하는 구조체

int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 }; // x축 이동방향
int dy[] = { 0, 1, 1, 1, 0, -1, -1, -1 }; // y축 이동방향
int T_Dir[] = { 0, 2, 4, 6 }; // 합쳐지는 파이어볼의 방향 변경 (모두 홀수 또는 짝수)
int F_Dir[] = { 1, 3, 5, 7 }; // 합쳐지는 파이어볼의 방향 변경 (그 외)

int N, M, K; // 격자 크기, 파이어볼 개수, 이동 횟수 변수 선언
vector<FIREBALL> MAP[MAX][MAX]; // 맵 변수 선언 (한 칸에 여러개의 값을 가짐, 값의 정보가 파이어볼)
vector<FIREBALL> FireBall; // 파이어볼 변수 선언

void Input() // 입력을 받는 함수
{
	cin >> N >> M >> K; // 격자 크기, 파이어볼 개수, 이동 횟수 입력 받음
	for (int i = 0; i < M; i++) // M개의 파이어볼
	{
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d;
		FireBall.push_back({ r, c, m, s, d }); // 각 파이어볼의 정보를 저장
		MAP[r][c].push_back({ r, c, m, s, d });
	}
}

void Move_Fireball() // 파이어볼을 1번 이동시키는 함수 (1번의 이동으로 속력 s만큼 움직임)
{
	for (int i = 1; i <= N; i++) // 파이어볼의 위치는 1~N 행렬 사이에 있음
	{
		for (int j = 1; j <= N; j++)
		{
			MAP[i][j].clear(); // 파이어볼 이동 전 맵 초기화
		}
	}

	for (int i = 0; i < FireBall.size(); i++)
	{
		int x = FireBall[i].x;
		int y = FireBall[i].y;
		int Mass = FireBall[i].Massive;
		int Speed = FireBall[i].Speed;
		int Dir = FireBall[i].Dir; // 파이어볼 정보를 가져옴

		int Move = Speed % N; // 현재 속력으로 움직이게 되면 속력/N 만큼 자기 자리에 위치, 속력%N 만큼 움직이면 됨
		int nx = x + dx[Dir] * Move; // 기존 위치에서 파이어볼 방향으로 이동
		int ny = y + dy[Dir] * Move; // 기존 위치에서 파이어볼 방향으로 이동
		if (nx > N) nx -= N; // 위치가 격자 크기를 넘어가게 될 경우 N을 빼주면 됨
		if (ny > N) ny -= N; // 위치가 격자 크기를 넘어가게 될 경우 N을 빼주면 됨
		if (nx < 1) nx += N; // 위치가 0 이하가 될 경우 N을 더해주면 됨
		if (ny < 1) ny += N; // 위치가 0 이하가 될 경우 N을 더해주면 됨

		MAP[nx][ny].push_back({ nx, ny, Mass, Speed, Dir }); // 파이어볼 이동
		FireBall[i].x = nx; // 파이어볼 위치 업데이트
		FireBall[i].y = ny; // 파이어볼 위치 업데이트
	}
}

void Sum_FireBall() // 한 칸에 파이어볼이 2개 이상 있을 때 연산 함수
{
	vector<FIREBALL> Temp; // 계산용으로 사용하는 임의변수
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			int Cnt = MAP[i][j].size(); // 해당 칸에 존재하는 파이어볼의 개수

			if (Cnt == 0) continue; // 해당 칸에 아무것도 없을 경우 다음 반복문으로
			if (Cnt == 1)
			{
				Temp.push_back(MAP[i][j][0]);
				continue; // 해당 칸에 파이어볼이 1개 있을 때 임의 변수에 값을 추가하고 다음 반복문으로
			}

			// 해당 칸에 파이어볼이 1개 이상 있을 때
			int Massive_Sum = 0;
			int Speed_Sum = 0;
			bool Even = true; // 짝수 (쩐체 방향 체크에 사용)
			bool Odd = true; // 홀수 (전체 방향 체크에 사용)

			for (int k = 0; k < Cnt; k++) // 해당 칸에 파이어볼의 개수만큼 반복
			{
				Massive_Sum += MAP[i][j][k].Massive;
				Speed_Sum += MAP[i][j][k].Speed;
				if (MAP[i][j][k].Dir % 2 == 0) Odd = false; // 방향이 짝수면 odd false (한 번이라도 짝수 방향이 나오면 odd가 false가 됨)
				else Even = false; // 방향이 홀수면 even false (한 번이라도 홀수 방향이 나오면 even이 false가 됨)
			}

			int Mass = Massive_Sum / 5;
			int Speed = Speed_Sum / Cnt;
			if (Mass > 0) // 질량이 0보다 크게 나누어지는 파이어볼에 대해서 임의변수 값 추가 (질량이 0이 된 유령 파이어볼들은 소멸된다!!!!)
			{
				if (Even == true || Odd == true) // 방향이 모두 홀수이거나 모두 짝수인 상황 (방향을 짝수로 저장)
				{
					// 4개의 파이어볼로 나누어져서 임의변수에 값 추가
					for (int k = 0; k < 4; k++) Temp.push_back({ i,j, Mass, Speed, T_Dir[k] });
				}
				else // 방향에 홀수와 짝수가 섞여있는 상황 (방향을 홀수로 저장)
				{
					for (int k = 0; k < 4; k++) Temp.push_back({ i,j, Mass, Speed, F_Dir[k] });
				}
			}
		}
	}
	FireBall = Temp; // 파이어볼 정보 업데이트 (같은 칸에 2개 이상 파이어볼이 있는 것을 합쳐서 4개로 쪼갰음)
}

void Solution() // K번 이동을 실행하고 답을 출력하는 함수 (문제풀이)
{
	for (int i = 0; i < K; i++) // 사용자에게 입력받은 K번 반복
	{
		Move_Fireball(); // 파이어볼 1번 이동 실행
		Sum_FireBall(); // 1번 이동하고 한 칸에 여러개의 파이어볼이 있을 경우를 생각해서 연산 실행 (정리)
	}

	int Answer = 0;
	for (int i = 0; i < FireBall.size(); i++) Answer += FireBall[i].Massive; // 답 계산
	cout << Answer << endl; // 출력
}

void Solve()
{
	Input(); // 입력
	Solution(); // 문제풀이
}

int main(void)
{
	// 성능 향상
	ios::sync_with_stdio(false); // C++의 표준 입출력 스트림과 C의 표준 입출력 함수의 동기화를 해체 (C++의 'iostream' 라이브러리를 더 효율적으로 사용)
	cin.tie(NULL); // C++의 입출력 버퍼를 끊음 (cin과 cout이 함께 동작하여 사용되는 것을 중지)
	cout.tie(NULL); // C++의 입출력 버퍼를 끊음 (cout과 cin이 함께 동작하여 사용되는 것을 중지) -> 서로의 입출력 동작에 영향을 주지 않음

	// [표준 입력 스트림(stdin)을 파일 "Input.txt"로 디렉션]
	// 일반적으로 C++ 프로그램에서 표준 입력 스트림은 키보드로부터의 입력을 받음
	// 그러나 아래의 명령을 사용하면 프로그램이 파일 "Input.txt"에서 입력을 받도록 변경됨
	// → 아래의 명령어를 사용하면 프로그램에서 키보드 대신 파일("Input.txt")을 입력 소스로 사용하게 됨
	//(void) freopen("Input.txt", "r", stdin);

	Solve();

	//fclose(stdin); // 표준 입출력을 되돌려 놓음
	return 0;
}