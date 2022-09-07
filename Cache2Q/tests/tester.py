#!/usr/bin/env python3

import sys
import os
import tempfile
import subprocess

relative_path = "../build/"

args = sys.argv[1:]

args[0] = relative_path + args[0]

tmp_file = ".tmp"

number = 1
while True:
    test_name = "test" + str(number)
    number += 1

    if (not os.path.exists(test_name + ".in")):
        break

    inputf = open(test_name + ".in", "r")
    output = open(tmp_file, "w+")

    cmd = args
    subprocess.call(cmd, stdin=inputf, stdout=output)

    output.seek(0)

    answer = []

    for line in output:
        [answer.append(x) for x in line.strip().split(' ')]

    correct = []

    correct_test_file = open(test_name + ".out", "r")

    for line in correct_test_file:
        [correct.append(x) for x in line.strip().split(' ')]

    failed = False
    if (len(answer) != len(correct)):
        failed = True

    for i in range(len(answer)):
        if failed == True or answer[i] != correct[i]:
            failed = True
            break

    if failed:
        print(test_name + " FAILED.")
        inputf.seek(0)
        output.seek(0)
        correct_test_file.seek(0)

        print("input:")
        for line in inputf:
            print(line, end="")

        print("expected:")
        for line in correct_test_file:
            print(line)

        print("got:")
        for line in output:
            print(line)
    else:
        print(test_name + " passed.")

    inputf.close()
    output.close()
    correct_test_file.close()

    os.remove(tmp_file)
