'''
Author: Sheldon Logan

Distinct Subsequences
Description:

A subsequence of a given sequence S consists of S with zero or more elements
deleted. Formally, a sequence Z = z1z2..zk is a subsequence of X = x1x2...xm,
if there exists a strictly increasing sequence <i1,i2...ik> of indicies of
X such that for all j=1,2,...k we have Xij = Zj. e.g. Z=bcdb is a subsequence
of X=abcbdab with corresponding index sequence <2,3,5,7>

Input sample:

Your program should accept as its first argument a path to a filename.
Each line in this file contains two comma separated strings. The first is
the sequence X and the second is the subsequence Z. e.g.

babgbag,bag
rabbbit,rabbit
Output sample:

Print out the number of distinct occurrences of Z in X as a subsequence e.g.

5
3
'''
import sys
import copy

#find positions of all characters within a string
def find_char_in_string(string,char):
    char_idx = []
    for idx,item in enumerate(string):
        if char == item:
            char_idx.append(idx)
    return(char_idx)

#find if number in an array is greater than previous digit in the array
def creater_than_last_digit(num_arr,new_num):
    last_num = num_arr[-1]
    if(last_num<new_num):
        return(True)
    else:
        return(False)
'''
count distinct subsequences in the array
Basically the algorithm builds the substr from the input str
and count the amount of times you can do it.
'''
def count_distinct_subseq(str1,sub_str):
    char_occurence_dict = {}
    for char in sub_str:
        char_occurence_dict[char] = find_char_in_string(str1,char)

    perm_array = []
    for char in sub_str:
        if not perm_array:
            for item in char_occurence_dict[char]:
                perm_array.append([item])
        else:
            old_perm_array = perm_array
            perm_array = []
            for word in old_perm_array:
                for item in char_occurence_dict[char]:
                    if(creater_than_last_digit(word,item)):
                        new_arr = copy.deepcopy(word)
                        new_arr.append(item)
                        perm_array.append(new_arr)
                
    print(len(perm_array))

testcase = open(sys.argv[1],'r')
for test in testcase:
    if(test.strip()):
        input_line = test.strip().split(",")
        count_distinct_subseq(input_line[0],input_line[1])
testcase.close()


