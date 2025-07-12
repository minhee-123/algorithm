// 일곱 난쟁이 (https://www.acmicpc.net/problem/2309)
// 브루트 포스 (완전 탐색) 유형의 문제

// 문제풀이 절차
// 1. 입력 값을 배열에 저장, 그리고 전체 합을 저장
// 2. 정렬 (오름차순으로 출력해야 함)
// 3. 이중포문을 이용해 2개의 값을 빼면서 합이 100이 되는 것을 찾음 (이중포문으로 전체를 한번 훑어서 완전탐색이라고 하는 듯??)

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int dwarf[9];
	int sum = 0;
	for (int i = 0; i < 9; i++)
	{
		cin >> dwarf[i];
		sum += dwarf[i];
	}
	sort(dwarf, dwarf + 9); 
	//배열의 위치는 이런 식으로 입력
	//(배열이름, 배열이름 + 배열크기)

	for (int i = 0; i < 8; i++)
	{
		for (int j = i + 1; j < 9; j++)
		{
			if ((sum - dwarf[i] - dwarf[j]) == 100)
			{
				for (int z = 0; z < 9; z++)
				{
					if ((z != i) && (z != j)) cout << dwarf[z] << '\n';
				}
				return 0; //이걸 안 넣으면 오답으로 처리된다!
				// return 0는 C++에서 프로그램을 종료한다는 의미
				// 예제 입력에서는 가능한 답안이 하나였지만, 가능한 답안이 두가지 이상인 경우, 한번 출력하고 프로그램을 종료시키지 않으면 답안 두개가 출력됨
				// 한가지 답안만 출력해야 하므로 출력했을 경우(결과도출) 프로그램을 아예 종료시키는 것
			}
		}
	}
	return 0;
}