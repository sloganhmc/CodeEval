'''
Author: Sheldon Logan

Repeated SubString
Description:

You are to find the longest repeated substring in a given text.
Repeated substrings may not overlap. If more than one substring is
repeated with the same length, print the first one you find.(starting
from the beginning of the text). NOTE: The substrings can't be all spaces

Input sample:

Your program should accept as its first argument a path to a filename.
The input file contains several lines. Each line is one test case. Each line
contains a test string. eg.

banana
Output sample:

For each set of input produce a single line of output which is the longest
repeated substring. If there is none, print out the string NONE. eg.

an
'''

import sys

#check to see if string is spaces
def is_string_spaces(input_str):
    for char in input_str:
        if char != " ":
            return(False)
    return(True)

#create substrings of a given length
def create_substr(input_str, sub_len):
    len_str = len(input_str)
    num_runs = len_str - sub_len
    sub_str_arr = []
    for idx in range(0,num_runs):
        sub_str = input_str[idx:idx+sub_len]
        sub_str_arr.append(sub_str)
    return(sub_str_arr)
    
#count substrings within a string
def count_sub_str(input_str, sub_str):
    len_str = len(input_str)
    len_sub_str = len(sub_str)
    count = 0
    
    str_idx = 0
    for idx in range(0,len_str):
        if(str_idx>len_str):
            break
        if(input_str[str_idx:str_idx+len_sub_str] == sub_str):
            count+= 1
            str_idx = str_idx+len_sub_str
        else:
            str_idx += 1
    return(count)

#Main function to find the repeated substring
def find_rep_substr(input_str):
    len_str = len(input_str)
    max_len = int(len_str/2)
    max_sub_str = ""
    
    for len_sub_str in range(1,max_len+1):
        sub_strs = create_substr(input_str, len_sub_str)
        for item in sub_strs:
            tmp_count = count_sub_str(input_str,item)
            if(tmp_count>1):
                max_sub_str = item
                break
            
    if not is_string_spaces(max_sub_str):
        print(max_sub_str)
    else:
        print("NONE")

testcase = open(sys.argv[1],'r')
for test in testcase:
    if(test.strip()):
        find_rep_substr(test.strip())
testcase.close()

