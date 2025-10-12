#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <stack>

using namespace std;

// 무한대 값 설정 (int 대신 long long을 사용해야 오버플로우 방지)
const long long INF = numeric_limits<long long>::max();

// 간선 정보를 저장하는 pair: {비용, 도착 도시}
using Edge = pair<int, int>; 

// 다익스트라 알고리즘
void dijkstra(int V, const vector<vector<Edge>>& adj, int start, int end) {
    // dist: 시작점에서 각 도시까지의 최소 비용
    vector<long long> dist(V + 1, INF);
    // parent: 최단 경로 상에서 현재 도시에 도달하기 직전의 도시 (경로 추적용)
    vector<int> parent(V + 1, 0); 
    
    // 우선순위 큐 (Min Heap): {비용, 도시 번호}를 저장하여 최소 비용 경로를 탐색
    // {비용, 도시 번호} 순으로 저장하며, 비용이 작은 것이 우선순위가 높음
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    // 시작 도시 초기화
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        long long current_cost = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // 현재 꺼낸 비용이 이미 계산된 최소 비용보다 크면 무시 (불필요한 탐색 제거)
        if (current_cost > dist[u]) {
            continue;
        }

        // 현재 도시 u와 연결된 모든 간선 검사
        for (const auto& edge : adj[u]) {
            int v = edge.second;         // 도착 도시
            int weight = edge.first;     // 버스 비용 (간선 가중치)

            // 갱신 조건: 현재 도시를 거쳐 v로 가는 비용이 기존 비용보다 작다면
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight; // 비용 갱신
                parent[v] = u;              // 경로 추적: v의 직전 도시는 u
                pq.push({dist[v], v});      // 큐에 추가
            }
        }
    }

    // =======================================================
    // 1. 최소 비용 출력
    // =======================================================
    cout << dist[end] << endl;

    // =======================================================
    // 2 & 3. 경로 추적 및 출력
    // =======================================================
    stack<int> path_stack;
    int current_node = end;

    // 도착점에서 시작점까지 parent 배열을 역추적하며 스택에 저장
    while (current_node != 0) {
        path_stack.push(current_node);
        // 시작점(start)의 parent는 0이므로, 0에 도달하면 멈춘다.
        if (current_node == start) break;
        current_node = parent[current_node];
    }
    
    // 경로의 도시 개수 출력
    cout << path_stack.size() << endl;

    // 경로의 도시 순서대로 출력 (스택의 특성상 역순으로 출력)
    while (!path_stack.empty()) {
        cout << path_stack.top() << " ";
        path_stack.pop();
    }
    cout << endl;
}

int main() {
    // 입출력 속도 향상 (선택 사항)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    // 1. 도시의 개수 N 입력
    cin >> N;
    // 2. 버스의 개수 M 입력
    cin >> M;

    // 인접 리스트: adj[출발 도시] = {{비용, 도착 도시}, ...}
    // 비용을 first로 두어 우선순위 큐와 정렬 순서를 맞춤
    vector<vector<Edge>> adj(N + 1);

    // 3. 버스 정보 입력
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v}); // u -> v로 가는 비용 w
    }

    int start, end;
    // 4. 구하고자 하는 구간의 출발점과 도착점 입력
    cin >> start >> end;

    // 다익스트라 실행
    dijkstra(N, adj, start, end);

    return 0;
}
