#include <cstdio>
#include <cmath>
#include <utility>
using namespace std;

long long a[100001], b[100001], total, target, res;
int main() {
    int N;
    std::scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        std::scanf("%lld %lld", a+i, b+i);
        total += a[i] + b[i];
    }
    target = total/2/N;
    int i = 0, j = 0;
    for (int i = 0, j = 0; i < N; i++) {
        if (a[i] == target && b[i] == target)
            continue;
        long long ta = a[i], tb = b[i];
        if (ta > tb) swap(ta, tb);
        if (ta < target && tb > target) {
            if (target-ta > tb-target) {
                ta += tb-target;
                res += tb-target;
                tb = target;
            }
            else {
                tb -= target-ta;
                res += target-ta;
                ta = target;
            }
            if (tb == target && ta == target)
                continue;
        }
        long long dtb = abs(tb-target), dta = abs(ta-target);
        res += dtb + dta;
        if (a[i] > b[i]) {
            a[i+1] += tb-target;
            b[i+1] += ta-target;
        }
        else {
            a[i+1] += ta-target;
            b[i+1] += tb-target;
        }
    }
    std::printf("%lld\n", res);
    return 0;
}
