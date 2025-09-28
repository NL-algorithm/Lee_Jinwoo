import sys

# N과 M (1 <= M <= N <= 8)
input = sys.stdin.read
data = input().split()

if not data:
    # 입력이 없는 경우 처리
    exit()

N = int(data[0])
M = int(data[1])

# 현재까지 만든 수열을 저장할 리스트
sequence = []

# 결과를 한 번에 모아 출력하기 위한 리스트
results = []

def dfs(count, start_num):
    """
    백트래킹 함수 (DFS)

    :param count: 현재까지 선택한 숫자의 개수 (수열의 길이)
    :param start_num: 다음에 선택할 수 있는 가장 작은 숫자
    """
    # 1. 종료 조건: 수열의 길이가 M이 되면 결과를 저장
    if count == M:
        # sequence 리스트의 원소들을 공백으로 구분된 문자열로 만들어 results에 추가
        results.append(' '.join(map(str, sequence)))
        return

    # 2. 반복: start_num부터 N까지의 숫자를 시도
    # 비내림차순 조건(A[i] <= A[i+1])을 위해 i는 start_num부터 시작
    # 중복 허용 조건은 start_num을 'i'로 설정하여 만족시킴
    for i in range(start_num, N + 1):
        # 현재 숫자 i를 수열에 추가
        sequence.append(i)
 
        dfs(count + 1, i)

        sequence.pop()


dfs(0, 1)


print('\n'.join(results))
