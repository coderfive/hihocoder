#!/usr/bin/python3
import subprocess, sys
import random

def get_correct_result(a):
    res = 0
    l = 0
    r = 0
    for i in range(len(a)):
        for j in range(i+1, len(a)):
            tmp = a[i] * a[j] * (a[i]&a[j])
            if tmp > res:
                l, r = i, j
                res = tmp
    return res, a[l], a[r]

def doit(N, amin, amax, cmd):
    text = "1\n%d\n" % N
    a = []
    for i in range(N):
        a.append(random.randint(amin, amax))
        text += str(a[-1]) + ' '
    #print("text is:\n" + text)
    po = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    #print("text mode: ", po.text_mode)
    so, se = po.communicate(input=text.encode('utf8'))
    correct_result = get_correct_result(a)
    res = int(so.decode('utf8').strip())
    if res != correct_result[0]:
        print("error! expected: %s, got: %ld" % (str(correct_result),res))
        print("input:\n" + text)
        return 1
    return 0
    

# 254.py N Amin Amax -- cmd [arg1] [arg2]...
if __name__ == '__main__':
    if len(sys.argv) < 6:
        print("./254.py N Amin Amax -- cmd [arg1] [arg2]..")
        sys.exit(1)
    r = doit(int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]), sys.argv[5:])
    sys.exit(r)
