#!/usr/bin/env python

import os
import subprocess32 as subprocess
import re

FNULL = open(os.devnull, 'w')
PYTHON2_TESTS=['reverse']
PYTHON_TESTS=['countchar']
C_TESTS=['decode']

def get_score(test_output):
    lines = test_output.split('\n')
    try:
        last_line = lines[-2]
        last_word = last_line.split(' ')[-1]
        return float(last_word)
    except (IndexError, ValueError):
        return float(0.0)

def run_one_test(test):
    binname = ['./{0}'.format(test), 'input.txt', 'in.txt']
    try:
        output = subprocess.check_output(binname, stderr=FNULL, timeout=30.0)
    except subprocess.CalledProcessError as e:
        output = "Program Error: {0}\n score is 0.0\n".format(e)
        if int(format(e).split(' ')[-1])<0:
            print output
            return output, get_score(output)
    except subprocess.TimeoutExpired:
        output = "Execution Timed out: score is 0.0\n"
        return output, get_score(output)
    except OSError:
        output = "Compilation failed: score is 0.0\n"
        return output, get_score(output)
    binname = ['python', '{0}.py'.format(test), '-i', 'out_{0}.txt'.format(test), '-o', 'in.txt'.format(test)]
    try:
        output = subprocess.check_output(binname, timeout=30.0)
    except subprocess.CalledProcessError:
        output = "Program Error (Output file not in expected format): score is 0.0\n"
    except subprocess.TimeoutExpired:
        output = "Execution Timed out: score is 0.0\n"
    except OSError:
        output = "Compilation failed: score is 0.0\n"
    print output
    return output, get_score(output)

def run_two_test(test):
    binname = ['./{0}'.format(test), 'input.txt', 'in.txt']
    try:
        output = subprocess.check_output(binname, stderr=FNULL, timeout=30.0)
    except subprocess.CalledProcessError as e:
        output = "Program Error: {0}\n score is 0.0\n".format(e)
        if int(format(e).split(' ')[-1])<0:
            print output
            return output, get_score(output)
    except subprocess.TimeoutExpired:
        output = "Execution Timed out: score is 0.0\n"
        return output, get_score(output)
    except OSError:
        output = "Compilation failed: score is 0.0\n"
        return output, get_score(output)
    binname = ['python', '{0}.py'.format(test), '-i', 'out_{0}.txt'.format(test), '-o', 'in.txt'.format(test)]
    try:
        output = subprocess.check_output(binname, timeout=30.0)
    except subprocess.CalledProcessError:
        output = "Program Error (Output file not in expected format): score is 0.0\n"
    except subprocess.TimeoutExpired:
        output = "Execution Timed out: score is 0.0\n"
    except OSError:
        output = "Compilation failed: score is 0.0\n"
    print output
    return output, get_score(output)



def run_decoder_test(test):
    binname = ['./{0}'.format(test)]
    try:
        output = subprocess.check_output(binname, timeout=30.0)
    except subprocess.CalledProcessError:
        output = "Segfault failure on extractBit((char)28, 1) or extractBit((char)125, 5): score is 0.0\n"
    except subprocess.TimeoutExpired:
        output = "Execution Timed out: score is 0.0\n"
    except OSError:
        output = "Compilation failed: score is 0.0\n"
    print output
    return output, get_score(output)

def run_decoder3_test(test):
    binname = ['./{0}_2'.format(test)]
    try:
        output = subprocess.check_output(binname, timeout=30.0)
    except subprocess.CalledProcessError:
        output = "Segfault failure on decodeChar {'0', '1', '1', '0', '1', '0'} or decodeChar {'1', '0', '1', '0', '1', '1'}: score is 0.0\n"
    except subprocess.TimeoutExpired:
        output = "Execution Timed out: score is 0.0\n"
    except OSError:
        output = "Compilation failed: score is 0.0\n"
    print output
    return output, get_score(output)
 
 
def run_decoder2_test(test):
    binname = ['./{0}_segfault'.format(test)]
    try:
        output = subprocess.check_output(binname, timeout=30.0)
        output = "Segfault check on decodeChar(NULL) passed: score is 1.0\n"
    except subprocess.CalledProcessError:
        output = "Segfault on decodeChar(NULL): score is 0.0\n"
    except subprocess.TimeoutExpired:
        output = "Execution Timed out: score is 0.0\n"
    except OSError:
        output = "Compilation failed: score is 0.0\n"
    print output
    return output, get_score(output)
 
def run_tests():
    username = os.path.basename(os.getcwd())
    with open('grader_output.txt', 'w') as f:
        final_score = 0.0
        f.write("====== Contact for regrading checkpoint ======\n")
        f.write("Jor-el: jorel.ucsd@gmail.com\n")
        f.write("Aravind: akumark@eng.ucsd.edu\n")
        f.write("Nima: nganjehloo@gmail.com\n")
	f.write("Ivan: ihuang@eng.ucsd.edu\n")
        f.write("\n********************************************************************************************************************\nThe test cases that were validated are present in the location: /home/linux/ieng6/cs30f/public/hw3_feedback/test/\n********************************************************************************************************************\n\n")
        for test in PYTHON_TESTS:
            output, score = run_one_test(test)
            f.write("====== Partial Score ======\n")
            f.write("{1}: {0}/1.0\n\n".format(score, test))
            f.write("{0}\n\n".format(output))
            final_score+=score
        for test in PYTHON2_TESTS:
            output, score = run_two_test(test)
            f.write("====== Partial Score ======\n")
            f.write("{1}: {0}/1.0\n\n".format(score, test))
            f.write("{0}\n\n".format(output))
            final_score+=score
        for test in C_TESTS:
            output, score = run_decoder_test(test)
            f.write("====== Partial Score ======\n")
            f.write("{0}\n\n".format(output))
            output, score3 = run_decoder3_test(test)
            f.write("{0}\n\n".format(output))
            output, score2 = run_decoder2_test(test)
            f.write("{0}\n\n".format(output))
            score+=score2+score3
            f.write("{1}: {0}/3.0\n\n".format(score, test))
            final_score+=score
 
        f.write("====== Final Scores ======\n")
        f.write("Total: {0}/5.0\n".format(final_score))
    with open('../grades.csv', 'a') as csv:
        csv.write("{user},{score}\n".format(user=username, score=final_score))

if __name__ == '__main__':
    run_tests()
