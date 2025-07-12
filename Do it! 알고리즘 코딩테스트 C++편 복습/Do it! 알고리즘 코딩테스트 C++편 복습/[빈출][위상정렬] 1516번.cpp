// 게임 개발하기
// 문제: https://www.acmicpc.net/problem/1516

// 위상정렬 → 노드 순서를 찾음 (사이클이 없어야 함)
// 진입 차수 배열 만들기 (진입 차수 배열의 개념이 핵심)
// 진입 차수가 0인 것을 선택 → 연결된 애들의 진입차수를 -1 (0인 애들을 큐에 넣고 하나씩 빼면 되겠지, 사이클이 없어서 돌아갈 일이 없기 때문에 visit 처리를 안 해줘도 문제없음)

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N;
vector<vector<int>> building; //빌딩 선후관계 저장 (먼저 지어야되는 것 → 후에 짓는 것)
vector<int> selfT; //본인 건물 짓는데 걸리는 시간
vector<int> answerT; //정답 시간
vector<int> arr; //진입차수 배열

int main()
{
	cin >> N;

	building.resize(N + 1);
	selfT.resize(N + 1);
	answerT.resize(N + 1, 0); //0으로 초기화
	arr.resize(N + 1, 0); //0으로 초기화

	for (int i = 1; i <= N; i++)
	{
		cin >> selfT[i];

		int temp;
		while (1)
		{
			cin >> temp;
			if (temp == -1) break;

			building[temp].push_back(i);
			arr[i]++;
		}
	} //입력 및 진입차수배열

	queue<int> que;
	for (int i = 1; i <= N; i++)
	{
		if (arr[i] == 0) que.push(i);
	}

	while (!que.empty())
	{
		int now = que.front();
		que.pop();

		for (int i = 0; i < building[now].size(); i++)
		{
			int next = building[now][i];
			answerT[next] = max(answerT[next], answerT[now] + selfT[now]); //이 부분을 언제쯤 혼자 떠올릴 수 있을까나... 정진하자!

			arr[next]--; //진입차수배열 감소 (방문했으니까)
			if (arr[next] <= 0) que.push(next);
		}
	}

	for (int i = 1; i <= N; i++)
	{
		cout << answerT[i] + selfT[i] << '\n';
	}
	return 0;
}