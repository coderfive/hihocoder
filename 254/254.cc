#include <cstdio>
#include <algorithm>

int a[100001];

long long llm(int lhs, int rhs) {
    return ((long long)a[lhs]) * ((long long)a[rhs]) * ((long long)(a[lhs]&a[rhs]));
}

// [start, end]
long long check_range(int start, int end, int bidx) {
    if (bidx == 0) {
        if (end == start)
            return 0;
        return llm(end, end-1);
    }
    if (start == end)
        return 0;
    if ((a[end] & (1<<bidx)) == 0)
        return check_range(start, end, bidx-1);
    long long res = llm(end, end-1), tmp;
    int ls = start, le = end;
    while (ls <= le && (a[le] & (1<<bidx))) le--;
    if (end-le == 1) {
        for (int i = end-1; i >= start; i--) {
            tmp = llm(i, end);
            if (tmp > res)
                res = tmp;
        }
        tmp = check_range(start, end-1, bidx-1);
        if (tmp > res)
            res = tmp;
    } else {
        tmp = check_range(le+1, end, bidx-1);
        if (tmp > res)
            res = tmp;
    }
    return res;
}

int main() {
    int T;
    int N;
    std::scanf("%d", &T);
    while (T--) {
        std::scanf("%d", &N);
        for (int i = 0; i < N; i++)
            std::scanf("%d", a+i);
        std::sort(a, a+N);
        int bidx = 19;
        while (bidx >= 0 && (a[N-1] & (1<<bidx)) == 0) bidx--;
        long long r = 0;
        if (bidx >= 0)
            r = check_range(0, N-1, bidx);
        std::printf("%lld\n", r);
    }
    return 0;
}
