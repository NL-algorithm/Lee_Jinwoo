#include <iostream>
#include <vector>

using namespace std;

// 행렬의 크기
int N;
// 거듭제곱 횟수 (B는 10^11까지 가능하므로 long long 사용)
long long B;
// 모듈러 값
const int MOD = 1000;

// N x N 행렬을 표현하는 타입 정의
typedef vector<vector<int>> Matrix;

Matrix multiply(const Matrix& A, const Matrix& B) {
    Matrix result(N, vector<int>(N, 0));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            long long sum = 0; // 합계를 계산할 때 오버플로우 방지를 위해 long long 사용
            for (int k = 0; k < N; ++k) {
                // (A[i][k] * B[k][j]) % MOD 연산을 수행하고 sum에 더함
                sum += (long long)A[i][k] * B[k][j];
            }
            // 최종 sum을 MOD로 나눈 나머지를 결과 행렬에 저장
            result[i][j] = sum % MOD;
        }
    }
    return result;
}


Matrix power(const Matrix& A, long long exponent) {
    // 1. Base Case: B == 1
    // 행렬 A를 반환하되, 이미 입력 과정에서 MOD 연산을 했으므로 그대로 반환해도 되지만
    // 안전을 위해 한번 더 MOD 연산을 적용한 사본을 반환
    if (exponent == 1) {
        Matrix result = A;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                result[i][j] %= MOD;
            }
        }
        return result;
    }
    
    // 2. Recursive Step: A^(B/2) 계산
    Matrix half = power(A, exponent / 2);
    
    // 3. Combine: B가 짝수일 때
    // A^B = A^(B/2) * A^(B/2)
    if (exponent % 2 == 0) {
        return multiply(half, half);
    } 
    // 4. Combine: B가 홀수일 때
    // A^B = A^(B/2) * A^(B/2) * A
    else {
        return multiply(multiply(half, half), A);
    }
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // N과 B 입력
    cin >> N >> B;

    // 행렬 A 입력 및 초기화
    Matrix A(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            // 입력 시부터 MOD 연산을 적용하여 값이 1000을 넘지 않도록 보장
            cin >> A[i][j];
            A[i][j] %= MOD; 
        }
    }

    // B가 0일 때는 단위 행렬이 되어야 하지만, 1 <= B 조건이므로 처리 불필요.
    // B가 1일 때는 power 함수 내에서 처리됨.

    // A^B 계산
    Matrix result = power(A, B);

    // 결과 출력
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << result[i][j] << (j == N - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
