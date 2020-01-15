#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import os
import sys


d = {}
def diff(old, new, commit, output):
    for line in old:
        vec = line.strip().rsplit(';', 1)
        if vec[0] in d:
            sys.stdout.write("{};error\n", commit)
            d[vec[0]] = vec[1]
        else:
            d.setdefault(vec[0], vec[1])

    # 如果new的项
    for line in new:
        vec = line.strip().rsplit(';', 1)
        if vec[0] in d:
            # 如果新的有了，且非method，比较最后一个字段，不一样则输出MODIFIED
            if "METHOD" in vec[0]:
                if d[vec[0]] != vec[1]:
                    output.write("{},{},MODIFIED\n".format(commit, vec[0]))
                    # print(d[vec[0]])
            # 只要找到就删除
            del d[vec[0]]
        else:
            # 如果没有，则输出ADD的
            output.write("{};{};ADD\n".format(commit, vec[0]))

    # 删除需要另外查找，在旧的有，但是新的没有
    for k, v in d.iteritems():
        output.write("{};{};DELETE\n".format(commit, k))
    return

if __name__ == '__main__':
    # arg 1. 旧commit的文件
    # arg 2. 新commit的文件
    # arg 3. 旧commit号
    with open(sys.argv[1], "r") as old:
        with open(sys.argv[2], "r") as new:
            diff(old, new, sys.argv[3], sys.stderr)
    sys.stderr.flush()
