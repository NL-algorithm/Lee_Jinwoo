#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> 

using namespace std;

// BFS를 사용하여 두 사람의 촌수를 계산하는 함수
int calculate_kinship(int n, int start_person, int end_person, const vector<vector<int>>& adj) {
    // 촌수를 저장할 배열. -1은 아직 방문하지 않았음을 의미한다.
    // 사람 번호가 1부터 N까지이므로, 크기는 N + 1로 설정한다.
    vector<int> dist(n + 1, -1);
    
    // BFS를 위한 큐
    queue<int> q;

    // 시작점 설정
    q.push(start_person);
    dist[start_person] = 0; // 시작점과의 촌수는 0촌

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // 목표 지점에 도달하면 현재 촌수를 반환
        if (current == end_person) {
            return dist[current];
        }

        // 인접한 모든 노드(친척)를 탐색
        for (int next : adj[current]) {
            // 아직 방문하지 않은 사람이라면 (dist가 -1이라면)
            if (dist[next] == -1) {
                // 촌수 업데이트: 현재 촌수 + 1
                dist[next] = dist[current] + 1;
                // 큐에 추가
                q.push(next);
            }
        }
    }

    // 큐가 비워질 때까지 목표 지점에 도달하지 못했다면 친척 관계가 없음
    return -1;
}

void solve() {
    // 1. 입력 받기
    int n; // 전체 사람 수
    cin >> n;

    int p1, p2; // 촌수를 계산해야 하는 두 사람
    cin >> p1 >> p2;

    int m; // 부모 자식 관계의 개수
    cin >> m;

    // 2. 그래프 (인접 리스트) 생성
    // 사람 번호가 1부터 N까지이므로 N + 1 크기로 생성
    vector<vector<int>> adj(n + 1);

    // 부모-자식 관계는 양방향 간선으로 처리 (촌수 계산을 위해)
    for (int i = 0; i < m; ++i) {
        int parent, child;
        cin >> parent >> child;
        
        // parent와 child 사이에 1촌 관계 설정 (양방향)
        adj[parent].push_back(child);
        adj[child].push_back(parent);
    }

    // 3. 촌수 계산 및 결과 출력
    int result = calculate_kinship(n, p1, p2, adj);

    cout << result << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
