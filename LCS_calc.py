'''
Author: Sheldon Logan
Longest common subsequence

Description:

You are given two sequences. Write a program to determine the longest common subsequence between the two strings(each string can have a maximum length of 50 characters). (NOTE: This subsequence need not be contiguous. The input file may contain empty lines, these need to be ignored.)
Input sample:

The first argument will be a file that contains two strings per line, semicolon delimited. You can assume that there is only one unique subsequence per test case. e.g.

XMJYAUZ;MZJAWXU
Output sample:

The longest common subsequence. Ensure that there are no trailing empty spaces on each line you print. e.g.

MJAU

'''

import sys

def BuidLCSTable(seq1,seq2):
    len_seq1 = len(seq1)
    len_seq2 = len(seq2)
    dyn_prog_table = []
    for row in range(len_seq2+1):
        dyn_prog_table.append([0]*(len_seq1+1))

    for row_idx in range(1,len_seq2+1):
        for col_idx in range(1,len_seq1+1):
            if(seq2[row_idx-1] == seq1[col_idx-1]):
                dyn_prog_table[row_idx][col_idx] = dyn_prog_table[row_idx-1][col_idx-1] + 1
            else:
                dyn_prog_table[row_idx][col_idx] = max([dyn_prog_table[row_idx][col_idx-1],dyn_prog_table[row_idx-1][col_idx]])

    return(dyn_prog_table)  
    
def BuildLCS(dyn_prog_table, seq1, seq2, row_idx, col_idx):
    if(row_idx == 0 or col_idx == 0):
        return ""
    elif seq1[col_idx-1] == seq2[row_idx-1]:
        return(BuildLCS(dyn_prog_table, seq1, seq2, row_idx-1, col_idx-1)+ seq1[col_idx-1])
    else:
        if(dyn_prog_table[row_idx][col_idx-1]>dyn_prog_table[row_idx-1][col_idx]):
            return(BuildLCS(dyn_prog_table, seq1, seq2, row_idx, col_idx-1))
        else:
            return(BuildLCS(dyn_prog_table, seq1, seq2, row_idx-1, col_idx))

def GetLCS(seq1,seq2):
    LCStable = BuidLCSTable(seq1,seq2);
    max_row_idx = len(seq2)
    max_col_idx = len(seq1)
    LCS = BuildLCS(LCStable, seq1, seq2, max_row_idx, max_col_idx)
    print(LCS)

testcases = open(sys.argv[1],'r')
for test in testcases:
        if(test.strip()):
            input_line = test.split(';')  
            seq1 = input_line[0]
            seq2 = input_line[1].strip()
            GetLCS(seq1,seq2)
testcases.close()     

    

