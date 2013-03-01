/*
Find Min Path Sum
Description:

You are given an n*n matrix of integers. You can move only right and down. 
Calculate the minimal path sum from the top left to the bottom right

Input sample:

Your program should accept as its first argument a path to a filename. The first line 
will have the value of n(the size of the square matrix). This will be followed by n 
rows of the matrix. (Integers in these rows will be comma delimited). After the n rows, 
the pattern repeats. e.g.

2
4,6
2,8
3
1,2,3
4,5,6
7,8,9
Output sample:

Print out the minimum path sum for each matrix. e.g.

14
21

*/

#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

void Tokenize(const string& str,vector<string>& tokens,const string& delimiters );

class Matrix{
	private:
		int N;
		vector<vector<int> > matrix_values;
	public:
		Matrix() {};
		Matrix(vector<string> &input_vectors, int in_N) ;
		void printMatrix();
		int find_min_sum();
};

int
Matrix::find_min_sum(){
	int val1, val2;
	int ** min_sum_array;
	
	//allocate array for minimum path sum
	min_sum_array = new(nothrow) int* [N];
	if(min_sum_array==0){
		exit(-1);
		cout << "error allocating 2d array for min sum" << endl;
	}
	for(int i=0; i<N; i++){
		min_sum_array[i] = new(nothrow) int[N];
		if(min_sum_array[i] ==0){
			exit(-1);
			cout << "error allocating 1d array for min sum" << endl;
		}
	}
	
	//go through array and calculate minimum sum
	for(int row_idx =0; row_idx<N; row_idx++){
		for(int col_idx =0; col_idx<N; col_idx++){
			//(0,0) value
			if(row_idx ==0 && col_idx ==0){
				min_sum_array[row_idx][col_idx] = matrix_values[row_idx][col_idx];
			}
			
			//rest of first row
			else if(row_idx == 0) {
				min_sum_array[row_idx][col_idx] = min_sum_array[row_idx][col_idx-1] + matrix_values[row_idx][col_idx];
			}
			
			//second row and beyond
			else{
				//if first column
				if(col_idx == 0){
					min_sum_array[row_idx][col_idx] = min_sum_array[row_idx-1][col_idx] + matrix_values[row_idx][col_idx];
				}
				//all other columns
				else{
					val1 = min_sum_array[row_idx][col_idx-1];
					val2 = min_sum_array[row_idx-1][col_idx];
					if(val1 < val2)
						min_sum_array[row_idx][col_idx] = val1 + matrix_values[row_idx][col_idx];
					else
						min_sum_array[row_idx][col_idx] = val2 + matrix_values[row_idx][col_idx];
				}
			}
		}
	}
	
	cout << min_sum_array[N-1][N-1] <<endl;
	
	//delete array for minimum path sum
	for(int i=0; i<N; i++)
		delete[] min_sum_array[i];
	
	delete [] min_sum_array;
}

Matrix::Matrix(vector<string> &input_vectors, int in_N){
	vector<string> tokens;
	for(int i=0; i <input_vectors.size(); i++){
		tokens.clear();
		Tokenize(input_vectors[i], tokens, "\r\n,");
		vector<int> temp_array;
		for(int j=0; j<tokens.size(); j++){
			temp_array.push_back(atoi(tokens[j].c_str()));
		}
		matrix_values.push_back(temp_array);
	}
	N = in_N;
}

void
Matrix::printMatrix(){
	cout << "Matrix size: " << N <<endl;
	cout << "Matrix: " << endl;
	for(int i=0; i<matrix_values.size(); i++){
		for(int j=0; j<matrix_values[i].size();j++){
			cout << matrix_values[i][j] << " ";
		}
		cout << endl;
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


int main(int argc, char* argv[] ){
	vector<string> tokens, array_tokens;
	int matrix_size;
	bool parsed_first_matrix;
	
	ifstream file;
	string lineBuffer;

	parsed_first_matrix = false;
	file.open(argv[1]);
	while (!file.eof()){
		getline(file, lineBuffer);
		if (lineBuffer.length() == 0)
			continue; //ignore all empty lines
		else{
			tokens.clear();
			Tokenize(lineBuffer, tokens, "\r\n,");
			if(tokens.size() == 1){
				if(parsed_first_matrix){
					Matrix input_matrix(array_tokens,matrix_size);
					//input_matrix.printMatrix();
					input_matrix.find_min_sum();
				}
				matrix_size = atoi(tokens[0].c_str());
				array_tokens.clear();
			}
			else{
				parsed_first_matrix = true;
				array_tokens.push_back(lineBuffer);
			}
		}
	}
	Matrix input_matrix(array_tokens,matrix_size);
	//input_matrix.printMatrix();
	input_matrix.find_min_sum();
}
