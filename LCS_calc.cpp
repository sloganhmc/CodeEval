/*
Author: Sheldon Logan

Longest Common Subsequence
Description:

You are given two sequences. Write a program to determine the longest common subsequence between the two strings(each string can have a maximum length of 50 characters). (NOTE: This subsequence need not be contiguous. The input file may contain empty lines, these need to be ignored.)
Input sample:

The first argument will be a file that contains two strings per line, semicolon delimited. You can assume that there is only one unique subsequence per test case. e.g.

XMJYAUZ;MZJAWXU
Output sample:

The longest common subsequence. Ensure that there are no trailing empty spaces on each line you print. e.g.

MJAU
*/

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<vector>
#include <algorithm>

using namespace std;

void Tokenize(const string& str,vector<string>& tokens,const string& delimiters );
void BuildLCSTable(int** LCStable, string seq1, string seq2) ;
void BuildLCS(int** LCStable, string seq1, string seq2, int row_idx, int col_idx, vector<char>& LCS_string);
void GetLCS(string seq1, string seq2);

void BuildLCSTable(int** LCStable, string seq1, string seq2) {
	int len_seq1, len_seq2;
	
	len_seq1= seq1.length();
	len_seq2= seq2.length();
	
	for(int row_idx=1;row_idx<(len_seq2+1);row_idx++){
		for(int col_idx=1;col_idx<(len_seq1+1);col_idx++){
			if(seq2[row_idx-1] == seq1[col_idx-1])
				LCStable[row_idx][col_idx] = LCStable[row_idx-1][col_idx-1] + 1;
			else
				LCStable[row_idx][col_idx] = max(LCStable[row_idx][col_idx-1],LCStable[row_idx-1][col_idx]);
		}
	}
}

void GetLCS(string seq1, string seq2){
	int max_row_idx, max_col_idx;
	int** LCS_table;
	vector<char> LCS_val;
	
	max_row_idx = seq2.length();
	max_col_idx = seq1.length();
	
	//allocate memeory for LCS table
	//extra column and row for dynamic programming table
	LCS_table = new(nothrow) int*[max_row_idx+1];
	if(LCS_table==0){
		cout << "Error allocating memory for LCS table(2D array)" << endl;
		exit(1);
	}
	for(int i=0;i<(max_row_idx+1);i++){
		LCS_table[i] = new(nothrow) int[max_col_idx+1];
		if(LCS_table[i]==0){
			cout << "Error allocating memory for LCS table single row" << endl;
			exit(1);
		}
	}
	
	//initalize LCS table to zero
	for(int row_idx=0;row_idx<(max_row_idx+1);row_idx++)
		for(int col_idx=0;col_idx<(max_col_idx+1);col_idx++)
			LCS_table[row_idx][col_idx] = 0;
	
	//Build LCS dynamic programming table
	BuildLCSTable(LCS_table, seq1, seq2);
	
	//Build LCS from LCStable
	LCS_val.clear();
	BuildLCS(LCS_table, seq1, seq2, max_row_idx, max_col_idx, LCS_val);
	
	//print LCS string
	for(int i=LCS_val.size()-1; i>=0;i--)
		cout << LCS_val[i];
	cout << endl;
	
	//free memory for LCS table
	for(int i=0;i<(max_row_idx+1);i++){
		delete[] LCS_table[i];
	}
	delete[] LCS_table;
}

void BuildLCS(int** LCStable, string seq1, string seq2, int row_idx, int col_idx, vector<char>& LCS_string){
	if(row_idx == 0 or col_idx == 0)
		return;
	else if(seq1[col_idx-1] == seq2[row_idx-1]){
		LCS_string.push_back(seq1[col_idx-1]);
		return(BuildLCS(LCStable, seq1, seq2, row_idx-1, col_idx-1,LCS_string));
	}
	else{
		if(LCStable[row_idx][col_idx-1]>LCStable[row_idx-1][col_idx])
			return(BuildLCS(LCStable, seq1, seq2, row_idx, col_idx-1,LCS_string));
		else
			return(BuildLCS(LCStable, seq1, seq2, row_idx-1, col_idx,LCS_string));
	}
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

int 
main(int argc, char* argv[]){

	vector<string> tokens;
	ifstream file;
	string lineBuffer, seq1, seq2;

	file.open(argv[1]);

	while (!file.eof()){
		getline(file, lineBuffer);
		if (lineBuffer.length() == 0)
			continue; //ignore all empty lines
		else{
			tokens.clear();
			Tokenize(lineBuffer, tokens, "\r\n;");
			if(tokens.size()){
				seq1 = tokens[0];
				seq2 = tokens[1];
				GetLCS(seq1, seq2);
			}
		}
	}
	return(0);
}