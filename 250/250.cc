#include <iostream>
#include <utility>
#include <cstring>
#include <vector>

char s[1001];
long long mod = 1000000000 + 7;
long long fn[1001][1001];

std::pair<int, long long> do_it(char *s) {
    int left = 0, right = 0, d = 0;
    int sum = 0;
    std::vector<int> par;
    long long res = 1;
    for (int i = 0; s[i] != '\0'; i++) {
        auto c = s[i];
        if (c == '(') {
            left++;
            sum++;
        }
        else {
            sum--;
            right++;
            if (sum == -1) {
                sum = 0;
                d++;
                par.push_back(1);
            }
            else
                par.push_back(0);
        }
    }
    int cum = 0;
    for (auto i = par.rbegin(); i != par.rend(); ++i) {
        if (*i == 0)
            *i = cum;
        else
            *i = ++cum;
    }
    if (par.size() <= 1 || par[0] == 0)
        return std::make_pair(d, res);
    int pos = par.size()-1;
    while (par[pos] == 0)
        pos--;
    fn[pos][1] = 1;
    fn[pos][2] = 0;
    for (int i = pos-1; i >= 0; i--) {
        for (int j = 1; j < par[i]; j++) {
            fn[i][j] = fn[i+1][j] + 1;
        }
        if (par[i] == par[i+1])
            fn[i][par[i]] = fn[i+1][par[i]] + 1;
        else
            fn[i][par[i]] = fn[i+1][par[i]-1] + 1;
        if (i == 0)
            break;
        for (int j = 1; j <= par[i]; j++) {
            fn[i][j] += fn[i][j-1];
            fn[i][j] %= mod;
        }
        fn[i][par[i]+1] = 0;
    }
    return std::make_pair(d, fn[0][par[0]]);
}

char mp[128];
int main() {
    mp['('] = ')';
    mp[')'] = '(';
    std::cin >> s;
    auto p = do_it(s);
    for (int i = 0, j = std::strlen(s)-1; i < j; i++, j--)
        std::swap(s[i], s[j]);
    for (int i = 0; s[i] != '\0'; i++)
        s[i] = mp[s[i]];
    auto p2 = do_it(s);
    p.first += p2.first;
    p.second = p.second * p2.second % mod;
    std::cout << p.first << ' ' << p.second;
    return 0;
}
