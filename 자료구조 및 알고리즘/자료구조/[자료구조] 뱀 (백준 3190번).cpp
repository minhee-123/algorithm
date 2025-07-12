// 뱀 (https://www.acmicpc.net/problem/3190)

#include <iostream>
#include <deque> //뱀의 앞뒤로 위치가 추가되는 경향이 있어서 deque 사용 (앞뒤 push가 있음)
#include <utility> //pair 라이브러리
using namespace std;

int N, K, LD; //보드크기, 사과개수, 방향변환횟수
int T = 0; //시간
int idx = 0;
int map[100][100] = { 0 }; //정사각 보드
deque<pair<int, char>> rotation; //회전정보
deque<pair<int, int>> snake; //뱀

int dir = 0;
int dx[4] = { 0, 0, 1, -1 }; 
int dy[4] = { 1, -1, 0, 0 }; 

void Input()
{
	cin >> N >> K;
	for (int i = 0; i < K; i++)
	{
		int x, y;
		cin >> x >> y;
		map[x - 1][y - 1] = 1; //사과 채워넣음 (1로 표시)
	}

	cin >> LD;
	for (int i = 0; i < LD; i++)
	{
		int t; char r;
		cin >> t >> r;
		rotation.push_back({ t, r }); //회전정보 넣음
	}
}

int RotatioN(int di, char ld)
{
	// 0(위) 1(아래) 2(오른쪽) 3(왼쪽)
	if (ld == 'L')
	{
		if (di == 0) return 3;
		else if (di == 1) return 2;
		else if (di == 2) return 0;
		else if (di == 3) return 1;
	}
	else if (ld == 'D')
	{
		if (di == 0) return 2;
		else if (di == 1) return 3;
		else if (di == 2) return 1;
		else if (di == 3) return 0;
	}
}

void Move() //이동
{
	snake.push_back({ 0,0 }); //뱀 출발위치
	map[0][0] = 2; //뱀의 위치 기록 (머리에서 꼬리까지) (2로 표시)

	while (1)
	{
		T++; //매초마다 이동

		//이동
		int mx = snake.front().first + dx[dir];
		int my = snake.front().second + dy[dir];

		//확인
		if ((mx < 0 || mx >= N || my < 0 || my >= N) || map[mx][my] == 2) //부딪히는 경우
		{
			break;
		}
		else if (map[mx][my] == 0) //사과가 없는 경우
		{
			map[mx][my] = 2; //머리 위치 기록
			map[snake.back().first][snake.back().second] = 0; //꼬리 위치가 없어졌으니 기록 삭제
			snake.push_front({ mx, my }); //머리 이동
			snake.pop_back(); //꼬리 자름
		}
		else if (map[mx][my] == 1) //사과가 있는 경우
		{
			map[mx][my] = 2; //머리 위치 기록
			snake.push_front({ mx, my }); //머리 이동
		}

		//회전
		if (idx < rotation.size())
		{
			if (T == rotation[idx].first) //X초가 끝난 뒤에 회전
			{
				dir = RotatioN(dir, rotation[idx].second);
				idx++;
			}
		}
	}
}

int main()
{
	Input();
	Move();

	cout << T;
	return 0;
}

// 회전, 뱀이 움직이는 방향 때문에 2h 이상 살펴봄
// ★X,Y 내가 생각하는 방향과 Map에서 움직이는 방향이 다를 수 있음
// 예시로 dy가 1증가 하는 것을 머리로 생각하면 위로 한칸 가는 것 같지만 → 열이 1 증가, 오른쪽으로 한칸 가는 것과 같음

// 2차원 배열(행렬)과 방향 시뮬레이션에 약함 ★연습필요
// x랑 y라고 하면 헷갈리니까 row, column이라고 써서 연습해도 괜찮을듯