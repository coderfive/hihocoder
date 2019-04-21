#include <iostream>
#include <vector>

int main() {
    int N;
    std::cin >> N;
    std::vector<bool> isprime(N+1, true);
    std::vector<int> primes;
    for (int i = 2; i <= N; i++) {
        if (isprime[i])
            primes.push_back(i);
        for (auto p : primes) {
            if (p*i <= N)
                isprime[p*i] = false;
            else
                break;
            if (i % p == 0)
                break;
        }
    }
    std::cout << primes.size() << std::endl;

    return 0;
}
