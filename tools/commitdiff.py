#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import os
import sys


def diff(old, new, commit, output):
    newlist = {}
    for line in new:
        vec = line.split(',')
    return

if __name__ == '__main__':
    with open(sys.argv[1], "r") as old:
        with open(sys.argv[2], "r") as new:
            diff(old, new, sys.argv[3], sys.stderr)
