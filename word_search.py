'''
Author: Sheldon Logan

Word Search
Description:

Given a 2D board and a word, find if the word exists in the grid.
The word can be constructed from letters of sequentially adjacent
cell, where adjacent cells are those horizontally or vertically
neighboring. The same letter cell may not be used more than once.

Input sample:

The board to be used may be hard coded as:

[
[ABCE],
[SFCS],
[ADEE]
]
Your program should accept as its first argument a path to a filename.
Each line in this file contains a word. e.g.
ASADB
ABCCED
Output sample:

Print out True if the word exists in the board, False otherwise. e.g.

False
True

'''
import sys

#find the start positions for each character in grid
def create_dict_start_pos(in_dic):
    dict_pos = {}
    for r_idx,row in enumerate(in_dic):
        for c_idx,val in enumerate(row):
            if val in dict_pos:
                dict_pos[val].append([(r_idx,c_idx)])
            else:
                dict_pos[val] = [[(r_idx,c_idx)]]

    return(dict_pos)

#find neighbourhood positions of char specified 
def find_letter_close_by(in_dic, row_idx, col_idx, in_char, pos_of_letters):
    num_rows = 3;
    num_cols = 4;
    results_arr = []

    used_char_arr = create_let_used_arr();
    for item in pos_of_letters:
        used_char_arr[item[0]][item[1]] = 1

    #check left
    if(col_idx>0):
        if(in_dic[row_idx][col_idx-1] == in_char and used_char_arr[row_idx][col_idx-1] == 0):
            results_arr.append((row_idx,col_idx-1))
            
    #check right
    if(col_idx<num_cols-1):
        if(in_dic[row_idx][col_idx+1] == in_char and used_char_arr[row_idx][col_idx+1] == 0):
            results_arr.append((row_idx,col_idx+1))
            
    #check down
    if(row_idx<num_rows-1):
        if(in_dic[row_idx+1][col_idx] == in_char and used_char_arr[row_idx+1][col_idx] == 0):
            results_arr.append((row_idx+1,col_idx))
            
    #check up
    if(row_idx>0):
        if(in_dic[row_idx-1][col_idx] == in_char and used_char_arr[row_idx-1][col_idx] == 0):
            results_arr.append((row_idx-1,col_idx))

    return(results_arr)

#create blank array of whether that character is used or not
def create_let_used_arr():
    #flag to know if letter is used already or not
    letter_already_used = 3*[0]
    for i in range(0,3):
        letter_already_used[i]=(4*[0])

    return(letter_already_used)

#find word in the grid
def is_word_in_grid(input_str):
    len_input_str = len(input_str)
    
    #hard coded word grid
    word_grid = [['A','B','C','E'],['S','F','C','S'],['A','D','E','E']]

    #start positions of all letters in grid
    start_pos_dict = create_dict_start_pos(word_grid);

    #algorithm essentially keeps a list of all possible methods to obtain a specific
    #seqeunce of characters...if no method then list will be empty
    search_arr = []
    for idx,char in enumerate(input_str):
        if(idx==0):
            search_arr = start_pos_dict[char]
        else:
            new_search_arr = []
            for item in search_arr:
                new_search = find_letter_close_by(word_grid, item[-1][0], item[-1][1], char, item);
                for nsrch in new_search:
                    new_search_arr.append(item+[nsrch])
            search_arr = new_search_arr

    if(search_arr):
        print('True')
    else:
        print('False')
    
testcases = open(sys.argv[1],'r')
for test in testcases:
        if(test.strip()):
            is_word_in_grid(test.strip())
testcases.close()    
