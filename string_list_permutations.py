'''
Author: Sheldon Logan

Description:

Credits: Challenge contributed by Max Demian.

You are given a number N and a string S. Print all of the possible ways to
write a string of length N from the characters in string S, comma delimited
in alphabetical order.

Input sample:

The first argument will be the path to the input filename containing the
test data. Each line in this file is a separate test case. Each line is
in the format: N,S i.e. a positive integer, followed by a string
(comma separated) eg.

1,aa
2,ab
3,pop
Output sample:

Print all of the possible ways to write a string of length N from the
characters in string S comma delimited in alphabetical order, with no
duplicates. eg.

a
aa,ab,ba,bb
ooo,oop,opo,opp,poo,pop,ppo,ppp
'''

import sys

def string_list(input_str,len_out_str):
    #create unique list of characters in string
    unique_chars = list(set(input_str))
    str_buf = []
    
    #do string permutaions and allow repeats
    for num_cross in range(0,len_out_str):
            if not str_buf:
                    for char in unique_chars:
                            str_buf.append(char)
            else:
                    old_str_buf = str_buf
                    str_buf = []
                    for char in unique_chars:
                            for word in old_str_buf:
                                    new_word = word+char
                                    str_buf.append(new_word)
    str_buf.sort()
    result_str = ""
    for word in str_buf:
        if(result_str):
            result_str += "," + word
        else:
            result_str = word
    print(result_str)


testcase = open(sys.argv[1],'r')
for test in testcase:
    if(test.strip()):
        input_line = test.strip().split(",")
        string_list(input_line[1],int(input_line[0]))
testcase.close()
