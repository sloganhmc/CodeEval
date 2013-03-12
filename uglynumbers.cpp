/*
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
*/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include<fstream>
#include <sstream>
#include <inttypes.h>

using namespace std;

void create_operations_array(vector<string> &opp_arr, int num_items);
void ugly_number_checker(string input_str);
int64_t get_number_operations(string in_str, string oper, int in_str_len);
void Tokenize(const string& str,vector<string>& tokens,const string& delimiters );
bool is_ugly_num(int int64_t);

//parse a string into tokens based on specified delimeters
void Tokenize(const string& str,vector<string>& tokens,const string& delimiters = " ") {
	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);

	// Find first "non-delimiter".
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos){
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));

		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);

		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}

//function that creates a string array of  possible operations to execute on input number
void create_operations_array(vector<string> &opp_arr, int num_items){
	int opp_arr_size;
	string curr_word, oper_str;
	vector<string> old_opp_arr;
	
	oper_str = "+- ";
	opp_arr.clear();
	for(int i=0; i<3; i++){
		string single_char(1,oper_str[i]);
		opp_arr.push_back(single_char);
	}
	
	//do crossing num_items - 1 times
	for(int i=1; i<num_items; i++){
		//copy opp_arr to old_opp_arr
		opp_arr_size = opp_arr.size();
		old_opp_arr.resize(opp_arr_size);
		for(int j=0;j<opp_arr_size; j++)
			old_opp_arr[j] = opp_arr[j];
		
		//clear opp_arr
		opp_arr.clear();
		for(int str_idx=0; str_idx<3;str_idx++){
			string curr_char(1,oper_str[str_idx]);
			for(int item_idx=0; item_idx<opp_arr_size; item_idx++){
				curr_word = old_opp_arr[item_idx];
				opp_arr.push_back(curr_char+curr_word);
			}
		}
	}
}

//given a number and corresponding operations generate final number
int64_t get_number_operations(string in_str, string oper, int in_str_len){
	int64_t value, temp_int;
	int len_num_arr;
	char last_op;
	string temp_val;
	vector<int> num_arr;
	vector<char> oper_string;
	
	last_op = ' ';
	value = 0;
	temp_val = "";
	for(int i=0;i<in_str_len;i++){
		temp_val += in_str[i];
		if(i != in_str_len-1){
			if(oper[i] != ' '){
				temp_int = strtoll(temp_val.c_str(),NULL,10);
				//temp_int = int64_t(atol(temp_val.c_str()));
				if(last_op == '+')
					value += temp_int;
				else if(last_op == '-')
					value = value - temp_int;
				else
					value = temp_int;
				temp_val = "";
				last_op = oper[i];
			}
		}
	}
	
	temp_int = strtoll(temp_val.c_str(),NULL,10);
	//temp_int = int64_t(atol(temp_val.c_str()));
	if(last_op == '+')
		value += temp_int;
	else if(last_op == '-')
		value = value - temp_int;
	else
		value = temp_int;
	return(llabs(value));
}

//check to see if an number is ugly or not. Returns true if ugly, false if not
bool is_ugly_num(int64_t in_num){
    if(in_num%2 == 0) 
        return true;
    else if(in_num%3 == 0)
        return true;
    else if(in_num%5 == 0)
        return true;
    else if(in_num%7 == 0)
        return true;
    else if(in_num == 0)
        return true;
    else
        return false;	
}

/*
1)First generate all possible combinations for number
2)Second for each generate number checks to see if it is ugly or not.
*/
void ugly_number_checker(string input_str){
	int len_input_str, len_operations_array, count;
	vector<string> operations_array;
	
	len_input_str = input_str.length();
	count = 0;
	
	//if string has multiple  characters then generate and evaluate all numbers
	if(len_input_str > 1){
		create_operations_array(operations_array, len_input_str-1);
		len_operations_array =  operations_array.size();
		for (int i=0; i<len_operations_array; i++){
			if(is_ugly_num(get_number_operations(input_str, operations_array[i], len_input_str))){
				count++;
			}
		}
		cout << count << endl;
	}
	
	//otherwise string is basically a number check that number
	else{
		if(is_ugly_num(int64_t(atol(input_str.c_str()))))
			cout << 1 << endl;
		else
			cout << 0 << endl;
	}
}

int 
main(int argc, char* argv[]){

	vector<string> tokens;
	ifstream file;
	string lineBuffer;
	
	file.open(argv[1]);

	while (!file.eof()){
		getline(file, lineBuffer);
		if (lineBuffer.length() == 0)
			continue; //ignore all empty lines
		else{
			tokens.clear();
			Tokenize(lineBuffer, tokens, "\r\n");
			if(tokens.size()){
				ugly_number_checker(tokens[0]);
			}
		}
	}
	return(0);
}