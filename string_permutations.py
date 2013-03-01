'''
Author: Sheldon Logan

String Permutator
String Permutations  Share on LinkedIn

Description:

Write a program to print out all the permutations of a string in alphabetical order.

Input sample:

The first argument will be a text file containing an input string, one per line. e.g. 

hat
Output sample:

Print to stdout, permutations of the string, comma separated, in alphabetical order.
e.g.

aht,ath,hat,hta,tah,tha
'''


import sys

def string_permutator(input_str):
        str_len = len(input_str)
        str_buf = []

        for num_cross in range(0,str_len):
                if not str_buf:
                        for char in input_str:
                                str_buf.append(char)
                        print(str_buf)
                else:
                        old_str_buf = str_buf
                        str_buf = []
                        for char in input_str:
                                for word in old_str_buf:
                                        if not char in word:
                                                new_word = word+char
                                                str_buf.append(new_word)
                        print(str_buf)

        str_buf.sort();
        final_str = ""
        for string in str_buf:
                if(final_str):
                        final_str = final_str + ',' + string
                else:
                        final_str = string
        print(final_str)

test_cases = open(sys.argv[1],'r')
for test in test_cases:
        if(test):
                string_permutator(test.strip())
test_cases.close()

