/*
Author: Sheldon Logan
Description:

Write a program to print a 2D array (n x m) in spiral order (clockwise)

Input sample:

Your program should accept as its first argument a path to a filename.The input file contains several lines. Each line is one test case. Each line contains three items (semicolon delimited). The first is 'n'(rows), the second is 'm'(columns) and the third is a single space separated list of characters/numbers in row major order. eg.

3;3;1 2 3 4 5 6 7 8 9
Output sample:

Print out the matrix in clockwise fashion, one per line, space delimited. eg.
1 2 3 6 9 8 7 4 5
*/

#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

void Tokenize(const string& str,vector<string>& tokens,const string& delimiters );

//Matrix class
class MatrixVector{
	private:
		int num_rows;
		int num_cols;
		vector<string> mat_vector;
	public:
		MatrixVector() {};
		MatrixVector(int r, int c, vector<string> &mat_vec);
		void spiralPrint();
		string getValue(int row_idx, int col_idx);
		void print_MatrixInfo();
};

//get value in matrix
string
MatrixVector::getValue(int row_idx, int col_idx){
	return(mat_vector[(row_idx*num_cols)+col_idx]);
}

//function to spiral print from Matrix
void 
MatrixVector::spiralPrint(){
	int xidx, yidx, min_x, min_y, max_x, max_y;
	bool not_printed = false;
	
	//index used for what variable to print
	xidx = 0;
	yidx = 0;
	
	//how far to print in each direction
	min_x = 0;
	min_y  = 0;
	max_x = num_cols;
	max_y = num_rows;
	
	//while you still have to print 
	while(true){
		
		//print left
		//first check that you can print left if not exit loop
		if(min_x >= max_x)
			break;
		
		for(yidx = min_x; yidx<max_x; yidx++){
			if(not_printed)
				cout << " " << getValue(xidx, yidx);
		
			else{
				cout << getValue(xidx, yidx);
				not_printed = true;
			}
		}
		yidx--;
		
		//add 1 to min_y since highest row has been printed
		min_y += 1;
		
		//print down
		//first check tht you can print down if not exit loop
		if(min_y >= max_y)
			break;
        
		for(xidx = min_y; xidx<max_y; xidx++){
			if(not_printed)
				cout << " " << getValue(xidx, yidx);
			
			else{
				cout << getValue(xidx, yidx);
				not_printed = true;
			}
		}
		xidx--;
		
		//subtract 1 from max_x since farthest column has been printed
		max_x -= 1;

		//print right
		//first check that you can print left
		if(min_x >= max_x)
			break;

		for(yidx = max_x-1; yidx >= min_x; yidx--)
			cout << " " << getValue(xidx, yidx);
		yidx++;
		
		//subtract 1 from max_y since lowest column has been printed
		max_y -= 1;
        
		//print up
		//first check that you can print up
		if(min_y >= max_y)
			break;

		for(xidx = max_y-1; xidx>= min_y; xidx--)
			cout << " " << getValue(xidx, yidx);
		
		xidx++;
		//add 1 to min_x since hearest row has been printed
		min_x += 1;		
	}
	cout << endl;
}

//constructor for matrix class
MatrixVector::MatrixVector(int r, int c, vector<string> &mat_vec){
	num_rows = r;
	num_cols = c;
	mat_vector.clear();
	for(int i=0; i<mat_vec.size(); i++)
		mat_vector.push_back(mat_vec[i]);
}

//print matrix
void
MatrixVector::print_MatrixInfo(){
	cout << "Num of Rows: " << num_rows << endl;
	cout << "Num of Columns: " << num_cols << endl;
	cout << "Vector for matrix: " << endl;
	for(int i=0; i<mat_vector.size(); i++)
		cout << mat_vector[i] << " ";
	cout << endl;
}

//Break string into tokens base on delimiters specified
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
	vector<string> tokens, array_tokens;
	int num_rows, num_cols;
	ifstream file;
	string lineBuffer;

	file.open(argv[1]);

	while (!file.eof()){
		getline(file, lineBuffer);
		if (lineBuffer.length() == 0)
			continue; //ignore all empty lines
		else{
			tokens.clear();
			Tokenize(lineBuffer, tokens, "\r\n;");
			if(tokens.size()){
				num_rows = atoi(tokens[0].c_str());
				num_cols = atoi(tokens[1].c_str());
				array_tokens.clear();
				Tokenize(tokens[2],array_tokens);
				MatrixVector input_mat(num_rows,num_cols, array_tokens);
				input_mat.spiralPrint();
			}
		}
	}
}
