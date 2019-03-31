import time
import os, random, sys

def bfs(ch, param, depth, node=1):
    if len(ch[node]) == 0:
        param[1].append(node)
    else:
        param[0][depth+1] += ch[node]
        for c in ch[node]:
            bfs(ch, param, depth+1, c)

def gen_Nnodes(N=10):
    children = [list() for i in range(N+1)]
    parent = [1] * (N+1)
    parent[1] = 0
    level = [0] * (N+1)
    used = [1]
    unused = [ i for i in range(2, N+1) ]
    while len(unused) > 0:
        n = random.choice(unused)
        unused.remove(n)
        pa = random.choice(used)
        used.append(n)
        children[pa].append(n)
        parent[n] = pa
        level[n] = 1 + level[pa]
    res = ''
    param = [[list() for i in range(N+1)], []]
    param[0][0] = [1]
    bfs(children, param, 0)
    while len(param[0][-1]) == 0:
        param[0].pop()
    km = [[0] * (N+1) for i in range(N+1)]
    # calculate dist
    for i in range(1, N+1):
        if len(children[i]) != 0:
            continue
        for j in range(1, N+1):
            if len(children[j]) != 0 or i == j:
                continue
            km[i][j] = km[j][i] = get_dist(parent, level, i, j)
    res += '%d %d %d\n' % (N, len(param[0]), len(param[1]))
    res += ' '.join(str(len(p)) for p in param[0]) + '\n'
    for p in param[0]:
        res += ' '.join(str(n) for n in p) + '\n'
    res += ' '.join(str(n) for n in param[1]) + '\n'
    for i in param[1]:
        res += ' '.join(str(km[i][j]) for j in param[1]) + '\n'
    out = ' '.join(str(parent[n]) for n in range(1,N+1)) + ' '
    graph = 'digraph 248 {\n'
    graph += get_edges(children)
    graph += '}'
    return (res, out, graph)

def get_edges(ch, node=1):
    res = ''
    for i in ch[node]:
        res += '%d -> %d;\n' % (node, i)
    for i in ch[node]:
        res += get_edges(ch, i)
    return res

def get_dist(pa, level, i, j):
    if level[i] < level[j]:
        i, j = j, i
    d = 0
    while level[i] != level[j]:
        d += 1
        i = pa[i]
    while i != j:
        d += 2
        i = pa[i]
        j = pa[j]
    return d

if __name__ == '__main__':
    if len(sys.argv) > 1:
        ins, outs, graph = gen_Nnodes(int(sys.argv[1]))
    else:
        ins, outs, graph = gen_Nnodes()
    with open('in', 'w') as f:
        f.write(ins)
    with open('out', 'w') as f:
        f.write(outs)
    with open('graph', 'w') as f:
        f.write(graph)
    os.system('dot -Tsvg graph -O')
