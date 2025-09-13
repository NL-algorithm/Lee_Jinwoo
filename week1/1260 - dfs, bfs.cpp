#include <iostream>
#include <cstring>
#include <queue>

using namespace std;
int n,m,v;

int graph[1002][1002]; //node 간 연결 여부 표시 graph[0][1]은 0,1노드가 연결되어있다는 뜻
bool visited[1002];

void dfs(int node)
{
      visited[node] = 1;
      cout << node << ' '; 
      for(int next = 1 ; next <=n; ++next){
		if(!visited[next] && graph[node][next]) //방문이 되어있지 않고, 간선이 있다면
        	dfs(next);
      }
}
void bfs(int node)
{
    queue<int> q; 
    q.push(node);    //시작 노드

    while (!q.empty())
    {
        int next = q.front(); //큐 맨 앞에 값을 방문
        visited[next] = 1;   
        cout << next << " ";  
        q.pop();              //pop 큐에서 뺌

        //방문했던 노드와 가까운 노드 큐에 넣어줌
        for (int i = 1; i <= n; i++)
        {
            if (graph[next][i] == 1 && visited[i] == 0)
            {
                q.push(i);        
                visited[i] = 1; 
            }
        }
    }
    
}

int main(void)
{
    
    int x,y;
    cin >> n >> m>> v;

    memset(graph,0,sizeof(graph));
    
    for(int i=0; i<m; i++)
    {
        cin >> x >> y;
        graph[x][y]=graph[y][x]=1;
    }
    dfs(v);
   
    cout << '\n';

    memset(visited,0, sizeof(visited));

    bfs(v);
    
    return 0;
}