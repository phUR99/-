#include <bits/stdc++.h>
#define fastio                       \
    ios_base::sync_with_stdio(NULL); \
    cin.tie(NULL);                   \
    cout.tie(NULL)
using namespace std;
char board[105][105], tmp_board[105][105];
bool bottom[105][105];
int r, c, n;
void check();
void move();

/*
1. 모양을 어떻게 유지할까?
-> 조건에 맞는 좌표들을 벡터로 전부 집어넣어줌
2. 범위 주의해서 확인하기
-> 현재 범위가 반열림 구간이 맞는 지에 대해서 확인하기!!!
3. 조건 확인하기
-> 한칸만 없앨 수 있으므로, 독립된 클러스터는 많이 생겨도 항상 하나임

*/
void play_left(int h)
{
    int col = -1;

    for (int i = 0; i < c; i++)
    {
        if (board[h][i] == 'x')
        {
            col = i;
            break;
        }
    }
    if (col == -1)
        return;
    board[h][col] = '.';
    check();
    move();
}
void play_right(int h)
{
    int col = -1;
    // 범위 주의
    for (int i = c - 1; i >= 0; i--)
    {
        if (board[h][i] == 'x')
        {
            col = i;
            break;
        }
    }
    if (col == -1)
        return;
    board[h][col] = '.';
    check();
    move();
}
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
void move()
{
    vector<vector<int>> arr;
    arr.resize(c);

    for (int i = 1; i <= r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (board[i][j] == 'x' && !bottom[i][j])
            {
                arr[j].push_back(i);
            }
        }
    }
    int down = 200;
    for (int i = 0; i < c; i++)
    {
        for (auto h : arr[i])
        {
            int cnt = 0;
            for (int j = h + 1; j <= r; j++)
            {
                if (board[j][i] == 'x' && bottom[j][i])
                    break;
                cnt++;
            }
            down = min(cnt, down);
        }
    }
    for (int i = 1; i <= r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            tmp_board[i][j] = '.';
            if (bottom[i][j])
                tmp_board[i][j] = 'x';
        }
    }
    for (int i = 0; i < c; i++)
    {
        for (auto h : arr[i])
        {
            tmp_board[h + down][i] = 'x';
        }
    }
    for (int i = 1; i <= r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            board[i][j] = tmp_board[i][j];
        }
    }
}
void check()
{
    memset(bottom, 0, sizeof(bottom));
    for (int i = 0; i < c; i++)
    {
        if (bottom[r][i] || board[r][i] != 'x')
            continue;
        queue<pair<int, int>> q;
        q.push({r, i});
        bottom[r][i] = true;
        while (!q.empty())
        {
            auto cur = q.front();
            q.pop();
            for (int dir = 0; dir < 4; dir++)
            {
                int nx = cur.first + dx[dir];
                int ny = cur.second + dy[dir];
                if (nx < 1 || nx > r || ny < 0 || ny >= c)
                    continue;
                if (bottom[nx][ny] || board[nx][ny] != 'x')
                    continue;
                bottom[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
}

int main()
{
    fastio;
    cin >> r >> c;
    for (int i = 1; i <= r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> board[i][j];
        }
    }
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int height;
        cin >> height;
        height = r + 1 - height;
        if (i % 2 == 0)
        {
            play_left(height);
        }
        else
        {
            play_right(height);
        }
    }
    for (int i = 1; i <= r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << board[i][j];
            // cout << bottom[i][j];
        }
        cout << '\n';
    }

    return 0;
}