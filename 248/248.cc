#include <vector>
#include <iostream>

struct lnode { int left, right ; };
lnode level_nodes[101][101];
int level[101];
int child[101];
int parent[101];
bool is_leaf[101];
int dist[101][101];

int main () {
    int N, M, K, edges = 1;
    std::cin >> N >> M >> K;
    std::vector<int> A(M);
    for (auto & a : A)
        std::cin >> a;
    int last = 0, cur;
    for (int i = 0; i < M; i++) {
        last = 0;
        for (int j = 0; j < A[i]; j++) {
            std::cin >> cur;
            level[cur] = i;
            level_nodes[i][cur].left = last;
            level_nodes[i][last].right = cur;
            last = cur;
        }
        level_nodes[i][0].left = cur;
    }
    std::vector<int> leaves(K);
    for (auto & a : leaves) {
        std::cin >> a;
        is_leaf[a] = true;
    }
    parent[level_nodes[0][0].right] = 0;
    for (int i = 0; i < K; i++)
        for (int j = 0; j < K; j++) {
            std::cin >> cur;
            dist[leaves[i]][leaves[j]] = cur;
            dist[leaves[j]][leaves[i]] = cur;
        }
    for (int l = M-1; l > 0; l--) {
        int n = level_nodes[l][0].right;
        int tmp = n;
        int il = l-1;
        for (int in = level_nodes[il][0].right; in ; in = level_nodes[il][in].right) {
            if (is_leaf[in])
                continue;
            parent[tmp] = in;
            child[in] = tmp;
            tmp = in;
            break;
        }
    }
    for (int l = M-1; l > 0; l--) {
        int n = level_nodes[l][0].right;
        for (int j = 1; j < A[l]; j++) {
            int left = n;
            n = level_nodes[l][n].right;
            int ch = left, nch = n;
            while (!is_leaf[ch])
                ch = child[ch];
            while (!is_leaf[nch])
                nch = child[nch];
            int d = dist[ch][nch] - (level[ch] - level[left]) - (level[nch]-level[n]);
            int il = l-1;
            if (d == 2)
                parent[n] = parent[left];
            else {
                left = parent[left];
                for (int in = level_nodes[il][left].right; in ; in = level_nodes[il][in].right) {
                    if (is_leaf[in])
                        continue;
                    parent[n] = in;
                    child[in] = n;
                    break;
                }
            }
        }
    }
    for (int i = 1; i <= N; i++)
        std::cout << parent[i] << ' ';
    return 0;
}
