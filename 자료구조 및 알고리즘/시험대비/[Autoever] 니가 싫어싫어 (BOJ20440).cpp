// 문제: https://www.acmicpc.net/problem/20440
// 알고리즘: 좌표압축 및 스위핑
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int N; // 모기의 마릿수 (최대 10^6)
map<int, int> t;
vector<int> reverse_t;

vector<pair<int, int>> mogi;
vector<int> timeline;
vector<int> mogi_cnt;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// (1) 입력
	cin >> N;
	mogi.resize(N);

	for (int i = 0; i < N; i++)
	{
		cin >> mogi[i].first >> mogi[i].second;
		
		t[mogi[i].first] = 0;
		t[mogi[i].second] = 0; // 압축할 좌표를 key 값으로 저장
	}

	// (2) 입력받은 모든 시간을 압축 (좌표압축)
	map<int, int>::iterator iter;
	iter = t.begin();
	
	int idx = 0;
	reverse_t.resize(t.size()); // 압축한 좌표에서 본래 좌표를 구하기 위함
	while (iter != t.end())
	{
		iter->second = idx;
		reverse_t[idx] = iter->first;

		idx++;
		iter++;
	}

	// (3) 각 시간에 따른 모기의 수 저장 (누적합을 이용)
	// → 모기가 들어오는 시간에 모기의 수가 +1 / 모기가 나가는 시간에 모기의 수가 -1
	// → 양 끝점의 변화만 표시해두고 앞에서부터 쭉 더해가는 누적합을 이용
	timeline.resize(t.size());
	for (int i = 0; i < N; i++)
	{
		int Te = mogi[i].first;
		int Tx = mogi[i].second;

		timeline[t[Te]]++;
		timeline[t[Tx]]--;
	} // 각 시간대에 모기의 변화 기록

	mogi_cnt.resize(t.size());
	mogi_cnt[0] = timeline[0];

	int max_mogi = -1, max_Te = 0, max_Tx = 0;
	bool max_interval = false;
	for (int i = 0; i < t.size(); i++)
	{
		if (i == 0) mogi_cnt[i] = timeline[i];
		else mogi_cnt[i] = mogi_cnt[i - 1] + timeline[i]; // 이전 시간대 모기의 수 + 현재 시간대 모기의 변화

		if (mogi_cnt[i] > max_mogi)
		{
			max_mogi = mogi_cnt[i];
			max_Te = i;
			max_interval = true;
		}
		else if (max_interval && mogi_cnt[i] < max_mogi)
		{
			max_Tx = i;
			max_interval = false;
		}
	} // 각 시간대에 모기의 수 기록 + 정답 찾기

	cout << max_mogi << '\n';
	cout << reverse_t[max_Te] << ' ' << reverse_t[max_Tx];
	return 0;
}

// 누적합 알고리즘을 생각해내지 못해서 아이디어는 AI 도움을 받음(순서대로 증가/감소하는 배열에서 특정 구간을 찾을 때는 구간합 이용)

// 시간초과 문제가 발생 
// → 좌표 역변환, 모기의 변화/개수 기록을 2*N 벡터로 선언해서 이용했는데 2*N(=2*10^6)을 여러번 사용해서 그런지 시간초과
// → 변환된 좌표의 개수를 알고있는 상황이므로 t.size()를 이용하는 게 효율적(t.size()로 다 바꾸니까 시간초과 문제 해결)
// → 그리고 map은 시간복잡도가 O(logK) 정도이므로 역변환은 그냥 배열(O(1))을 이용하는 게 빠름 → hash도 key/value 삽입은 O(1)