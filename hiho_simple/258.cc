#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int dp[20001];
int N, f, in, ip, c;
vector<int> children[2001];
int in_needed[2001], in_sup[2001], cost[2001], c_cost[2001];

void do_dp(int e) {
    if (in_needed[e] == 0) {
        c_cost[e] = cost[e];
        return;
    }
    for (auto i : children[e]) {
        do_dp(i);
    }
    if (children[e].size() == 0) {
        c_cost[e] = cost[e];
        return;
    }
    int ine = in_needed[e];
    memset(dp, 0, sizeof(int) * (in_needed[e]+1));
    for (auto i : children[e]) {
        if (c_cost[i] == 0)
            continue;
        if (in_sup[i] >= in_needed[e]) {
            if (c_cost[i] < dp[in_needed[e]] || dp[in_needed[e]] == 0) {
                dp[in_needed[e]] = c_cost[i];
            }
            continue;
        }
        for (int j = in_needed[e]-1; j + in_sup[i] >= in_needed[e]; j--) {
            if (dp[j] && (dp[ine] == 0 || dp[j] + c_cost[i] < dp[in_needed[e]]))
                dp[in_needed[e]] = dp[j] + c_cost[i];
        }
        for (int j = in_needed[e]; j > in_sup[i]; j--) {
            int k = j-in_sup[i];
            if (dp[k]) {
                if (dp[j] == 0 || dp[k] + c_cost[i] < dp[j])
                    dp[j] = dp[j-in_sup[i]] + c_cost[i];
            }
        }
        if (dp[in_sup[i]] == 0 || c_cost[i] < dp[in_sup[i]])
            dp[in_sup[i]] = c_cost[i];
    }
    c_cost[e] = dp[in_needed[e]];
    if (c_cost[e])
        c_cost[e] += cost[e];
}

int main(int argc, char **argv) {
    scanf("%d", &N);
    int el;
    for (int i = 1; i <= N; i++) {
        scanf("%d %d %d %d", &f, &in, &ip, &c);
        children[f].push_back(i);
        in_needed[i] = in;
        in_sup[i] = ip;
        cost[i] = c;
        if (f == 0) el = i;
    }
    do_dp(el);
    int res = c_cost[el];
    if (res == 0)
        res = -1;
    printf("%d\n", res);
    return 0;
}
