'''
Author: Sheldon Logan

Prefix Expressions
Description:

You are given a prefix expression. Write a program to evaluate it.
Input sample:

The first argument will be an input file with one prefix expression per line. e.g.

* + 2 3 4
Your program has to read this and insert it into any data structure you like.
Traverse that data structure and evaluate the prefix expression. Each token is
delimited by a whitespace. You may assume that the only valid operators appearing
in test data are '+','*' and '/' 

Output sample:

Print to stdout, the output of the prefix expression, one per line. e.g.

20

'''

import sys

def do_operator_operation(operator, num1, num2):
    if(operator == '*'):
        return(num1*num2)
    elif(operator == '/'):
        return(int(num1/num2))
    elif(operator == '+'):
        return(num1+num2)
    elif(operator == '-'):
        return(num1-num2)
    else:
        print("Incorrect operator")
        sys.exit(1)

def check_is_operator(input_str):
    if(input_str == '*'):
        return(True)
    elif(input_str == '/'):
        return(True)
    elif(input_str == '+'):
        return(True)
    elif(input_str == '-'):
        return(True)
    return(False)

def eval_prefix_expr(input_expr):
    pseudo_stack = []
    for item in reversed(input_expr):
        if(check_is_operator(item) and (len(pseudo_stack) <2)):
            print("Error not enough operands for calculation")
            sys.exit(1)
        elif(check_is_operator(item)):
            num1 = pseudo_stack.pop()
            num2 = pseudo_stack.pop()
            val = do_operator_operation(item, num1, num2)
            pseudo_stack.append(val)
        else:
            pseudo_stack.append(int(item))
        
    print(pseudo_stack[0])
        
testcase = open(sys.argv[1],'r')
for test in testcase:
    if(test.strip()):
        prefix_expr = test.strip().split(" ")
        eval_prefix_expr(prefix_expr)
testcase.close()




