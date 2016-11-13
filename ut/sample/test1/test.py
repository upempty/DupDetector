import os
import sys
import json
import time

def get_duplicate(filename):
    with open(filename, 'r') as result:
        file_op = {}
        dup = result.read().strip().split(':')
        if len(dup) is not 2:
            print "cmd output format error!"
            sys.exit()

        file_op[dup[0]] = int(dup[1])
    return file_op

def test():
    cmd = "./clone_detect src/ > clone_code.result"
    os.system(cmd)
    test = get_duplicate('clone_code.result')
    expect = get_duplicate('expect.txt')

    if not test.has_key('totalDuplicate'):
        print "can't find totalDuplicate in cmd output"
        sys.exit()
    print 'PASS' if  test['totalDuplicate'] == expect['totalDuplicate'] else 'FAILED'


if __name__ == '__main__':
    test()
