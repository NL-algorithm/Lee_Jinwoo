import sys

# 문제에서 주어진 모듈러 값
MOD = 1000000007

def power(base, exp):
    res = 1
    base %= MOD
    while exp > 0:
        # 지수가 홀수이면, 현재 base를 결과에 곱함
        if exp % 2 == 1:
            res = (res * base) % MOD
        
        # 지수를 2로 나누고, base를 제곱함
        exp >>= 1  # exp = exp // 2
        base = (base * base) % MOD
    return res

def mod_inverse(n):

    return power(n, MOD - 2)


input = sys.stdin.readline

# 주사위의 개수 M
M = int(input())

total_expected_value = 0

for _ in range(M):
    # N_i: i번째 주사위의 면 수
    # S_i: i번째 주사위의 모든 면의 합
    N_i, S_i = map(int, input().split())
    
    # i번째 주사위의 기댓값 E_i = S_i / N_i
    # 모듈러 연산으로 변환: E_i ≡ S_i * (N_i)^-1 (mod MOD)
    
    # 1. N_i의 모듈러 곱셈 역원 (N_i)^-1 을 구합니다.
    N_i_inv = mod_inverse(N_i)
    
    # 2. E_i = (S_i * N_i_inv) % MOD 를 계산합니다.
    #    (a * b) % M = ((a % M) * (b % M)) % M
    #    S_i가 MOD보다 클 수도 있으므로 S_i % MOD를 먼저 수행하는 것이 안전합니다.
    E_i = ((S_i % MOD) * (N_i_inv % MOD)) % MOD
    
    # 3. 모든 주사위의 기댓값을 더합니다. (덧셈도 모듈러 연산)
    total_expected_value = (total_expected_value + E_i) % MOD

# 최종 결과 출력
print(total_expected_value)
