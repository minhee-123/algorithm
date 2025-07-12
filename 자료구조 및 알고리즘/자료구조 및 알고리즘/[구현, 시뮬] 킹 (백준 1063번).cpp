// 킹 (https://www.acmicpc.net/problem/1063)
//알파벳 - 열 (왼쪽 오른쪽) (가장 왼쪽이 A, 가장 오른쪽이 H)
//숫자 - 행 (아래 위) (가장 아래가 0, 가장 위가 7)

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int MAP[8][8] = { 0 }; //체스판 (행/열)
int N; //명령 횟수
pair<char, int> king; //킹
pair<char, int> rock; //돌
vector<string> command; //명령 모음
int kr, kc, rr, rc; //r(행) c(열)

int dr[8] = { 0, 0, -1, 1, 1, 1, -1, -1 }; //R, L, B, T, RT, LT, RB, LB
int dc[8] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int Ch_In(char ch)
{
	for (int i = 0; i < 8; i++)
	{
		if (ch == 'A' + i) return i;
	}
}

char In_Ch(int in)
{
	for (int i = 0; i < 8; i++)
	{
		if (in == i) return 'A' + i;
	}
}

int com_dir(string com)
{
	if (com == "R") return 0;
	else if (com == "L") return 1;
	else if (com == "B") return 2;
	else if (com == "T") return 3;
	else if (com == "RT") return 4;
	else if (com == "LT") return 5;
	else if (com == "RB") return 6;
	else if (com == "LB") return 7;
}

void Input()
{
	cin >> king.first >> king.second;
	cin >> rock.first >> rock.second;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		string temp;
		cin >> temp;
		command.push_back(temp);
	}

	kr = king.second - 1;
	rr = rock.second - 1;
	kc = Ch_In(king.first);
	rc = Ch_In(rock.first);
}

void Solution()
{
	int K_C = kc, R_C = rc, K_R = kr, R_R = rr;
	for (int i = 0; i < N; i++)
	{
		K_R = kr + dr[com_dir(command[i])];
		K_C = kc + dc[com_dir(command[i])];
		if (K_R < 0 || K_R > 7 || K_C < 0 || K_C > 7) continue;
		else
		{
			if (K_R == rr && K_C == rc)
			{
				R_R = rr + dr[com_dir(command[i])];
				R_C = rc + dc[com_dir(command[i])];
				if (R_R < 0 || R_R > 7 || R_C < 0 || R_C >7) continue;
				
				kr = K_R;
				kc = K_C;
				rr = R_R;
				rc = R_C;
			}
			else
			{
				kr = K_R;
				kc = K_C;
			}
		} //처음에 짰던 알고리즘에서 순서만 약간 수정했더니 맞았음 (if문으로 과정을 쪼갰을 뿐임 → 구현/시뮬에서 틀린다면 과정을 쪼개도 괜찮을 듯)
	}

	king.first = In_Ch(kc);
	king.second = kr + 1;
	rock.first = In_Ch(rc);
	rock.second = rr + 1;
}

int main()
{
	Input();
	Solution();

	cout << king.first << king.second << '\n';
	cout << rock.first << rock.second;
	return 0;
}