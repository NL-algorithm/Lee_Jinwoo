import sys
input = sys.stdin.readline

def solve():
    # 1. 입력 받기
    try:
        N = int(input())
        if N == 0:
            print(0)
            return
        A = list(map(int, input().split()))
    except EOFError:
        # 입력이 없거나 비어 있을 경우 처리
        print(0)
        return
    except Exception:
        # 기타 입력 오류 처리 (예: 빈 줄)
        return

    # 2. DP 배열 초기화
    # dp_inc[i]: A[i]를 마지막으로 하는 가장 긴 증가하는 부분 수열의 길이
    dp_inc = [1] * N
    # dp_dec[i]: A[i]를 시작으로 하는 가장 긴 감소하는 부분 수열의 길이 (A[i]가 최고점)
    dp_dec = [1] * N
    
    # 3. LIS (가장 긴 증가하는 부분 수열) 계산
    # 앞에서 뒤로 순회
    for i in range(N):
        for j in range(i):
            if A[j] < A[i]:
                # A[i]가 A[j]보다 크다면, A[i]를 뒤에 붙여 길이를 갱신할 수 있다.
                dp_inc[i] = max(dp_inc[i], dp_inc[j] + 1)
                
    # 4. LDS (가장 긴 감소하는 부분 수열) 계산
    # 뒤에서 앞으로 역순으로 순회
    for i in range(N - 1, -1, -1):
        for j in range(i + 1, N):
            if A[j] < A[i]:
                # A[i]를 최고점으로 할 때, A[i]보다 작은 A[j]를 이어붙여 길이를 갱신할 수 있다.
                # (A[i] > A[j] > A[k]...)
                dp_dec[i] = max(dp_dec[i], dp_dec[j] + 1)

    # 5. 최댓값 찾기
    max_lbs_length = 0
    for i in range(N):
        # A[i]를 최고점으로 하는 바이토닉 수열의 길이 = LIS(증가) + LDS(감소) - 1(A[i] 중복)
        current_length = dp_inc[i] + dp_dec[i] - 1
        max_lbs_length = max(max_lbs_length, current_length)
        
    print(max_lbs_length)

solve()
