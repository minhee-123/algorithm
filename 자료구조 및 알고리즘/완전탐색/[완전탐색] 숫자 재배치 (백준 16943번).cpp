//숫자 재배치 (https://www.acmicpc.net/problem/16943)
//참고: https://ansohxxn.github.io/algorithm/permutation/ 
//algorithm 라이브러리의 next_permutation 사용하면 모든 순열을 구할 수 있음
//★이때 사용하는 컨테이너는 오름차순으로 정렬되어 있어야 함

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	string str_A, str_B;
	cin >> str_A >> str_B;

	vector<char> A_element;
	for (int i = 0; i < str_A.length(); i++)
	{
		A_element.push_back(str_A[i]);
	}
	sort(A_element.begin(), A_element.end());

	//nPn 순열 만들기 (nPr의 경우 반복문을 r까지 돌리고 reverse(begin()+r, end()); 해줘야 함)
	vector<string> C;
	do
	{
		if (A_element[0] == '0') continue;
		else
		{
			string temp = "";
			for (int i = 0; i < A_element.size(); i++)
			{
				temp += A_element[i];
			}
			C.push_back(temp);
		}

	} while (next_permutation(A_element.begin(), A_element.end()));

	int answer = 0;
	for (int i = C.size() - 1; i >= 0; i--)
	{
		if (stoi(C[i]) < stoi(str_B))
		{
			answer = stoi(C[i]);
			break;
		}
	}

	if (answer == 0) cout << -1;
	else
	{
		cout << answer;
	}
	return 0;
}