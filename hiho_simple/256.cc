#include <iostream>

long long N, Q, res;
int main() {
    std::cin >> N >> Q;
    res = N;
    long long r = 2, tmp, t2, base = Q;
    for (; r < N*2; r *= 2) {
        tmp = (N+r-1)/r + base;
        t2 = (N+r-(r-1)*Q)/(r+1) + Q + base;
        if (t2 < tmp) tmp = t2;
        t2 = (N+r+r-2-Q)/(r+r-1) + Q + base;
        if (t2 < tmp) tmp = t2;
        base += Q;
        if (res > tmp) res = tmp;
    }
    std::cout << res << std::endl;
    return 0;
}
