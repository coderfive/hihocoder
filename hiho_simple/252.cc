#include <iostream>
#include <map>
#include <algorithm>


int main() {
    int N, w, b, tmp;
    std::cin >> N;
    std::map<int,int> mp;
    for (int i = 0; i < N; i++) {
        std::cin >> b;
        w = 0;
        while (b--) {
            std::cin >> tmp;
            w += tmp;
            if (b == 0)
                break;
            mp[w]++;
        }
    }
    int m = 0;
    for (auto i = mp.begin(); i != mp.end(); ++i)
        if (i->second > m)
            m = i->second;
    std::cout << (N - m) << std::endl;

    return 0;
}
