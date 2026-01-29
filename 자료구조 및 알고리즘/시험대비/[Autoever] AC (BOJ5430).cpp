// 문제: https://www.acmicpc.net/problem/5430
// 알고리즘: 문자열
#include <iostream>
#include <string>
#include <deque>
using namespace std;

string func, arr_st;
int N;
deque<int> arr;

void Solution()
{
	arr.clear();
	cin >> func >> N >> arr_st;

	int index = 0;
	string temp = "";

	while (index < arr_st.size())
	{
		if (arr_st[index] == '[' || arr_st[index] == ',' || arr_st[index] == ']')
		{
			if (temp != "") arr.push_back(stoi(temp));
			temp = "";
			index++;
			continue;
		}
		temp += arr_st[index++];
	}

	bool flip = false;
	// flip == false 일 때는 D 명령에 대해 숫자를 앞에서 제거 (숫자 순서가 →)
	// flip == true일 때는 D 명령에 대해 숫자를 뒤에서 제거 (뒤집힌 상태, 숫자 순서가 ←)
	// 정답을 출력할 때도 같음

	// 명령 수행
	for (int i = 0; i < func.size(); i++)
	{
		char command = func[i];

		if (command == 'R') // 수의 순서를 뒤집는 함수
		{
			if (flip) flip = false;
			else flip = true;
		}
		else if (command == 'D') // 첫 번째 수를 버리는 함수
		{
			if (arr.empty()) // 에러 발생
			{
				cout << "error\n";
				return;
			}

			if (!flip) arr.pop_front(); // 뒤집히지 않은 상태라면
			else arr.pop_back(); // 뒤집힌 상태라면
		}
	}

	// 정답 출력
	if (!flip) // 뒤집혀 있지 않은 경우 (맨 앞이 처음)
	{
		cout << '[';
		for (int i = 0; i < arr.size(); i++)
		{
			if (i == arr.size() - 1) cout << arr[i];
			else cout << arr[i] << ',';
		}
		cout << "]\n"; // 바깥으로 빼줘야 함 (arr이 비어있는 경우도 고려)
	}
	else // 뒤집혀 있는 경우 (맨 뒤가 처음)
	{
		cout << '[';
		for (int i = arr.size()-1; i >= 0; i--)
		{
			if (i == 0) cout << arr[i];
			else cout << arr[i] << ',';
		}
		cout << "]\n"; // 바깥으로 빼줘야 함 (arr이 비어있는 경우도 고려)
	}
}

int main()
{
	int T;
	cin >> T;

	for (int i = 0; i < T; i++)
	{
		Solution();
	}
	return 0;
}