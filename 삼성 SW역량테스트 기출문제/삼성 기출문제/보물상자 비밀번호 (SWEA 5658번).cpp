// SWEA 5658번 보물상자 비밀번호
// 문제: https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRUN9KfZ8DFAUo
// 문제풀이: https://yabmoons.tistory.com/294
// 해쉬맵을 사용하면 풀이가 편안해짐 → 나중에 찾아보자

//#pragma warning (disable: 4996)

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N, K, Line_Num, Answer;
vector<char> V[4];
vector<int> Result;

void Initialize() // 한 번 초기화
{
	for (int i = 0; i < 4; i++)
	{
		V[i].clear();
	}
	Result.clear();
	Answer = 0;
}

void Input()
{
	cin >> N >> K;
	string Inp;
	cin >> Inp;
	Line_Num = N / 4; // 한 변에 들어갈 수 있는 숫자의 갯수 파악
	int Idx = 0;
	int Cnt = 0;

	for (int i = 0; i < Inp.size(); i++)
	{
		char Tmp = Inp[i];

		V[Idx].push_back(Tmp);
		Cnt++;
		if (Cnt == Line_Num)
		{
			Idx++;
			Cnt = 0;
		}
	}
}

void Turning()
{
	char Start = V[0].at(0);
	char Tail = V[3].at(Line_Num - 1);

	// 첫 번째 변의 첫 번째 값과 마지막 값을 계속해서 Swap 하면 한 칸씩 회전시킨 것과 같은 효과를 얻음
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < Line_Num; j++)
		{
			swap(V[0].at(0), V[i].at(j));
		}
	}
	V[0].at(0) = Tail;
}

bool Find_Data(int d)
{
	for (int i = 0; i < Result.size(); i++)
	{
		if (Result[i] == d) return true;
	}
	return false;
}

void Calculate_Value()
{
	// 16진수로 10진수로 변환하는 과정 (문제는 이해가 좀 안되는 함수)
	for (int i = 0; i < 4; i++)
	{
		int p = Line_Num - 1;
		int Sum = 0;
		for (int j = 0; j < V[i].size(); j++)
		{
			char c = V[i].at(j);
			int Tmp;
			if ('0' <= c && c <= '9') Tmp = c - '0';
			else if ('A' <= c && c <= 'F') Tmp = (c - 'A') + 10;

			int Sixteen = 1;

			for (int k = 0; k < p; k++) Sixteen = Sixteen * 16;

			Sum = Sum + Sixteen * Tmp;
			p--;
		}

		// 중복된 값이 없으면 저장
		if (Find_Data(Sum) == false) Result.push_back(Sum);
	}
}

bool desc(int a, int b) { return a > b; }

void Solution()
{
	Calculate_Value();

	for (int i = 0; i < Line_Num; i++)
	{
		Turning();
		Calculate_Value();
	}

	sort(Result.begin(), Result.end(), desc);
	Answer = Result[K - 1];
}

void Solve()
{
	int Tc; cin >> Tc;
	for (int T = 1; T <= Tc; T++)
	{
		Initialize();
		Input();
		Solution();

		cout << "#" << T << " " << Answer << "\n";
	}
}

int main()
{
	ios::sync_with_stdio;
	cout.tie(NULL);
	cin.tie(NULL);

	//freopen("Input.txt", "r", stdin);

	Solve();
	return 0;
}