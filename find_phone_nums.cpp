/*
Author: Sheldon Logan
Telephone Words(Uses a iterative algorithm)

Description:

Given a 7 digit telephone number, print out all the possible sequences of letters that can represent the given telephone number. Note that in a standard 12 key pad, 0 and 1 do not have any letters associated with them. They are to be treated as such, i.e. a 0/1 in the telephone number will be retained in the final word as well. You may use the following mapping between numbers and characters:

0 => 0
1 => 1
2 => abc
3 => def
4 => ghi
5 => jkl
6 => mno
7 => pqrs
8 => tuv
9 => wxyz
Input sample:

Your program should accept as its first argument a path to a filename.The input file contains 7 digit telephone numbers, one per line.

4155230
Output sample:

Print out the words that can produce the telephone number, alphabetically sorted and comma delimited. eg.

g1jjad0,g1jjae0,g1jjaf0,g1jjbd0,g1jjbe0,g1jjbf0,g1jjcd0,g1jjce0,g1jjcf0,g1jkad0,g1jkae0,g1jkaf0,g1jkbd0,g1jkbe0,g1jkbf0,g1jkcd0,g1jkce0,g1jkcf0,g1jlad0,g1jlae0,g1jlaf0,g1jlbd0,g1jlbe0,g1jlbf0,g1jlcd0,g1jlce0,g1jlcf0,g1kjad0,g1kjae0,g1kjaf0,g1kjbd0,g1kjbe0,g1kjbf0,g1kjcd0,g1kjce0,g1kjcf0,g1kkad0,g1kkae0,g1kkaf0,g1kkbd0,g1kkbe0,g1kkbf0,g1kkcd0,g1kkce0,g1kkcf0,g1klad0,g1klae0,g1klaf0,g1klbd0,g1klbe0,g1klbf0,g1klcd0,g1klce0,g1klcf0,g1ljad0,g1ljae0,g1ljaf0,g1ljbd0,g1ljbe0,g1ljbf0,g1ljcd0,g1ljce0,g1ljcf0,g1lkad0,g1lkae0,g1lkaf0,g1lkbd0,g1lkbe0,g1lkbf0,g1lkcd0,g1lkce0,g1lkcf0,g1llad0,g1llae0,g1llaf0,g1llbd0,g1llbe0,g1llbf0,g1llcd0,g1llce0,g1llcf0,h1jjad0,h1jjae0,h1jjaf0,h1jjbd0,h1jjbe0,h1jjbf0,h1jjcd0,h1jjce0,h1jjcf0,h1jkad0,h1jkae0,h1jkaf0,h1jkbd0,h1jkbe0,h1jkbf0,h1jkcd0,h1jkce0,h1jkcf0,h1jlad0,h1jlae0,h1jlaf0,h1jlbd0,h1jlbe0,h1jlbf0,h1jlcd0,h1jlce0,h1jlcf0,h1kjad0,h1kjae0,h1kjaf0,h1kjbd0,h1kjbe0,h1kjbf0,h1kjcd0,h1kjce0,h1kjcf0,h1kkad0,h1kkae0,h1kkaf0,h1kkbd0,h1kkbe0,h1kkbf0,h1kkcd0,h1kkce0,h1kkcf0,h1klad0,h1klae0,h1klaf0,h1klbd0,h1klbe0,h1klbf0,h1klcd0,h1klce0,h1klcf0,h1ljad0,h1ljae0,h1ljaf0,h1ljbd0,h1ljbe0,h1ljbf0,h1ljcd0,h1ljce0,h1ljcf0,h1lkad0,h1lkae0,h1lkaf0,h1lkbd0,h1lkbe0,h1lkbf0,h1lkcd0,h1lkce0,h1lkcf0,h1llad0,h1llae0,h1llaf0,h1llbd0,h1llbe0,h1llbf0,h1llcd0,h1llce0,h1llcf0,i1jjad0,i1jjae0,i1jjaf0,i1jjbd0,i1jjbe0,i1jjbf0,i1jjcd0,i1jjce0,i1jjcf0,i1jkad0,i1jkae0,i1jkaf0,i1jkbd0,i1jkbe0,i1jkbf0,i1jkcd0,i1jkce0,i1jkcf0,i1jlad0,i1jlae0,i1jlaf0,i1jlbd0,i1jlbe0,i1jlbf0,i1jlcd0,i1jlce0,i1jlcf0,i1kjad0,i1kjae0,i1kjaf0,i1kjbd0,i1kjbe0,i1kjbf0,i1kjcd0,i1kjce0,i1kjcf0,i1kkad0,i1kkae0,i1kkaf0,i1kkbd0,i1kkbe0,i1kkbf0,i1kkcd0,i1kkce0,i1kkcf0,i1klad0,i1klae0,i1klaf0,i1klbd0,i1klbe0,i1klbf0,i1klcd0,i1klce0,i1klcf0,i1ljad0,i1ljae0,i1ljaf0,i1ljbd0,i1ljbe0,i1ljbf0,i1ljcd0,i1ljce0,i1ljcf0,i1lkad0,i1lkae0,i1lkaf0,i1lkbd0,i1lkbe0,i1lkbf0,i1lkcd0,i1lkce0,i1lkcf0,i1llad0,i1llae0,i1llaf0,i1llbd0,i1llbe0,i1llbf0,i1llcd0,i1llce0,i1llcf0

*/

#include <iostream>
#include <stdlib.h>
#include <vector>
#include<algorithm>
#include <string>
#include<fstream>

using namespace std;

string get_num_letters(char num);
void make_phone_words(string phone_num, vector<string> &str_buf);
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

string get_num_letters(char num){
	switch(num){
		case '0':
			return(string(1,'0'));
			break;
		case '1':
			return(string(1,'1'));
			break;
		case '2':
			return("abc");
			break;
		case '3':
			return("def");
			break;
		case '4':
			return("ghi");
			break;
		case '5':
			return("jkl");
			break;
		case '6':
			return("mno");
			break;
		case '7':
			return("pqrs");
			break;
		case '8':
			return("tuv");
			break;
		case '9':
			return("wxyz");
			break;
		default:
			cout << "invalid number" <<endl;
			exit(-1);
	}
}

void make_phone_words(string phone_num, vector<string> &str_buf){
	int str_len, num_idx, num_letters_len, str_buf_size;
	string num_letters,new_word;
	vector<string> old_str_buf;
	
	str_len = phone_num.length();
	for(num_idx = str_len-1;num_idx>=0;num_idx--){
		num_letters = get_num_letters(phone_num[num_idx]);
		num_letters_len = num_letters.length();
		str_buf_size = str_buf.size();
		
		if(str_buf_size == 0){
			for (int i=0;i<num_letters_len;i++)
				str_buf.push_back(string(1,num_letters[i]));
		}
		else{
			old_str_buf.resize(str_buf_size);
			for(int item_idx=0; item_idx<str_buf_size; item_idx++)
				old_str_buf[item_idx] = str_buf[item_idx];
			
			str_buf.clear();
			
			for (int i=0;i<num_letters_len;i++){
				for(int j=0;j<str_buf_size;j++){
					new_word = string(1,num_letters[i])+old_str_buf[j];
					str_buf.push_back(new_word);
				}
			}
		}
	}
}

int 
main(int argc, char* argv[]){

	vector<string> tokens, str_buffer;
	ifstream file;
	string lineBuffer, phone_num;

	file.open(argv[1]);

	while (!file.eof()){
		getline(file, lineBuffer);
		if (lineBuffer.length() == 0)
			continue; //ignore all empty lines
		else{
			tokens.clear();
			Tokenize(lineBuffer, tokens, "\r\n");
			if(tokens.size()){
				phone_num = tokens[0];
				str_buffer.clear();
				make_phone_words(phone_num, str_buffer);
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
