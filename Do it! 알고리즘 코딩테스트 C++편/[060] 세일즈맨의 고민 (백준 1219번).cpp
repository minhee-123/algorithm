// 문제: https://www.acmicpc.net/problem/1219
#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
using namespace std;
// 벨만-포드 내부 로직을 바꿔서 최대값 업데이트, 양수사이클 이용
// 이때 양수사이클이 발생한다고 무조건 무한증식은 아님 (도착 노드로 가는 길에 양수사이클이 있어야 무한증식, 관련없는 노드에서 발생하는 양수사이클은 상관없음)
 
struct edge
{
	int start;
	int end;
	int moveMoney; //교통비
};

int N, S, E, M;
vector<long> mdistance; //오버플로우 주의
vector<int> cityMoney; //도시에서 얻는 돈
vector<edge> edges;

int main()
{
	cin >> N >> S >> E >> M;
	edges.resize(M);
	cityMoney.resize(N);
	mdistance.resize(N);
	fill(mdistance.begin(), mdistance.end(), LONG_MIN);
	for (int i = 0; i < M; i++) cin >> edges[i].start >> edges[i].end >> edges[i].moveMoney;
	for (int i = 0; i < N; i++) cin >> cityMoney[i];

	mdistance[S] = cityMoney[S];

	for (int i = 0; i <= N + 50; i++) //N의 최대값이 50이므로 N+50회 반복 (충분히 반복)
	{
		for (int j = 0; j < M; j++)
		{
			int start = edges[j].start;
			int end = edges[j].end;
			int money = cityMoney[end] - edges[j].moveMoney; //이동했을 때 얻는 돈

			if (mdistance[start] == LONG_MIN) continue; //시작노드를 아직 방문하지 않은 경우
			else if (mdistance[start] == LONG_MAX) mdistance[end] = LONG_MAX; //양수사이클 루트에 있다면 LONG_MAX (양수사이클 루트에 있는 경우)
			else if (mdistance[end] < mdistance[start] + money) //얻는 값이 최대가 되도록 함 (최단거리 알고리즘에서 값만 최대로 바꿈)
			{
				mdistance[end] = mdistance[start] + money; //반복 N-1회까지는 벨만-포드
				if (i >= N - 1) mdistance[end] = LONG_MAX; //반복 N회부터는 양수사이클 판별 시작
			}
		}
	}

	if (mdistance[E] == LONG_MIN) cout << "gg";
	else if (mdistance[E] == LONG_MAX) cout << "Gee";
	else cout << mdistance[E];
	return 0;
}