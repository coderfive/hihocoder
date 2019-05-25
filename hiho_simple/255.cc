#include <cstdio>
#include <map>

int r, c;
std::map<int,int> rc, cc, dll, dlt, drt, drr;
const int width = 1000000001;

long long count_pairs(std::map<int,int> &m) {
    long long res = 0;
    for (auto p : m) {
        long long tmp = p.second;
        res += tmp * (tmp-1);
    }
    return res/2;
}

int main() {
    int N;
    std::scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        std::scanf("%d %d", &r, &c);
        rc[r]++;
        cc[c]++;
        if (r <= c)
            dlt[c-r]++;
        else
            dll[r-c]++;
        c = width - c;
        if (r <= c)
            drt[c-r]++;
        else
            drr[r-c]++;
    }
    long long res = count_pairs(rc);
    res += count_pairs(cc);
    res += count_pairs(dll);
    res += count_pairs(dlt);
    res += count_pairs(drt);
    res += count_pairs(drr);
    std::printf("%lld\n", res);
    return 0;
}
