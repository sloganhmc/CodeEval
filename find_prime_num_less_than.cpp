/*
Author: Sheldon Logan
Prime Numbers (Uses Sieve of Erat algorithm)

Description:

Print out the prime numbers less than a given number N. For bonus points your solution should run in N*(log(N)) time or better. You may assume that N is always a positive integer.

Input sample:

Your program should accept as its first argument a path to a filename. Each line in this file is one test case. Each test case will contain an integer n < 4,294,967,295. eg.

10
20
100
Output sample:

For each line of input, print out the prime numbers less than N, in ascending order, comma delimited. (There should not be any spaces between the comma and numbers) eg.

2,3,5,7
2,3,5,7,11,13,17,19
2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>
#include <inttypes.h>
using namespace std;

void print_prime_num(int N);
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

void print_prime_num(int N){
	int idx, rootN,  n;
	vector<int> prime_numbers;
		
	//there are no prime numbers less than 2 
	if(N<=2){
		cout << endl;
		return;
	}
	
	//only one prime number less than 3: 2 
	else if(N<=3){
		prime_numbers.push_back(2);
	}
	
	//prime numbers less than 4: 2,3
	else if(N<4){
		prime_numbers.push_back(2);
		prime_numbers.push_back(3);
	}
	
	else{
		prime_numbers.push_back(2);
		prime_numbers.push_back(3);
		//calculate square root of N (input to the algorithm) and round up
		rootN =  (int)ceil(sqrt(N));
		
		//allocate  array of booleans specifying whether a number is a prime or not
		//algorithms operates on values less than N inclusive so allocated extra value for N
		bool* is_prime;
		is_prime = new(nothrow) bool[N+1];
		if(is_prime == 0){
			cout << "Error creating is_prime array" << endl;
			exit(1);
		}
	
		//initalize array to false
		for(idx=0;idx<N;idx++)
			is_prime[idx] = false;

		for (int x = 1; x <= rootN; x++){
			for (int y = 1; y <= rootN; y++){
				n = (4*x*x)+(y*y);
				if (n <= N && (n % 12 == 1 || n % 12 == 5))
					is_prime[n] ^= true;
				n = (3*x*x)+(y*y);
				if (n <= N && n % 12 == 7) 
					is_prime[n] ^= true;
				n = (3*x*x)-(y*y);
				if (x > y && n <= N && n % 12 == 11) 
					is_prime[n] ^= true;
			}
		}

		//mark all squares of primes and mulitples of them as not primes
		for (idx = 2; idx <= rootN; idx++){ 
			if (is_prime[idx]){ 
				for (int i = idx*idx; i < N; i += idx*idx) 
					is_prime[i] = false;
			}
		}
		
		//add all prime numbers to the array
		for (idx = 5; idx < N; idx++){
			if (is_prime[idx]){
				prime_numbers.push_back(idx);
			}
		}
		
		//memory cleanup: erase is_prime array
		delete[] is_prime;
	}
	for (int i=0;i<prime_numbers.size()-1; i++){
		cout << prime_numbers[i] << ",";
	}
	if(prime_numbers.size() > 0);
		cout << prime_numbers[prime_numbers.size()-1]  << endl; 
	return;
}

int main (int argc, char* argv[])
{
	vector<string> tokens;
	ifstream file;
	string lineBuffer, str;

	file.open(argv[1]);

	while (!file.eof()){
		getline(file, lineBuffer);
		if (lineBuffer.length() == 0)
			continue; //ignore all empty lines
		else{
			tokens.clear();
			Tokenize(lineBuffer, tokens, "\r\n;");
			if(tokens.size()){
				str = tokens[0];
				print_prime_num(atoi(str.c_str()));
			}
		}
	}
}
