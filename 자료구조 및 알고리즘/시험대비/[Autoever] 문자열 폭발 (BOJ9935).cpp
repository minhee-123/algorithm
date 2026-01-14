// 문제: https://www.acmicpc.net/problem/9935
// 알고리즘: 수열 압축(코테 기출)과 유사
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string origin;
string bomb;
vector<char> bomb_element;
vector<char> result;

int main()
{
	cin >> origin;
	cin >> bomb;

	bomb_element.resize(bomb.size());
	for (int i = 0; i < bomb.length(); i++) bomb_element[i] = bomb[i];

	for (int i = 0; i < origin.length(); i++)
	{
		result.push_back(origin[i]);
		if (result.size() < bomb.size()) continue; // 폭발 문자열보다 작으면 continue

		bool can_bomb = true;
		int re_idx = result.size() - 1;
		int bo_idx = bomb.size() - 1;
		
		while (bo_idx >= 0 && re_idx >= 0) // 폭발 유무를 확인
		{
			if (result[re_idx] != bomb[bo_idx])
			{
				can_bomb = false;
				break;
			}
			re_idx--;
			bo_idx--;
		}

		if (can_bomb) // 문자열 폭발
		{
			bo_idx = bomb.size() - 1;
			while (bo_idx >= 0)
			{
				result.pop_back();
				bo_idx--;
			}
		}
	}

	if (result.empty()) cout << "FRULA";
	else
	{
		string answer = "";
		for (int i = 0; i < result.size(); i++) answer += result[i];
		cout << answer;
	}
	return 0;
}

// 풀이법 생각을 못해서 알고리즘 힌트를 확인
// 자료구조 → 스택(stack)을 활용하면 간단하게 풀 수 있음!
// 후입선출 구조를 활용 (뒤에서 비교하면서 하나씩 쌓는 것!)

// 근데 스택을 이용해서 넣었다가 뺐다가 비교하고 다시 넣고를 반복했더니
// → 시간초과가 발생함 (메모리 복사와 함수 호출 오버헤드가 의외로 크다)
// 스택의 후입선출 구조를 활용하되 vector를 이용하는 게 나음(인덱스 접근이 필요)
// 매턴마다 마지막 M개(폭발 문자열의 수)만 비교하는 로직 = 시간 복잡도가 36 * 10^6 정도 (O(NM))

// 시간복잡도 계산이랑 풀이법을 떠올리는 연습 필요 → 다양한 자료구조 활용
// AI 도움없이 혼자 풀이를 떠올리고 디버깅해야 함