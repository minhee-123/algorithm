// 리모컨 (https://www.acmicpc.net/problem/1107)

//처음에는 가장 가까운 채널을 찾는 재귀함수를 만들어서 풀었는데 
//메모리 초과 발생 → 재귀적 호출을 통해 너무 많은 함수들을 호출할 경우 메모리 초과가 발생함)

//재귀함수를 사용하지 않고 품
//1. 채널 100번에서 +, -를 통해 직접 움직이는 방법의 cnt
//2. 숫자 버튼 조작을 한 후 +, - 이동을 통해 움직이는 방법의 cnt (누를 수 있는 모든 채널에 대해 해봄)
//3. 두 방법 중 더 적게 움직이는 것을 출력

#include <iostream>
using namespace std;

int N_start = 100;
bool button[10] = { false }; //전체 기본 false (고장나지 않은 경우)

int channel_move(int move) //채널 이동이 가능할 경우 버튼을 몇번 눌렀는지 count
{
	if (move == 0) //0번 채널로 이동하는 경우
	{
		if (button[move]) return 0;
		else return 1;
	}

	int cnt = 0;
	while (move) //0번 외의 채널로 이동하는 경우
	{
		if (button[move % 10]) return 0;
		cnt++;
		move = move / 10;
	}
	return cnt;
}

int main()
{
	int N, M;
	cin >> N;
	cin >> M;
	for (int i = 0; i < M; i++)
	{
		int temp;
		cin >> temp;
		button[temp] = true; //고장난 버튼은 true로 기록
	}

	int cnt = 0;
	cnt = abs(N - N_start);

	for (int i = 0; i < 1000000; i++) //모든 채널로 이동해서 cnt 계산 (N이 최대 500000이니까 0에서 500000, 1000000에서 500000이 같은 것을 고려해 1000000까지 반복문)
	{
		int can_move = channel_move(i);
		if (can_move > 0) //채널 이동이 가능한 경우
		{
			int cnt_temp = can_move + abs(N - i);
			if (cnt_temp < cnt) cnt = cnt_temp;
		}
	}
	
	cout << cnt;
	return 0;
}