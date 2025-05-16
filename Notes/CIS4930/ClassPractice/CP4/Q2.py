from bisect import bisect_left

def LIS(arr):
    n = len(arr)
    if n == 0:
        print(0)
        return

    # Elelments in traditional LIS method
    dp = []
    # Indices for LIS.
    indices = [-1] * n
    prev = [-1] * n

    for i in range(n):
        pos = bisect_left(dp, arr[i])

        if pos == len(dp):
            dp.append(arr[i])
        else:
            dp[pos] = arr[i]

        indices[pos] = i

        if pos > 0:
            prev[i] = indices[pos - 1]

    # Reconstruct LIS
    lis = []
    end = indices[len(dp) - 1]
    while end != -1:
        lis.append(end)
        end = prev[end]
    lis.reverse()

    print(len(lis))
    print(" ".join(map(str, lis)))


def main():
    while True:
        try:
            line = input().strip()
            if not line:
                break
            n = int(line)
            arr = list(map(int, input().split()))
            if len(arr) != n:
                print("HUH")
                continue
            LIS(arr)
        except (EOFError, ValueError):
            break


if __name__ == "__main__":
    main()
