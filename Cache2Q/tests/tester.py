#!/usr/bin/env python3

import sys
import os
import tempfile
import subprocess

relative_path = "../build/"

args = sys.argv[1:]

args[0] = relative_path + args[0]

number = 1
while True:
    test_name = "test" + str(number)
    number += 1

    if (not os.path.exists(test_name + ".in")):
        break

    inputf = open(test_name + ".in", "r")
    output = open(".tmp", "w+")

    cmd = args + ["<", test_name]
    subprocess.call(cmd, stdout=output, stdin=inputf, stderr=None)

    output.seek(0)

    answer = []

    for line in output:
        [answer.append(x) for x in line.strip().split(' ')]

    correct = []

    correct_test_file = open(test_name + ".out", "r")

    for line in correct_test_file:
        [correct.append(x) for x in line.strip().split(' ')]

    if (len(answer) != len(correct)):
        print(test_name + " failed.")
        continue

    failed = False
    for i in range(len(answer)):
        if answer[i] != correct[i]:
            failed = True
            break

    if (failed):
        print(test_name + " failed.")
    else:
        print(test_name + " passed.")
