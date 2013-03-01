'''
Author: Sheldon Logan

Spiral Printing

Description:

Write a program to print a 2D array (n x m) in spiral order (clockwise)

Input sample:

Your program should accept as its first argument a path to a filename.The input file contains several lines.
Each line is one test case. Each line contains three items (semicolon delimited).
The first is 'n'(rows), the second is 'm'(columns) and the third is a single space separated list of characters/numbers
in row major order. eg.

3;3;1 2 3 4 5 6 7 8 9
Output sample:

Print out the matrix in clockwise fashion, one per line, space delimited. eg.

1 2 3 6 9 8 7 4 5
Submit your solution in a file (some file name).(py| c| cpp| rb| pl| php| tcl| clj| js| scala| cs| m) | spiral_printing.java|spiral_printing.scala or use the online editor.
'''
import sys

def convert_mat_idx_to_vec_idx(row_idx, col_idx, num_cols):
    return((row_idx*num_cols)+col_idx)
    

def spiral_print(num_rows, num_cols, matrix_array):
    xidx = 0;
    yidx = 0;


    #how far to print in each direction
    min_x = 0
    min_y = 0
    max_x = num_cols
    max_y = num_rows

    result_str = ""
    
    #while you still have to print
    while(True):    
        #print left#
        #first check that you can print left if not exit loop
        if(min_x >= max_x):
            break;
        
        for yidx in range(min_x,max_x):
            if(result_str):
                result_str = result_str + " " + matrix_array[convert_mat_idx_to_vec_idx(xidx,yidx,num_cols)]
            else:
                result_str = matrix_array[convert_mat_idx_to_vec_idx(xidx,yidx,num_cols)]
                    
            
        #add 1 to min_y since highest row has been printed
        min_y += 1
        
        #print down#
        #first check tht you can print down if not exit loop
        if(min_y >= max_y):
            break;
        
        for xidx in range(min_y,max_y):
            if(result_str):
                result_str = result_str + " " + matrix_array[convert_mat_idx_to_vec_idx(xidx,yidx,num_cols)]
            else:
                result_str = matrix_array[convert_mat_idx_to_vec_idx(xidx,yidx,num_cols)]

        #subtract 1 from max_x since farthest column has been printed
        max_x -= 1
                
        #print right#
        #first check that you can print left
        if(min_x >= max_x):
            break;

        for yidx in reversed(range(min_x,max_x)):
            result_str = result_str + " " + matrix_array[convert_mat_idx_to_vec_idx(xidx,yidx,num_cols)]

        #subtract 1 from max_y since lowest column has been printed
        max_y -= 1
        
        #print up#
        #first check that you can print up
        if(min_y >= max_y):
            break;

        for xidx in reversed(range(min_y,max_y)):
            result_str = result_str + " " + matrix_array[convert_mat_idx_to_vec_idx(xidx,yidx,num_cols)]

        #add 1 to min_x since hearest row has been printed
        min_x += 1
        
    print(result_str)

testcases = open(sys.argv[1],'r')
for test in testcases:
        if(test.strip()):
            input_line = test.split(';')  
            num_rows = int(input_line[0])
            num_cols = int(input_line[1])
            vector = (input_line[2].strip()).split()
            spiral_print(num_rows, num_cols, vector)
testcases.close()     

