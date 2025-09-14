#include <iostream>
#include <vector>

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

const int MAX_SIZE = 1206;

int main() {
    OptimizeIO();

    int n, m; // n: 표의 크기, m: 합을 구할 횟수
    std::cin >> n >> m;

    int prefixSum[MAX_SIZE][MAX_SIZE] = {0};

    // 1. 2차원 누적 합 테이블 생성 
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= n; ++c) {
            int currentValue;
            std::cin >> currentValue;
            
            // 누적 합 계산 공식:P[r][c] = 현재값 + P[r-1][c] + P[r][c-1] - P[r-1][c-1]
            // (r-1, c-1)까지의 합이 두 번 더해졌으므로 한 번 빼준다.
            prefixSum[r][c] = currentValue + prefixSum[r - 1][c] + prefixSum[r][c - 1] - prefixSum[r - 1][c - 1];
        }
    }

    // 2. M개의 쿼리 처리 
    for (int i = 0; i < m; ++i) {
        int r1, c1, r2, c2; // r1-c1부터 r2-c2까지의 구간
        std::cin >> r1 >> c1 >> r2 >> c2;

        /* 특정 구간의 합 계산 공식:
           결과 = P[r2][c2] - P[r1-1][c2] - P[r2][c1-1] + P[r1-1][c1-1]
           두 번 제외된 (r1-1, c1-1)까지의 합을 다시 더해준다.*/
        int result = prefixSum[r2][c2] - prefixSum[r1 - 1][c2] - prefixSum[r2][c1 - 1] + prefixSum[r1 - 1][c1 - 1];
        
        std::cout << result << '\n';
    }

    return 0;
}
