// ����: https://www.acmicpc.net/problem/1525

// ��� �����ؾ����� ���� �� ������ Ǯ�̸� �����ߴ�
// 2���� �迭�� 1��������, �迭�� �ƴ� string�� ����ؼ� ����
// ������ Ǯ��: https://yabmoons.tistory.com/75

// 1������ index�� 2���� ������ ��ȯ (M�� ���� ����(columns))
// �� row = index / M
// �� col = index % M

// 2���� ���� 1���� index�� ��ȯ (M�� ���� ����(columns))
// �� index = (row * M) + col

// string �湮 ���θ� üũ�ϱ� ���� set�� Ȱ���ߴ�!
// �� ���� string ���� (���� �� ����)�� ���ؼ� �ߺ� üũ�ϸ� �ȵ�
// �� 2���� visit���δ� �ذ� �Ұ���
// �� set�� Ȱ�� 
// (set�� key�� value�� �Ȱ��� map)
// (�ߺ��� ������� ���� - �ߺ��� ���� ������ �߰����� �ʰ� ����)
// (���Ҹ� insert�ϸ� �ڵ����� �������� - �ڵ����� �������� ����)

// �� set�� find�� �ؼ� ���Ұ� �ִ��� Ȯ���� �� ���� ����ϴϱ� ����ص���!

#include <iostream>
#include <string>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

// ��ĭ�� 0�̶�� �Ѵٸ�
// �ʿ��� �̵��� �� �ִ� �� 0���̴�
// �� ���� ��ĭ���� �̵��� �� ���� = 0�� �α��� �� �ڸ��� �ٲ� �� ����

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };
set<string> visit;
string answer_string = "123456780"; // �̰� ó���� 890 ���� �ߴ� �ٺ��ΰ�

int main()
{
	string Map = "";
	for (int i = 0; i < 9; i++)
	{
		int temp;
		cin >> temp;
		Map += to_string(temp);
	}

	queue<pair<string, int>> que;
	que.push({ Map, 0 });
	visit.insert(Map);

	while (!que.empty())
	{
		string now = que.front().first;
		int nowCNT = que.front().second;

		que.pop();

		if (now == answer_string)
		{
			cout << nowCNT;
			return 0; // ������ ã������ ���⼭ ����
		}

		int index = now.find('0'); // ���ڰ� �ִ� index ��ȯ (0�� ��ġ ��ȯ)
		int nowR = index / 3; // ���� ���� 3
		int nowC = index % 3;

		for (int i = 0; i < 4; i++)
		{
			int nextR = nowR + dr[i];
			int nextC = nowC + dc[i];
			string next = now;

			if (nextR < 0 || nextR >= 3 || nextC < 0 || nextC >= 3) continue;

			int nextIndex = nextR * 3 + nextC;
			swap(next[index], next[nextIndex]);

			if (visit.find(next) != visit.end()) continue; // �̹� �湮�� Map�� ��� pass

			visit.insert(next);
			que.push({ next, nowCNT + 1 });
		}
	}
	cout << -1;
	return 0;
}