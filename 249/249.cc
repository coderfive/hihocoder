#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

int N, M, D, dx, dy, sc, mc, dhp, dap;
int total_nodes;
int init_state;
int state[6][1<<20];
bool done[6][1<<20];
char mp[7][7];
std::vector<std::pair<int, int>> hp;
bool is_front[21];
bool is_special[21];
bool is_monster[21];
bool slate_removed[21];
struct link_node {
    int prev, next, v;
};
struct link_node front[21];
struct link_node &front_head = front[20];
int monster_alive;

void add_node_after(int n, int new_node, link_node ln[]) {
    link_node &cur = ln[n];
    link_node &next = ln[cur.next];
    link_node &nn = ln[new_node];
    cur.next = new_node;
    next.prev = new_node;
    nn.prev = n;
    nn.next = next.v;
}

link_node & remove_node(int n, link_node ln[]) {
    link_node &af = ln[ln[n].next];
    link_node &bf = ln[ln[n].prev];
    af.prev = bf.v;
    bf.next = af.v;
    return ln[n];
}

void add_node_tail(int new_node, link_node ln[]) {
    add_node_after(ln[20].prev, new_node, ln);
}

void explore_front(int node) {
    int cur;
    // up
    cur = node - M;
    if (cur >= 0 && !is_front[cur] && !slate_removed[cur]) {
        is_front[cur] = true;
        add_node_tail(cur, front);
    }
    // down
    cur = node + M;
    if (cur < total_nodes && !is_front[cur] && !slate_removed[cur]) {
        is_front[cur] = true;
        add_node_tail(cur, front);
    }
    // left
    cur = node - 1;
    if (node % M != 0 && !is_front[cur] && !slate_removed[cur]) {
        is_front[cur] = true;
        add_node_tail(cur, front);
    }
    // right
    cur = node + 1;
    if (node % M != M-1 && !is_front[cur] && !slate_removed[cur]) {
        is_front[cur] = true;
        add_node_tail(cur, front);
    }
}

int run(int buff, int cur_state) {
    if (done[buff][cur_state])
        return state[buff][cur_state];
    int hit = -1, this_hit;
    int local_state, local_buff, front_last, attack;
    if (monster_alive == 0) goto out;
    for (int n = front_head.next; n != front_head.v; n = front[n].next) {
        auto &node = remove_node(n, front);
        front_last = front_head.prev;
        local_state = cur_state ^ (1<<n);
        slate_removed[n] = true;
        local_buff = buff-1;
        if (local_buff == -1)
            local_buff = 0;
        this_hit = 0;
        if (is_monster[n]) {
            monster_alive--;
            attack = (hp[n].first + dap - 1) / dap;
            if (attack <= local_buff) {
                local_buff -= attack;
            }
            else {
                this_hit = (attack-local_buff) * hp[n].second;
                local_buff = 0;
            }
            if (is_special[n]) local_buff = 5;
        }
        explore_front(n);
        this_hit += run(local_buff, local_state);
        if (hit == -1)
            hit = this_hit;
        else if (hit > this_hit)
            hit = this_hit;
        for (int i = front[front_last].next; i != front_head.v; i = front[i].next) {
            auto &node = remove_node(i, front);
            is_front[i] = false;
        }
        if (is_monster[n])
            monster_alive++;
        slate_removed[n] = false;
        add_node_after(node.prev, n, front);
    }
    if (hit != -1)
        state[buff][cur_state] = hit;
out:
    done[buff][cur_state] = true;
    return state[buff][cur_state];
}

int main() {
    std::cin >> N >> M;
    total_nodes = N*M;
    int dots = 0;
    hp.resize(N*M);
    for (int i = 0; i < 21; i++) {
        front[i].next = front[i].prev = front[i].v = i;
    }
    for (int i = 0; i < N; i++) {
        std::cin >> mp[i];
        dots += std::count_if(mp[i], mp[i]+M, [](char c) { return c == '.'; });
    }
    int a, b, pos = 0;
    for (int i = 0; i < N*M - dots - 1; i++) {
        std::cin >> a >> b;
        int row = pos/M, col = pos%M;
        for (; mp[row][col] != 'M' && mp[row][col] != 'S'; pos++) {
            if (++col == M) {
                row++;
                col = 0;
            }
        }
        if (mp[row][col] == 'S') is_special[pos] = true;
        is_monster[pos] = true;
        monster_alive++;
        hp[pos++] = std::make_pair(a,b);
    }
    while (mp[D/M][D%M] != 'D') D++;
    std::cin >> dhp >> dap;
    slate_removed[D] = true;
    explore_front(D);
    init_state = (1<<total_nodes)-1;
    init_state ^= 1<<D;
    run(5, init_state);
    if (dhp > state[5][init_state])
        std::cout << dhp - state[5][init_state] << std::endl;
    else
        std::cout << "DEAD\n";
    return 0;
}
