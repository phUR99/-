#include <bits/stdc++.h>
#define fastio                       \
    ios_base::sync_with_stdio(NULL); \
    cin.tie(NULL);                   \
    cout.tie(NULL)
using namespace std;
int board[20][20], tmp_board[20][20];
int dist[20][20];
bool check[20][20];
/*
1. 궁수가 N-1에 위치한게 아니라 N에 위치해있다는 점에 주의, 거리가 안맞아서 고생함
2. 정렬 조건이 2개 이상 있을 때, 맞는 조건 하나만 찾는게 아니라,
가능한 원소를 전부 넣어놓은 다음에 정렬을 이용해서 맨 앞의 원소를 뽑는 방법 -> 작은 조건이면 훨씬 좋은거 같음
궁수의 수가 작아서 재귀가 아니라 반복문으로 해결 -> 더 많아지면 재귀로 궁수의 위치를 뽑기
*/

int n, m, d;
int answer = 0;

int dx[] = {0, 1, -1, 0};
int dy[] = {-1, 0, 0, 1};

void init()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            tmp_board[i][j] = board[i][j];
        }
    }
}
void copy()
{
    for (int i = n; i > 0; i--)
    {
        for (int j = 0; j < m; j++)
        {
            tmp_board[i][j] = tmp_board[i - 1][j];
        }
    }
    for (int j = 0; j < m; j++)
    {
        tmp_board[0][j] = 0;
    }
}
bool cmp(vector<int> &a, vector<int> &b)
{
    if (a[0] == b[0])
        return a[2] < b[2];
    return a[0] < b[0];
}

void find(int p)
{

    queue<pair<int, int>> q;
    memset(dist, -1, sizeof(dist));

    q.push({n, p});
    dist[n][p] = 0;
    vector<vector<int>> arr;

    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();
        for (int dir = 0; dir < 4; dir++)
        {
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                continue;
            if (dist[nx][ny] != -1)
                continue;
            if (dist[cur.first][cur.second] + 1 > d)
                continue;
            q.push({nx, ny});
            dist[nx][ny] = dist[cur.first][cur.second] + 1;
            if (tmp_board[nx][ny])
            {
                arr.push_back({dist[nx][ny], nx, ny});
            }
        }
    }
    if (arr.empty())
        return;
    sort(arr.begin(), arr.end(), cmp);
    int x = arr[0][1];
    int y = arr[0][2];
    check[x][y] = true;
}

void play(int p1, int p2, int p3)
{
    init();
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        memset(check, 0, sizeof(check));
        find(p1);
        find(p2);
        find(p3);
        for (int k = 0; k < n; k++)
        {
            for (int j = 0; j < m; j++)
            {
                cnt += check[k][j];
                if (check[k][j])
                    tmp_board[k][j] = 0;
            }
        }
        copy();
    }
    answer = max(answer, cnt);
}

int main()
{
    fastio;
    cin >> n >> m >> d;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> board[i][j];
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = i + 1; j < m; j++)
        {
            for (int k = j + 1; k < m; k++)
            {
                play(i, j, k);
            }
        }
    }
    cout << answer;
    return 0;
}