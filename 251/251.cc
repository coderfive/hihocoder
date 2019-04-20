#include <iostream>
#include <vector>

int main() {
    int N;
    std::cin >> N;
    std::vector<int> pn;
    pn.reserve(N+10);
    pn.push_back(2);
    pn.push_back(3);
    int i, j;
    for (i = 5; i < N; i+=2) {
        for (j = 0; pn[j]*pn[j] < i; j++) {
            if (i % pn[j] == 0)
                break;
        }
        if (i % pn[j] != 0)
            pn.push_back(i);
    }
    for (i = 0, j = pn.size()-1; i <= j;) {
        while (i <= j && pn[i] + pn[j] > N) j--;
        while (i <= j && pn[i] + pn[j] < N) i++;
        if (pn[i] + pn[j] == N)
            break;
    }
    std::cout << pn[i] << ' ' << pn[j] << std::endl;
    return 0;
}
