/*
Author: Sheldon Logan

String Permutations (Uses an iterative formula)
Description:

Write a program to print out all the permutations of a string in alphabetical order.

Input sample:

The first argument will be a text file containing an input string, one per line. e.g. 

hat
Output sample:

Print to stdout, permutations of the string, comma separated, in alphabetical order.
e.g.

aht,ath,hat,hta,tah,tha

*/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include<algorithm>
#include <string>
#include<fstream>

using namespace std;

void string_permute(string input_str, vector<string> &str_buf);
bool is_not_in_word(char input_char, string input_str);
void Tokenize(const string& str,vector<string>& tokens,const string& delimiters );

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

void string_permute(string input_str, vector<string> &str_buf){
	int str_len = input_str.length();
	int str_buf_size;
	char curr_carr;
	string curr_word;
	
	vector<string> old_str_buf;
	
	for(int i=0; i<str_len; i++){
		string single_char(1,input_str[i]);
		str_buf.push_back(single_char);
	}
	
	//do crossing str_len - 1 times
	for(int i=1; i<str_len; i++){
		
		//copy str_buf to old str buf
		str_buf_size = str_buf.size();
		old_str_buf.resize(str_buf_size);
		for(int j=0;j<str_buf_size; j++)
			old_str_buf[j] = str_buf[j];
	
		//clear str_buf
		str_buf.clear();
		
		for(int str_idx=0; str_idx<str_len;str_idx++){
			curr_carr = input_str[str_idx];
			string curr_char(1,input_str[str_idx]);
			
			for(int item_idx=0; item_idx<str_buf_size; item_idx++){
				curr_word = old_str_buf[item_idx];
				
				if(is_not_in_word(curr_carr, curr_word)){
					str_buf.push_back(curr_char+curr_word);
				}
			}
		}
	}
}

bool is_not_in_word(char input_char, string input_str){
	int str_len = input_str.length();
	
	for(int i=0; i<str_len; i++){
		if(input_char == input_str[i])
			return false;
	}
	return true;
	
}

int 
main(int argc, char* argv[]){

	vector<string> tokens, str_buffer;
	ifstream file;
	string lineBuffer, str_to_permute;

	file.open(argv[1]);

	while (!file.eof()){
		getline(file, lineBuffer);
		if (lineBuffer.length() == 0)
			continue; //ignore all empty lines
		else{
			tokens.clear();
			Tokenize(lineBuffer, tokens, "\r\n");
			if(tokens.size()){
				str_to_permute = tokens[0];
				str_buffer.clear();
				string_permute(str_to_permute, str_buffer);
				sort (str_buffer.begin(), str_buffer.end());
				for(int i=0; i<str_buffer.size();i++){
					if(i==0)
						cout << str_buffer[i] ;
					else
						cout << "," << str_buffer[i] ;
				}
				cout << endl;
			}
		}
	}
	return(0);
}



