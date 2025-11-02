#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 각 테스트 케이스를 해결하는 함수
void solve() {
    int N, K; // 건물의 개수 N, 건설순서 규칙 K
    cin >> N >> K;

    vector<int> D(N + 1); // 각 건물당 건설 시간 (1-based index)
    for (int i = 1; i <= N; ++i) {
        cin >> D[i];
    }

    vector<vector<int>> adj(N + 1); // 인접 리스트
    vector<int> inDegree(N + 1, 0);   // 진입 차수
    
    for (int i = 0; i < K; ++i) {
        int X, Y;
        cin >> X >> Y;
        adj[X].push_back(Y); // X -> Y 간선 추가
        inDegree[Y]++;       // Y의 진입 차수 증가
    }

    int W; // 승리를 위해 건설해야 할 건물 번호
    cin >> W;

    // dp[i] = 건물 i가 건설 완료되는 최소 시간
    vector<int> dp(N + 1, 0);
    queue<int> q;

    // 1. 진입 차수가 0인 노드를 큐에 추가하고 DP 테이블 초기화
    for (int i = 1; i <= N; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
            dp[i] = D[i]; // 선행 건물이 없으므로, 완료 시간 = 건설 시간
        }
    }

    // 2. 위상 정렬 실행
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            // v의 완료 시간은 (현재까지 계산된 v의 완료 시간)과 
            // (u의 완료 시간 + v의 건설 시간) 중 더 큰 값
            dp[v] = max(dp[v], dp[u] + D[v]);
            
            inDegree[v]--; // 선행 건물 u가 처리되었으므로 v의 진입 차수 감소
            
            if (inDegree[v] == 0) {
                // v의 모든 선행 건물이 완료되었으므로 큐에 추가
                q.push(v);
            }
        }
    }

    // 3. 목표 건물의 최소 완료 시간 출력
    cout << dp[W] << '\n';
}

int main() {
    // 입출력 속도 향상 (C++ 표준 스트림 동기화 해제)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T; // 테스트케이스 개수
    cin >> T;
    while (T--) {
        solve(); // 각 테스트 케이스 해결
    }

    return 0;
}
