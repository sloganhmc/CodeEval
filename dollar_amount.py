'''
Author: Sheldon Logan

Text Dollar

Description:

Credits: This challenge has been authored by Terence Rudkin

You are given a positive integer number. This represents the sales made that day in your
department store. The payables department however, needs this printed out in english.
NOTE: The correct spelling of 40 is Forty. (NOT Fourty)

Input sample:

Your program should accept as its first argument a path to a filename.
The input file contains several lines. Each line is one test case.
Each line contains a positive integer. eg.

3
10
21
466
1234
Output sample:

For each set of input produce a single line of output which is the english textual
representation of that integer. The output should be unspaced and in Camelcase.
Always assume plural quantities. You can also assume that the
numbers are < 1000000000 (1 billion). In case of ambiguities eg. 2200 could be
TwoThousandTwoHundredDollars or TwentyTwoHundredDollars, always choose the representation
with the larger base i.e. TwoThousandTwoHundredDollars. For the examples shown above,
the answer would be:

ThreeDollars
TenDollars
TwentyOneDollars
FourHundredSixtySixDollars
OneThousandTwoHundredThirtyFourDollars
'''

import sys

#Figures the string to append based on the place value
def convert_place_to_str(place, top_mid_bot):
    if(place == 3):
        return('Hundred')
    elif(place == 1 and top_mid_bot == 1):
        return('Dollars')
    elif(place == 1 and top_mid_bot == 2):
        return('Thousand')
    elif(place == 1 and top_mid_bot == 3):
        return('Million')

#sum string array
def sum_array(in_arr):
    sum_val = 0;
    for item in in_arr:
        sum_val += int(item[0])
    if(sum_val >0):
        return(False)
    else:
        return(True)

#convert a number given the place to a string
def convert_num_place_to_str(num, place, pos):
    if not place == 2:
        if(num == '0' and place == 1):
            return(convert_place_to_str(place,pos))
        elif(num == '0' and place == 3):
            return('')
        elif(num == '1'):
            return('One'+convert_place_to_str(place,pos))
        elif(num == '2'):
            return('Two'+convert_place_to_str(place,pos))
        elif(num == '3'):
            return('Three'+convert_place_to_str(place,pos))
        elif(num == '4'):
            return('Four'+convert_place_to_str(place,pos))
        elif(num == '5'):
            return('Five'+convert_place_to_str(place,pos))
        elif(num == '6'):
            return('Six'+convert_place_to_str(place,pos))
        elif(num == '7'):
            return('Seven'+convert_place_to_str(place,pos))
        elif(num == '8'):
            return('Eight'+convert_place_to_str(place,pos))
        elif(num == '9'):
            return('Nine'+convert_place_to_str(place,pos))
        elif(num == '10'):
            return('Ten'+convert_place_to_str(place,pos))
        elif(num == '11'):
            return('Eleven'+convert_place_to_str(place,pos))
        elif(num == '12'):
            return('Twelve'+convert_place_to_str(place,pos))
        elif(num == '13'):
            return('Thirteen'+convert_place_to_str(place,pos))
        elif(num == '14'):
            return('Fourteen'+convert_place_to_str(place,pos))
        elif(num == '15'):
            return('Fifteen'+convert_place_to_str(place,pos))
        elif(num == '16'):
            return('Sixteen'+convert_place_to_str(place,pos))
        elif(num == '17'):
            return('Seventeen'+convert_place_to_str(place,pos))
        elif(num == '18'):
            return('Eighteen'+convert_place_to_str(place,pos))
        elif(num == '19'):
            return('Nineteen'+convert_place_to_str(place,pos))
    else:
        if(num == '0'):
            return('')
        elif(num == '2'):
            return('Twenty')
        elif(num == '3'):
            return('Thirty')
        elif(num == '4'):
            return('Forty')
        elif(num == '5'):
            return('Fifty')
        elif(num == '6'):
            return('Sixty')
        elif(num == '7'):
            return('Seventy')
        elif(num == '8'):
            return('Eighty')
        elif(num == '9'):
            return('Ninety')
'''
given an array with three strings e.g.['3','1','9'] it combines the last
two elements of the array if the second element is '1' hence the example
would become ['3','19']. This is done since the numbers betweeen 10-19 have
unique names vs the numbers between 20 - 99 which are a prefix + digit
'''
def create_arrays_for_parsing(in_arr):
    len_arr = len(in_arr)
    num_place_tuple_array = []
    
    for idx,char in enumerate(in_arr):
        if(idx == len_arr-2 and char == '1'):
            num_place_tuple_array.append((in_arr[idx]+in_arr[idx+1],1))
            break
        num_place_tuple_array.append((char,len_arr-idx))
        
    return(num_place_tuple_array)

#output the text dollar value of a number
def output_text_dollar(input_str):
    top_part = []
    middle_part = []
    bottom_part = []

    #break strings into 3 parts, top, middle and bottom
    count = 0;
    curr_part = 1;
    input_str = input_str[::-1]
    for idx,char in enumerate(input_str):
        if(curr_part == 1):
            bottom_part.append(char)
            count+=1;
            if(count == 3):
                curr_part +=1
                count = 0
        elif(curr_part == 2):
            middle_part.append(char)
            count+=1;
            if(count == 3):
                curr_part +=1
                count = 0
        elif(curr_part == 3):
            top_part.append(char)
            count+=1;
            if(count == 3):
                curr_part +=1
                count = 0
                
    #arrange strings in order for parsing          
    top_part = create_arrays_for_parsing(top_part[::-1])
    middle_part = create_arrays_for_parsing(middle_part[::-1])
    bottom_part = create_arrays_for_parsing(bottom_part[::-1])

    result_str = ''
    if not(sum_array(top_part)):
        for item in top_part:
            result_str +=  convert_num_place_to_str(item[0], item[1], 3)
            
    if not(sum_array(middle_part)):    
        for item in middle_part:
            result_str +=  convert_num_place_to_str(item[0], item[1], 2)
            
    if not(sum_array(bottom_part)):   
        for item in bottom_part:
            result_str +=  convert_num_place_to_str(item[0], item[1], 1)
            
    else:
        result_str += 'Dollars'
        
    print(result_str)

testcases = open(sys.argv[1],'r')
for test in testcases:
        if(test.strip()):
            output_text_dollar(test.strip())
testcases.close()    
