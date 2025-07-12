// 문제: https://softeer.ai/practice/7727

// ★ 첫번째 풀이 방법 → 틀렸음 (틀린 풀이는 소프티어 제출이력 중 가장 최근의 틀렸음 풀이를 보면 됨)
// 1. 한 친구가 최대로 열매를 수확하고 해당 경로를 저장해둠
// 2. 저장해둔 경로를 visit 업데이트, 다음 친구는 visit한 곳을 제외하고 최대로 열매를 수확함
// 3. 시작 순서를 순열로 구하고, 모든 순열(모든 순서)에 대해 1~2를 실행
// 4. 모든 경우에 대해서 수확한 총 열매가 최대가 될 때 정답

// 첫번째 풀이 방법에서 헛점은 친구들이 "동시에" 한나무에 방문하지는 못하지만 한 나무에 여러친구가 방문할 수는 있다는 점
// 이미 한 친구가 들린 나무를 다른 시점(time)에서 다른 친구가 방문할 수는 있음 (열매를 수확할 수는 없음)

// ★ 두번째 풀이 방법
// 참고: https://tigerfrom2.tistory.com/407
// 근데 참고 풀이의 문제점은 순서가 하나다 (뒤에부터 시작하는 걸로 하고 있는데 테스트 케이스에서 운 좋게 통과되는 것임)

// 첫번째 풀이와 두번째 풀이 모두 해결하지 못하는 문제
// 한 사람이 움직일 때 자기가 방문했던 나무를 또 방문해서 움직였을 때 최대가 나오는 경우를 반영하지 못함
// 3초 전에 움직임이 종료되는데, 이때 최대가 나오는 경우를 반영하지 못함
// 그러나 테스트케이스에서 이 부분을 고려하지 않고 있기 때문에 통과에는 문제가 없음 → 문제와 테스트케이스가 그리 좋은 편은 아닌듯

// 이 정도면 문제에서 사용되는 알고리즘, 풀이 방법을 충분히 공부했고
// ★ 문제와 테스트케이스도 자잘한 문제가 있으니까 완벽한 풀이는 포기함 (시간낭비 같음)





///////////////////////////// ★ 첫번째 풀이
#include <iostream>
#include <vector>
using namespace std;

int N, M;
bool visited[21][21][4] = { false, };
int tree[21][21];

vector<pair<int, int>> startset;

int answer = 0;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
void dfs(int x, int y, int cnt, int value, int dim) {
	if (cnt == 3) {
		if (dim == 1) {
			answer = max(answer, value);
			return;
		}
		else {
			int nx = startset[dim - 2].first - 1;
			int ny = startset[dim - 2].second - 1;
			dfs(nx, ny, 0, value + tree[nx][ny], dim - 1);
			return;
		}
	}

	for (int i = 0; i < 4; i++) {
		int nextx = x + dx[i];
		int nexty = y + dy[i];

		if (nextx < N && nextx > -1 && nexty < N && nexty > -1 && visited[nextx][nexty][dim] == false) {
			visited[nextx][nexty][dim] = true;
			int nextValue = value;
			if (dim == 3) nextValue += tree[nextx][nexty];
			else if (dim == 2) {
				if (visited[nextx][nexty][3] == false) nextValue += tree[nextx][nexty];
			}
			else if (dim == 1) {
				if (visited[nextx][nexty][2] == false && visited[nextx][nexty][3] == false) nextValue += tree[nextx][nexty];
			}

			dfs(nextx, nexty, cnt + 1, nextValue, dim);
			visited[nextx][nexty][dim] = false;
		}
	}
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> tree[i][j];
		}
	}

	for (int j = 0; j < M; j++) {
		int a, b;
		cin >> a >> b;
		startset.push_back({ a,b });
	}

	for (int i = 0; i < startset.size(); i++) {
		int x = startset[i].first - 1;
		int y = startset[i].second - 1;
		visited[x][y][i + 1] = true;
	}

	int x = startset[startset.size() - 1].first - 1;
	int y = startset[startset.size() - 1].second - 1;
	dfs(x, y, 0, tree[x][y], M);

	cout << answer << endl;
}





///////////////////////////// ★ 첫번째 풀이
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int N, M;
vector<pair<int, int>> people;
int MAP[21][21] = { 0 };
bool visit[21][21]; //false

int dr[4] = { 1, 0, -1, 0 }; //상우하좌
int dc[4] = { 0, 1, 0, -1 };

vector<pair<int, int>> answer_path;
vector<pair<int, int>> temp_path;

int max_apple = 0;
void move(int row, int col, int depth, int apple)
{
    if (depth >= 3)
    {
        if (apple > max_apple)
        {
            max_apple = apple;
            answer_path = temp_path;
        }
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        int next_row = row + dr[i];
        int next_col = col + dc[i];

        if (visit[next_row][next_col]) continue;
        if (next_row <= 0 || next_row > N || next_col <= 0 || next_col > N) continue;

        temp_path.push_back({ next_row, next_col });
        visit[next_row][next_col] = true;
        move(next_row, next_col, depth + 1, apple + MAP[next_row][next_col]);

        temp_path.pop_back();
        visit[next_row][next_col] = false;
    }

    if (apple > max_apple)
    {
        max_apple = apple;
        answer_path = temp_path;
    }
}

void record_path()
{
    for (int i = 0; i < answer_path.size(); i++) visit[answer_path[i].first][answer_path[i].second] = true;
}

int main()
{
    cin >> N >> M;

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++) cin >> MAP[i][j];
    }

    people = vector<pair<int, int>>(M, { 0, 0 });
    vector<int> people_num;
    for (int i = 0; i < M; i++)
    {
        cin >> people[i].first >> people[i].second;
        people_num.push_back(i);
    }

    vector<vector<int>> permu; //순열로 순서 생성 (최대값이 나오는 순서를 모르기 때문에 모든 순서를 수행해봄)
    int index = 0;
    do
    {
        permu.push_back({});
        for (int i = 0; i < people_num.size(); i++)
        {
            permu[index].push_back(people_num[i]);
        }
        index++;

    } while (next_permutation(people_num.begin(), people_num.end()));

    int answer = 0;
    for (int i = 0; i < permu.size(); i++)
    {
        memset(visit, false, sizeof(visit));
        for (int i = 0; i < people.size(); i++) visit[people[i].first][people[i].second] = true;

        int collect = 0;
        for (int j = 0; j < permu[i].size(); j++)
        {
            int index = permu[i][j];

            max_apple = 0;
            temp_path.clear();
            answer_path.clear();
            temp_path.push_back({ people[index].first, people[index].second });

            move(people[index].first, people[index].second, 0, MAP[people[index].first][people[index].second]);

            collect += max_apple;
            record_path();
        }

        answer = max(answer, collect);
    }

    cout << answer;
    return 0;
}