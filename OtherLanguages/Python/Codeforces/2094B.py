
import sys
input = sys.stdin.readline

n = int(input())
for _ in range(n):
    a, b, l, r = map(int, input().split())
    d = a-b
    x = min(-l, d, r-l)
    d -= x
    l += x
    y = min(r, d, r-l)
    r -= y
    print(l, r)