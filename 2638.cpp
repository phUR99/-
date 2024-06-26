#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
// 현재 정보
int board[105][105];
// 공기의 정보
int tmp_board[105][105];
// 방문 판정
bool visited[105][105];
// 외부 판정
bool out[105][105];
int n, m;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// 1이 하나라도 있는지 체크
bool check(int n, int m){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if(board[i][j]) return false;
        }
        
    }
    return true;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> board[i][j];
        }
        
    }
    int ans = 0;    
    while (true)
    {
        if(check(n, m)) break;
        memset(visited, false, sizeof(visited));
        memset(tmp_board, 0, sizeof(tmp_board));
        ans++;

        queue<pair<int, int>> q;
        // ㅁ로 경계면에 붙어있는 원소에 대해서 BFS 실행
        for (int i = 0; i < n; i++)
        {          
            if(i != 0 && i != n-1)  continue;
            for (int j = 0; j < m; j++)
            {                
                if(visited[i][j] || board[i][j]) continue;
                q.push({i, j});
                visited[i][j] = true;
                out[i][j] = true;
                while (!q.empty())
                {
                    auto cur = q.front(); q.pop();
                    for (int dir = 0; dir < 4; dir++)
                    {
                        int nx = cur.first + dx[dir];
                        int ny = cur.second + dy[dir];
                        if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                        if(visited[nx][ny] || board[nx][ny]) continue;
                        out[nx][ny] = true;
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }                                        
                }
                
            }
        }
        for (int i = 0; i < n; i++)
        {          
            for (int j = 0; j < m; j++)
            {             
                if(j != 0 && j != m-1)  continue;
                if(visited[i][j] || board[i][j]) continue;
                q.push({i, j});
                visited[i][j] = true;
                out[i][j] = true;
                while (!q.empty())
                {
                    auto cur = q.front(); q.pop();
                    for (int dir = 0; dir < 4; dir++)
                    {
                        int nx = cur.first + dx[dir];
                        int ny = cur.second + dy[dir];
                        if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                        if(visited[nx][ny] || board[nx][ny]) continue;
                        out[nx][ny] = true;
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }                                        
                }
                
            }
        }

        memset(visited, false, sizeof(visited));
        // 치즈에 대해서 상하좌우 탐색
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if(!board[i][j]) continue;
                int cnt = 0;
                for (int dir = 0; dir < 4; dir++)
                {
                    int nx = i + dx[dir];
                    int ny = j + dy[dir];                    
                    if(nx <0 || nx >=n || ny <0 || ny >= m) continue;
                    if(!out[nx][ny]) continue;
                    cnt++;
                }                
                tmp_board[i][j] = cnt;
            }
            
        }
        // 2 이상인 위치에 대해서는 board -> 0, out -> true로 변경
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                const int &tmp = tmp_board[i][j];
                if(tmp < 2) continue;
                board[i][j] = 0;
                out[i][j] = true;                
            }
            
        }
    }

            
    cout << ans;
        


    return 0;
}