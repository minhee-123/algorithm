// 문제: https://www.acmicpc.net/problem/12100
#include <iostream>
#include <vector>
using namespace std;
// 최대 5번 이동해서 만들 수 있는 가장 큰 블록의 값
// 이걸 백트래킹이라고 해야 하나 구현에 가까운듯

int N;
vector<vector<int>> Map;

int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 0 };

// 시간도 없고 정신도 없어서 Move 구현 부분은 AI 답변을 가져옴
// Move 구현은 빡구현 (전반적인 로직도 그다지 백트래킹은 아니라서...)
vector<int> get_merged_line(vector<int>& line)
{
    vector<int> res;
    // 1. 0이 아닌 숫자만 추출
    for (int x : line) if (x != 0) res.push_back(x);

    vector<int> next_line;
    // 2. 인접한 같은 숫자 합치기
    for (int i = 0; i < res.size(); i++) {
        if (i + 1 < res.size() && res[i] == res[i + 1]) {
            next_line.push_back(res[i] * 2);
            i++; // 합쳐졌으므로 다음 숫자는 건너뜀
        }
        else {
            next_line.push_back(res[i]);
        }
    }
    // 3. 나머지는 0으로 채우기
    while (next_line.size() < N) next_line.push_back(0);
    return next_line;
}
vector<vector<int>> Move(int dir, vector<vector<int>> board)
{
    vector<vector<int>> next_board(N, vector<int>(N, 0));

    if (dir == 0) { // 상 (열 단위로 위로 밀기)
        for (int j = 0; j < N; j++) {
            vector<int> line;
            for (int i = 0; i < N; i++) line.push_back(board[i][j]);
            vector<int> merged = get_merged_line(line);
            for (int i = 0; i < N; i++) next_board[i][j] = merged[i];
        }
    }
    else if (dir == 1) { // 하 (열 단위로 아래로 밀기)
        for (int j = 0; j < N; j++) {
            vector<int> line;
            for (int i = N - 1; i >= 0; i--) line.push_back(board[i][j]);
            vector<int> merged = get_merged_line(line);
            for (int i = 0; i < N; i++) next_board[N - 1 - i][j] = merged[i];
        }
    }
    else if (dir == 2) { // 좌 (행 단위로 왼쪽으로 밀기)
        for (int i = 0; i < N; i++) {
            vector<int> line;
            for (int j = 0; j < N; j++) line.push_back(board[i][j]);
            vector<int> merged = get_merged_line(line);
            for (int j = 0; j < N; j++) next_board[i][j] = merged[j];
        }
    }
    else if (dir == 3) { // 우 (행 단위로 오른쪽으로 밀기)
        for (int i = 0; i < N; i++) {
            vector<int> line;
            for (int j = N - 1; j >= 0; j--) line.push_back(board[i][j]);
            vector<int> merged = get_merged_line(line);
            for (int j = 0; j < N; j++) next_board[i][N - 1 - j] = merged[j];
        }
    }
    return next_board;
}

int Find_Max(vector<vector<int>> board)
{
	int answer = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) answer = max(answer, board[i][j]);
	}
	return answer;
}

int max_value = 0;
void DFS(int dir, int depth, vector<vector<int>> board)
{
	board = Move(dir, board);
	depth++;

	if (depth == 5)
	{
		int value = Find_Max(board);
		max_value = max(max_value, value);
		return;
	}

	for (int i = 0; i < 4; i++) DFS(i, depth, board);
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		vector<int> temp;
		temp.resize(N);
		for (int j = 0; j < N; j++) cin >> temp[j];
		Map.push_back(temp);
	}

	for (int i = 0; i < 4; i++) DFS(i, 0, Map);
	cout << max_value;
	return 0;
}