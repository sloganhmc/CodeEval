/*
Author: Sheldon Logan

Description:

You will be given an M*N matrix. Each item in this matrix is either a '*' or a '.'. A '*' indicates a mine whereas a '.' does not. The objective of the challenge is to output a M*N matrix where each element contains a number (except the positions which actually contain a mine which will remain as '*') which indicates the number of mines adjacent to it. Notice that each position has at most 8 adjacent positions e.g. left, top left, top, top right, right, ...

Input sample:

Your program should accept as its first argument a path to a filename. Each line in this file contains M,N, a semicolon and the M*N matrix in row major form. e.g.

3,5;**.........*...
4,4;*........*......
Output sample:

Print out the new M*N matrix (in row major form) with each position(except the ones with the mines) indicating how many adjacent mines are there. e.g.

**100332001*100
*10022101*101110
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;
void Tokenize(const string& str,vector<string>& tokens,const string& delimiters );

class MineSweepMatrix{
	private:
		int num_rows, num_cols;
		string mine_vector;
	public:
		MineSweepMatrix() {};
		MineSweepMatrix(int nrows, int ncols, string mvector);
		void printMineSweepMatrix();
		void calculateMines();
		int convert_mat_idx_to_vec_idx(int r_idx, int c_idx);
		int count_mines(int r_idx, int c_idx);
};

void
MineSweepMatrix::calculateMines(){
	for(int row_idx=0; row_idx<num_rows; row_idx++){
		for(int col_idx=0; col_idx<num_cols; col_idx++){
			if(mine_vector[convert_mat_idx_to_vec_idx(row_idx, col_idx)] == '*')
				cout << "*";
			else
				cout << count_mines(row_idx,col_idx);
		}
	}
	cout << endl;
}

int 
MineSweepMatrix::count_mines(int r_idx, int c_idx){
	int count = 0;
	
	//up left
	if(r_idx>0 && c_idx>0)
		if(mine_vector[convert_mat_idx_to_vec_idx(r_idx-1, c_idx-1)] == '*')
			count++;
        
	//up
	if(r_idx>0)
		if(mine_vector[convert_mat_idx_to_vec_idx(r_idx-1, c_idx)] == '*')
			count++;
            
	//up right
	if(r_idx>0 && c_idx<(num_cols-1))
		if(mine_vector[convert_mat_idx_to_vec_idx(r_idx-1, c_idx+1)] == '*')
			count++;
        
	//right
	if(c_idx<(num_cols-1))
		if(mine_vector[convert_mat_idx_to_vec_idx(r_idx, c_idx+1)] == '*')
			count++;
    
	//down right
	if(r_idx<(num_rows-1) && c_idx<(num_cols-1))
		if(mine_vector[convert_mat_idx_to_vec_idx(r_idx+1, c_idx+1)] == '*')
			count++;
       
	//down
	if(r_idx<(num_rows-1))
		if(mine_vector[convert_mat_idx_to_vec_idx(r_idx+1, c_idx)] == '*')
			count++;
	//down left
	if(r_idx<(num_rows-1) && c_idx>0)
		if(mine_vector[convert_mat_idx_to_vec_idx(r_idx+1, c_idx-1)] == '*')
			count++;
    
	//left
	if(c_idx>0)
		if(mine_vector[convert_mat_idx_to_vec_idx(r_idx, c_idx-1)] == '*')
			count++;
	
	return(count);
}

int
MineSweepMatrix::convert_mat_idx_to_vec_idx(int r_idx, int c_idx){
	return((r_idx*num_cols)+c_idx);
}

MineSweepMatrix::MineSweepMatrix(int nrows, int ncols, string mvector){
	num_rows = nrows;
	num_cols = ncols;
	mine_vector = mvector;
}

void
MineSweepMatrix::printMineSweepMatrix(){
	cout << "Num of rows: " << num_rows << endl;
	cout << "Num of columns: " << num_cols << endl;
	cout << "Mine array: " << mine_vector << endl;
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

int main(int argc, char* argv[]){
	int num_rows, num_cols;
	vector<string> tokens, cols_rows_tokens;
	ifstream file;
	string lineBuffer;

	file.open(argv[1]);

	while (!file.eof()){
		getline(file, lineBuffer);
		if (lineBuffer.length() == 0)
			continue; //ignore all empty lines
		else{
			tokens.clear();
			Tokenize(lineBuffer, tokens, ";");
			if(tokens.size()){
				cols_rows_tokens.clear();
				Tokenize(tokens[0], cols_rows_tokens, ",");
				num_rows = atoi(cols_rows_tokens[0].c_str());
				num_cols = atoi(cols_rows_tokens[1].c_str());
				MineSweepMatrix inMat = MineSweepMatrix(num_rows, num_cols, tokens[1]);
				inMat.calculateMines();
			}
		}
	}
}