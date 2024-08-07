#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)


int N;
bool visited[10050];
int cache[10050][2];
int weight[10050];
vector<int> adj[10050];

void caching(int cur){

    visited[cur] = true;
    cache[cur][0] = 0;
    cache[cur][1] = weight[cur];
    for (auto nxt : adj[cur])
    {
        if(visited[nxt]) continue;
        caching(nxt);
        cache[cur][0] += max(cache[nxt][0], cache[nxt][1]);
        cache[cur][1] += cache[nxt][0];
    }    
}
vector<int> answer;
//이전 정점을 어떻게 선택했는가에 대한 아이디어
//캐시의 값이 더 큰걸 선택하면 된다는 것 까지는 알아냈으나
//이전 정점 선택한 것을 조건에 반영하는 것을 생각하지 못했음.
//이전 정점에 대한 정보를 들고가자

void tracking(int cur, bool INCLUDE){
    visited[cur] = true;
    if(cache[cur][0] < cache[cur][1] && !INCLUDE) {
        answer.push_back(cur);
        INCLUDE = true;
    }
    else INCLUDE = false;

    for (auto nxt : adj[cur])
    {
        if(visited[nxt]) continue;
        tracking(nxt, INCLUDE);        
    }      

}

int main(){
    fastio;
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> weight[i];
    }
    int u, v;
    for (int i = 0; i < N-1; i++)
    {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    caching(1);
    int V = max(cache[1][0], cache[1][1]);
    memset(visited, false, sizeof(visited));
    tracking(1, false);
    cout << V << '\n';
    sort(answer.begin(), answer.end());
    for (int i = 0; i < answer.size(); i++)
    {
        cout << answer[i] << ' ';
    }
    
    

    return 0;
}