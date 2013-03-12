import sys

'''
Author: Sheldon Logan

Description:

Credits: This challenge has appeared in a google competition before.

Once upon a time in a strange situation, people called a number ugly if
it was divisible by any of the one-digit primes (2, 3, 5 or 7). Thus, 14 is
ugly, but 13 is fine. 39 is ugly, but 121 is not. Note that 0 is ugly. Also
note that negative numbers can also be ugly; -14 and -39 are examples of
such numbers.

One day on your free time, you are gazing at a string of digits, something
like:

123456
You are amused by how many possibilities there are if you are allowed
to insert plus or minus signs between the digits. For example you can make:
1 + 234 - 5 + 6 = 236
which is ugly. Or
123 + 4 - 56 = 71
which is not ugly.

It is easy to count the number of different ways you can play with the
digits: Between each two adjacent digits you may choose put a plus sign,
a minus sign, or nothing. Therefore, if you start with D digits there
are 3^(D-1) expressions you can make. Note that it is fine to have leading
zeros for a number. If the string is '01023', then '01023', '0+1-02+3'
and '01-023' are legal expressions.

Your task is simple: Among the 3^(D-1) expressions, count how many of
them evaluate to an ugly number.
Input sample:

Your program should accept as its first argument a path to a filename. Each
line in this file is one test case. Each test case will be a single line
containing a non-empty string of decimal digits. The string in each test
case will be non-empty and will contain only characters '0' through '9'. Each
string is no more than 13 characters long. eg.

1
9
011
12345
Output sample:

Print out the number of expressions that evaluate to an ugly number for
each test case, each one on a new line eg

0
1
6
64
'''

#create list of operations for input string, i.e. addition, substraction or join previous numbers
def create_operations_array(num_items):
    unique_chars = [' ','+','-']
    str_buf = []
    
    #string permute join, addition and subtraction to get all possible combinations.
    for num_cross in range(0,num_items):
        if not str_buf:
            str_buf = [char for char in unique_chars]
        else:
            old_str_buf = str_buf
            str_buf = [word+char for char in unique_chars for word in old_str_buf]
    return(str_buf)

#check to see if an number is ugly or not. Returns true if ugly, false if not
def is_ugly_num(in_num):    
    if in_num%2 == 0: 
        return True
    elif in_num%3 == 0:
        return True
    elif in_num%5 == 0:
        return True
    elif in_num%7 == 0:
        return True
    elif in_num == 0:
        return True
    else:
        return False

def get_number_operations(in_str, oper, in_str_len):
    num_val = ''
    value = 0
    
    #calculate number based on operations for input_string
    for idx,char in enumerate(in_str):
        num_val += char
        if not (idx == in_str_len-1):
            if not oper[idx] == ' ':
                value += int(num_val)
                num_val = oper[idx]

    value += int(num_val)
    return(value)

'''
main function
1)First generate all possible combinations for number
2)Second for each generate number checks to see if it is ugly or not.
'''
def ugly_num_checker(input_str):
    len_str = len(input_str)
    
    #if string has multiple entries then evaluate all numbers
    if(len_str > 1):
        opp_array = create_operations_array(len_str-1)
        count = [1 for opp in opp_array if(is_ugly_num(get_number_operations(input_str, opp, len_str)))];
        #values = [get_number_operations(input_str, opp, len_str) for opp in opp_array];
        #count = [1 for val in values if(is_ugly_num(val))]
        print(sum(count))
        
    #otherwise string is basically a number check that number
    else:
        if(is_ugly_num(int(input_str))):
            print(1)
        else:
            print(0)

testcases = open(sys.argv[1],'r')
for test in testcases:
    if(test.strip()):
        ugly_num_checker(test.strip())
testcases.close()

