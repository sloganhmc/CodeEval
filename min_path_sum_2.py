'''
Author: Sheldon Logan

Minimum Path Sum
Description:

You are given an n*n matrix of integers. You can move only right and down. Calculate
the minimal path sum from the top left to the bottom right

Input sample:

Your program should accept as its first argument a path to a filename.
The first line will have the value of n(the size of the square matrix).
This will be followed by n rows of the matrix. (Integers in these rows will be
comma delimited). After the n rows, the pattern repeats. e.g.

2
4,6
2,8
3
1,2,3
4,5,6
7,8,9
Output sample:

Print out the minimum path sum for each matrix. e.g.

14
21

'''

import sys

"""
Calculates the minimum path sum using a table format. It navigates the matrix in a
right then down manner placing the minimum value to that point in a alternate array
"""
def find_min_sum(N,in_arr):
    min_count_array = []
    for idx in range(0,N):
        min_count_array.append(N*[0])

    for row_idx in range(0,N):
        for col_idx in range(0,N):
            #(0,0)
            if not row_idx and not col_idx:
                min_count_array[row_idx][col_idx] = int(in_arr[row_idx][col_idx])

            #all of first row
            elif not row_idx:
                min_count_array[row_idx][col_idx] = min_count_array[row_idx][col_idx-1] + int(in_arr[row_idx][col_idx])

            #second row and beyond    
            else:
                #if first column
                if not col_idx:
                    min_count_array[row_idx][col_idx] = min_count_array[row_idx-1][col_idx] + int(in_arr[row_idx][col_idx])
                else:
                    val_1 = min_count_array[row_idx][col_idx-1]
                    val_2 = min_count_array[row_idx-1][col_idx]
                    if(val_1 < val_2):
                        min_count_array[row_idx][col_idx] = val_1 + int(in_arr[row_idx][col_idx])
                    else:
                        min_count_array[row_idx][col_idx] = val_2 + int(in_arr[row_idx][col_idx])                 
                
    print(min_count_array[N-1][N-1])
        
testcase = open(sys.argv[1],'r')
parsed_first_matrix = False
N = ''
input_arr = []
for test in testcase:
    if(test.strip()):
        input_line = test.strip().split(',')
        if len(input_line) == 1:
            if parsed_first_matrix:
                find_min_sum(N,input_arr)
            N = int(input_line[0])
            del(input_arr[:])
        else:
            parsed_first_matrix = True
            input_arr.append(input_line)
            
find_min_sum(N,input_arr)
testcase.close()
