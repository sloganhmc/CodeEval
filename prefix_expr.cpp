/*
Author: Sheldon Logan

Prefix Expressions
Description:

You are given a prefix expression. Write a program to evaluate it.
Input sample:

The first argument will be an input file with one prefix expression per line. e.g.

* + 2 3 4
Your program has to read this and insert it into any data structure you like. Traverse that data structure and evaluate the prefix expression. Each token is delimited by a whitespace. You may assume that the only valid operators appearing in test data are '+','*' and '/' 

Output sample:

Print to stdout, the output of the prefix expression, one per line. e.g.

20

*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

void Tokenize(const string& str,vector<string>& tokens,const string& delimiters );
int do_operator_operation(string oper, int num1, int num2);
bool check_is_operator(string in_str);
void eval_prefix_expr(vector<string> &input_expr);

int do_operator_operation(string oper, int num1, int num2){
	if(oper == "*")
		return(num1*num2);
	else if(oper == "/")
		return(num1/num2);
	else if(oper == "+")
		return(num1+num2);
	else if(oper == "-")
		return(num1-num2);
	else{
		cout << "Incorrect operator" << endl;
		exit(1);
	}
}

bool check_is_operator(string in_str){
	if(in_str == "*")
		return(true);
	else if(in_str == "/")
		return(true);
	else if(in_str == "+")
		return(true);
	else if(in_str == "-")
		return(true);
	return(false);
}

void eval_prefix_expr(vector<string>& input_expr){
	int len_input_expr, num1, num2;
	vector<int> pseudo_stack;
	
	len_input_expr = input_expr.size();
	for(int i = len_input_expr-1;i>=0; i--){
		if(check_is_operator(input_expr[i]) && (pseudo_stack.size() <2)){
			cout << "Error not enough operands for calculation" << endl;
			exit(1);
		}
		else if(check_is_operator(input_expr[i])){
			num1 = pseudo_stack.back();
			pseudo_stack.pop_back();
			num2 = pseudo_stack.back();
			pseudo_stack.pop_back();
			pseudo_stack.push_back(do_operator_operation(input_expr[i], num1, num2));
		}
		else{
			pseudo_stack.push_back(atoi(input_expr[i].c_str()));	
		}
	}
	cout << pseudo_stack[0] << endl;
}

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

int main(int argc, char* argv[] ){
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
			Tokenize(lineBuffer, tokens, "\r\n ");
			if(tokens.size()){
				eval_prefix_expr(tokens);
			}
		}
	}
}