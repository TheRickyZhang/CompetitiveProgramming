import sys
input = sys.stdin.readline

def chunk(list):
    n = len(list)
    res = []
    i = 0
    while i < n:
        j = i
        while j < n and list[i] == list[j]:
            j += 1
        res.append(j-i)
        i = j
    return res


def solve():
    s = input()
    t = input()
    a = chunk(s)
    b = chunk(t)
    # print(a)
    # print(b)
    if len(a) != len(b) or s[0] != t[0]:
        print("NO")
        return
    for i in range(len(a)):
        if a[i] > b[i] or 2 * a[i] < b[i]:
            print("NO")
            return
    print("YES")

def main():
    t = int(input())
    for _ in range(t):
        solve()

if __name__ == '__main__':
    main()