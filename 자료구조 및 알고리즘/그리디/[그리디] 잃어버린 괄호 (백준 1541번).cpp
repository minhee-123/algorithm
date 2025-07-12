// 문제: https://www.acmicpc.net/problem/1541

// 그리디: 현재 상태에서 보는 선택지 중 최선의 선택지가 전체 선택지 중 최선의 선택지라고 가정하는 알고리즘
// 문제풀이 → 최솟값을 만들기 위해 가능한 큰 수를 빼야 함 → '-'가 나오는 이후의 숫자를 전부 빼버리면 됨 → 이 풀이가 그리디의 관점 (왜지)

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	string st;
	cin >> st;

	vector<int> comp;
	int m_index = 0;
	
	int index = 0;
	int label = 0;
	bool flag = true;
	while (1)
	{
		string temp = "";
		while (st[index] != '+' && st[index] != '-')
		{
			temp += st[index];
			index++;

			if (index >= st.size()) break;
		}
		comp.push_back(stoi(temp));
		label++;

		if (index >= st.size()) break;
		
		if (flag && st[index] == '-')
		{
			m_index = label;
			flag = false;
		}
		index++;
	}

	int min_num = 0;
	if (m_index > 0) //'-'가 없음
	{
		for (int i = 0; i < m_index; i++) min_num += comp[i];
		for (int i = m_index; i < comp.size(); i++) min_num -= comp[i];
	}
	else
	{
		for (int i = 0; i < comp.size(); i++) min_num += comp[i];
	}

	cout << min_num << '\n';
	return 0;
}