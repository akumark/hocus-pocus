#!/usr/bin/env python

import os
import subprocess32 as subprocess
import re

TESTS=['createlist', 'insert', 'getmax', 'getmin', 'search', 'popmin', 'remove', 'print', 'nulls']
ARM_TESTS = ['getmax_arm', 'getmin_arm', 'nulls_arm']

def get_score(test_output):
    lines = test_output.split('\n')
    last_line = lines[-2]
    last_word = last_line.split(' ')[-1]
    return float(last_word)

def run_one_test(test, outfile):
    outfile.write("====== Testing {0} ======\n".format(test))
    bin_name = "./test_{0}".format(test)
    try:
        output = subprocess.check_output([bin_name], timeout=30.0)
    except subprocess.CalledProcessError:
        output = "Program Error: score is 0.0\n"
    except subprocess.TimeoutExpired:
        output = "Execution Timed out: score is 0.0\n"
    except OSError:
        output = "Compilation failed: score is 0.0\n"
    outfile.write(output)

    if test!= 'print':
        part_score = get_score(output)
    else:
        if output.startswith("0 0 1 2 3 3 5 8 15 19"):
            part_score = 1.0
            outfile.write("Final score is 1.0\n")
        else:
            part_score = 0.0
            outfile.write("0.0\n")
    return (output, part_score)


def run_tests():
    username = os.path.basename(os.getcwd())
    with open('grader_output.txt', 'w') as f:
        score = 0
        arm_score = 0
        for test in TESTS:
            output, part_score = run_one_test(test, f)
            score = score + part_score
        for test in ARM_TESTS:
            output, part_score = run_one_test(test, f)
            arm_score = arm_score + part_score
        f.write("====== Final Scores ======\n")
        f.write("C: {0}/20\n".format(score))
        f.write("ARM: {0}/5\n".format(arm_score))
    with open('../grades.csv', 'a') as csv:
        csv.write("{user},{score},{asm}\n".format(user=username, score=score, asm=arm_score))

if __name__ == '__main__':
    run_tests()
