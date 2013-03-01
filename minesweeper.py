'''
Author: Sheldon Logan
Minesweeper

Description:

You will be given an M*N matrix. Each item in this matrix is either a '*' or a '.'. A '*' indicates a mine whereas a '.' does not. The objective of the challenge is to output a M*N matrix where each element contains a number (except the positions which actually contain a mine which will remain as '*') which indicates the number of mines adjacent to it. Notice that each position has at most 8 adjacent positions e.g. left, top left, top, top right, right, ...

Input sample:

Your program should accept as its first argument a path to a filename. Each line in this file contains M,N, a semicolon and the M*N matrix in row major form. e.g.

3,5;**.........*...
4,4;*........*......
Output sample:

Print out the new M*N matrix (in row major form) with each position(except the ones with the mines) indicating how many adjacent mines are there. e.g.

**100332001*100
*10022101*101110
'''

import sys

def convert_mat_idx_to_vec_idx(row_idx, col_idx, num_cols):
    return((row_idx*num_cols)+col_idx)

def count_mines(row_idx, col_idx, num_cols, num_rows, mine_array):
    count = 0;
    #up left
    if(row_idx>0 and col_idx>0):
        if(mine_array[convert_mat_idx_to_vec_idx(row_idx-1, col_idx-1, num_cols)] == "*"):
            count+=1
        
    #up
    if(row_idx>0):
        if(mine_array[convert_mat_idx_to_vec_idx(row_idx-1, col_idx, num_cols)] == "*"):
            count+=1
            
    #up right
    if(row_idx>0 and col_idx<(num_cols-1)):
        if(mine_array[convert_mat_idx_to_vec_idx(row_idx-1, col_idx+1, num_cols)] == "*"):
            count+=1
        
    #right
    if(col_idx<(num_cols-1)):
        if(mine_array[convert_mat_idx_to_vec_idx(row_idx, col_idx+1, num_cols)] == "*"):
            count+=1
    
    #down right
    if(row_idx<(num_rows-1) and col_idx<(num_cols-1)):
        if(mine_array[convert_mat_idx_to_vec_idx(row_idx+1, col_idx+1, num_cols)] == "*"):
            count+=1
       
    #down
    if(row_idx<(num_rows-1)):
        if(mine_array[convert_mat_idx_to_vec_idx(row_idx+1, col_idx, num_cols)] == "*"):
            count+=1
    #down left
    if(row_idx<(num_rows-1) and col_idx>0):
        if(mine_array[convert_mat_idx_to_vec_idx(row_idx+1, col_idx-1, num_cols)] == "*"):
            count+=1
    
    #left
    if(col_idx>0):
        if(mine_array[convert_mat_idx_to_vec_idx(row_idx, col_idx-1, num_cols)] == "*"):
            count+=1

    return(str(count))

def minesweeper_cal(num_rows, num_cols, mine_array):
    result_arr = []
    for i in range(0,num_rows):
        row_arr = num_cols*[0]
        result_arr.append(row_arr)

    for row_idx in range(0,num_rows):
        for col_idx in range(0,num_cols):
            val = mine_array[convert_mat_idx_to_vec_idx(row_idx, col_idx, num_cols)];
            if(val == '*'):
                result_arr[row_idx][col_idx] = "*"
            else:
                result_arr[row_idx][col_idx] = count_mines(row_idx, col_idx, num_cols, num_rows, mine_array)

    result_str = ''
    for row in result_arr:
        for item in row:
            result_str += item

    print(result_str)   
    
testcase = open(sys.argv[1],'r')
for test in testcase:
    if(test.strip()):
        input_line = test.strip().split(";")
        n_rows = int(input_line[0].split(",")[0])
        n_cols = int(input_line[0].split(",")[1])
        m_array = input_line[1]
        minesweeper_cal(n_rows,n_cols, m_array)
testcase.close()
