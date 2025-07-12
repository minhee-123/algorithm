// 문제: https://www.acmicpc.net/problem/1991
#include <iostream>
using namespace std;
//보통 이진트리는 순차표현으로(트리 위치에 index) 구현하지만
//해당 문제에서는 정직하게 순차표현을 사용하기에 부적절 (입력도 그렇게 들어온다는 보장이 없음)
//→ 왼쪽자식 오른쪽자식 위치가 중요하니까 2차원 배열 이용 → 이걸 많이 활용할지도 모르겠다 (왼쪽 오른쪽 이동이 용이함)

int N;
int tree[26][2]; //Left(0), Right(1)

void FirstOrder(int index) //전위순회
{
	// 현재노드 → 왼쪽노드 → 오른쪽노드
	if (index == -1) return;
	cout << (char)(index + 'A');
	FirstOrder(tree[index][0]); //왼쪽 이동
	FirstOrder(tree[index][1]); //오른쪽 이동
}

void SecondOrder(int index) //중위순회
{
	// 왼쪽노드 → 현재노드 → 오른쪽노드
	if (index == -1) return;
	SecondOrder(tree[index][0]); //왼쪽 이동
	cout << (char)(index + 'A');
	SecondOrder(tree[index][1]); //오른쪽 이동
}

void ThirdOrder(int index) //후위순회
{
	// 왼쪽노드 → 오른쪽노드 → 현재노드
	if (index == -1) return;
	ThirdOrder(tree[index][0]); //왼쪽 이동
	ThirdOrder(tree[index][1]); //오른쪽 이동
	cout << (char)(index + 'A');
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		char Me, L, R;
		cin >> Me >> L >> R;

		int node = Me - 'A'; //0은 A

		if (L == '.') tree[node][0] = -1;
		else tree[node][0] = L - 'A';
		
		if (R == '.') tree[node][1] = -1;
		else tree[node][1] = R - 'A';
	}

	FirstOrder(0);
	cout << '\n';

	SecondOrder(0);
	cout << '\n';

	ThirdOrder(0);
	cout << '\n';

	return 0;
}