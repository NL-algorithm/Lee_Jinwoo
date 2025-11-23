#include <iostream>
#include <cstring>
using namespace std;

int n , m, cabbage;
bool cabb[51][51];
bool check[51][51];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

bool dfs(int y,int x)
{
  if(check[y][x]) return false;
  check[y][x]=true;

  for(int i=0; i<4; i++)
    {
      int next_x = x + dx[i]; //3. 동,서,남,북으로 한칸씩 이동한다.
      int next_y = y + dy[i];

      if(next_x>=0 && next_y>=0&&next_x <m &&next_y<n &&cabb[next_y][next_x]) // 4. 인근 지역에 배추 있을 경우, 해당 지역 방문 처리
        dfs(next_y,next_x);
    }
  return true;
}
int main() {
  int TC;
  cin>>TC;
  for(int i=0; i<TC; i++)
    {
      cin>>m>>n>>cabbage;
      memset(cabb,0,sizeof(cabb));
      memset(check,0,sizeof(check));

      for(int j=0; j<cabbage; j++)
        {
          int x=0,y=0;
          cin>>x>>y;
          cabb[y][x]=true; //1. 행- y축 열-x축 
        }

      int bug_count=0;

      for(int j=0; j<n; j++)
        {
          for(int k=0; k<m; k++)
            {
              if(cabb[j][k]&&!check[j][k])
              {//2.탐색 안한 구역일 경우, dfs 수행&count추가.
                if(dfs(j,k)) bug_count++;
              }
            }
        }
      cout<<bug_count<<'\n';
    }
}
