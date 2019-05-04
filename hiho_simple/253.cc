#include <iostream>
#include <cstdio>
#include <string>

struct state {
    int left, right, all;
} smp[101][101];

char mp[101][101];
int N, M;
int area;

void populate(int row, int col, int left) {
    if (left) {
        if (smp[row][col].left)
            return;
        smp[row][col].left = area;
    }
    else if (mp[row][col] == ' ') {
        if (smp[row][col].all)
            return;
        smp[row][col].all = area;
    }
    else {
        if (smp[row][col].right)
            return;
        smp[row][col].right = area;
    }
    // left
    if (col > 0 && (left || mp[row][col] == ' '))
        populate(row, col-1, 0);
    // right
    if (col < M-1 && (!left || mp[row][col] == ' '))
        populate(row, col+1, mp[row][col+1] != ' ');
    // up
    if (row > 0 && ((left && mp[row][col] == '/') || (!left && mp[row][col] != '/')))
        populate(row-1, col, mp[row-1][col] == '\\');
    // down
    if (row < N-1 && ((left && mp[row][col] == '\\') || (!left && mp[row][col] != '\\')))
        populate(row+1, col, mp[row+1][col] == '/');
}

void new_area(int row, int col) {
    if (smp[row][col].all)
        return;
    if (smp[row][col].left && smp[row][col].right)
        return;
    area++;
    if (mp[row][col] == ' ') {
        populate(row, col, 0);
    }
    else {
        if (smp[row][col].left) {
            populate(row, col, 0);
        }
        else {
            populate(row, col, 1);
        }
        new_area(row, col);
    }
}

int main() {
    std::cin >> N >> M;
    std::string s;
    while (std::getchar() != '\n');
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            mp[i][j] = std::getchar();
        char c;
        while ((c = std::getchar()) != '\n');
    }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            new_area(i, j);
    std::cout << area << std::endl;
    return 0;
}
