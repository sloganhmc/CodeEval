'''
Author: Sheldon Logan

Climbing stairs(iterative)
Description:

You are climbing a stair case. It takes n steps to reach to the top. Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Input sample:

Your program should accept as its first argument a path to a filename. Each line in this file contains a positive integer which is the total number of stairs. e.g.

10
20
Output sample:

Print out the number of ways to climb to the top of the staircase. e.g.

89
10946

'''

import sys
import math

def count_stairs(N):
    max_num_twos = int(N/2)
    count = 0
    for num_twos in range(0,max_num_twos+1):
        num_ones = N-(2*num_twos)
        count+= math.factorial(num_ones+num_twos)/(math.factorial(num_ones)*math.factorial(num_twos))
    print(int(count))

testcase = open(sys.argv[1],'r')
for test in testcase:
    if(test.strip()):
        count_stairs(int(test.strip()))
testcase.close()
