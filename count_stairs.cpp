/*
Author: Sheldon Logan
Climbing Stairs (uses a recursive algorithm)
Description:

You are climbing a stair case. It takes n steps to reach to the top. Each time you can 
either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Input sample:

Your program should accept as its first argument a path to a filename. Each line in 
this file contains a positive integer which is the total number of stairs. e.g.

10
20
Output sample:

Print out the number of ways to climb to the top of the staircase. e.g.

89
10946

*/
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>

using namespace std;

void Tokenize(const string& str,vector<string>& tokens,const string& delimiters );
int count_num_stairs(int N);

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

int count_num_stairs(int N){
	if(N == 1)
		return(1);
	else if(N == 2)
		return(2);
	else 
		return(count_num_stairs(N-1)+count_num_stairs(N-2));
}

int 
main(int argc, char* argv[]){

	vector<string> tokens;
	ifstream file;
	string lineBuffer;
	int num_stairs, result;

	file.open(argv[1]);

	while (!file.eof()){
		getline(file, lineBuffer);
		if (lineBuffer.length() == 0)
			continue; //ignore all empty lines
		else{
			tokens.clear();
			Tokenize(lineBuffer, tokens, "\r\n");
			if(tokens.size()){
				string input_val = tokens[0];
				num_stairs = atoi(input_val.c_str());
				result = count_num_stairs(num_stairs);
				cout << result << endl;
			}
		}
	}
	return(0);
}