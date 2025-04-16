import sys
input = sys.stdin.readline

n = int(input())
for _ in range(n):
    initials = [s[0] for s in input().split()]
    print("".join(initials))