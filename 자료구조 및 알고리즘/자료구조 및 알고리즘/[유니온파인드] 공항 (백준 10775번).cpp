// 문제: https://www.acmicpc.net/problem/10775
// 그리디 + 유니온파인드 (시간 최적화가 필요한 문제 / 집합을 이용하는 걸 떠올려야 함)

// 문제풀이 TIP (풀이가 잘 생각나지 않아서 찾아봄)
// 1. 입력된 값보다 큰 게이트에 배치될 수 없기 때문에 → 범위 안에 남아있는 게이트 중 가장 큰 값에 배치되는 것이 언제나 최적해 (그리디 알고리즘)
// 2. 단순하게 완전탐색으로 풀면 시간 터짐 (시간복잡도 O(N^2), N은 최대 10^5)
// 3. 범위 내에서 최대값부터 채워나감 → g번에 도킹할때 g와 g-1을 하나의 집합으로 묶으면 됨 (g번이 다시 입력되면 범위내 가장 큰 값인 g-1에 도킹할 수 있음)
// 4. 즉 → 연속된 비행기들의 선두자리를 업데이트 (선두자리가 0이 나오면 break, 더이상 도킹할 수 없음)
// 자세한 내용은 아래 코드 내용을 확인하자

#include <iostream>
#include <vector>
using namespace std;

int G;
int P;
vector<int> gate;

int cnt = 0; //도킹한 비행기의 수

int Find(int c)
{
	if (gate[c] != c) gate[c] = Find(gate[c]);
	return gate[c];
} // 내가 평소에 하던 게 경로압축이었다 (순서만 바꾼거임, 동작은 같음, 속도 최적화)

void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);

	if (a == b) return;
	if (a > b) swap(a, b);

	gate[b] = a;
}

int main()
{
	cin >> G >> P;

	gate.resize(G + 1);
	for (int i = 0; i <= G; i++) gate[i] = i;

	while (P--)
	{
		int num;
		cin >> num; //게이트 범위를 입력받음

		num = Find(num); //범위 내에서 도킹할 게이트 번호를 찾음 (대표노드가 범위 내의 남은 게이트 중 가장 큰 번호)
		if (num == 0) break; //도킹할 수가 없는 상황 (1번이 최대인데 채워진 상황)

		Union(num, num - 1); //도킹한 게이트 번호와 그 앞 번호를 묶음 (대표노드를 num-1로 만듬)
		cnt++;
	}

	cout << cnt;
	return 0;
}

// 코드 구현 자체는 쉬운 편인데 풀이를 떠올리는 게 어려웠다 (결국 풀이를 찾아봤음)
// 최적해를 찾는 것도 연습하고
// 경로압축이 필요한 상황 + 유니온파인드를 섞는 것을 잘 연습하자 (N의 범위가 큰데 탐색이 복잡할 때 경로압축용으로 염두해두자)