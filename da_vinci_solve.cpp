/*
Author: Sheldon Logan

Da Vincy Problem
Description:

You were reading The Da Vyncy Code, the translation of a famous murder mystery novel into Python. 
The Code is finally revealed on the last page. You had reached the second to last page of the 
novel, and then you went to take a bathroom break.

While you were in the bathroom, the Illuminati snuck into your room and shredded the last page 
of your book. You had 9 backup copies of the book just in case of an attack like this, but the 
Illuminati shredded the last page from each of the those books, too. Then they propped up a fan, 
aimed it at the remains, and turned it on at high-speed.

The last page of your book is now in tatters.

However, there are many text fragments floating in the air. You enlist an undergraduate student 
for a 'summer research project' of typing up these fragments into a file. Your mission: reassemble
 the last page of your book.

Problem Description
=============

(adapted from a problem by Julie Zelenski)

Write a program that, given a set of fragments (ASCII strings), uses the following method 
(or a method producing identical output) to reassemble the document from which they came:

At each step, your program searches the collection of fragments. It should find the pair of 
fragments with the maximal overlap match and merge those two fragments. This operation should decrease
 the total number of fragments by one. If there is more than one pair of fragments with a 
 maximal overlap, you may break the tie in an arbitrary fashion.Fragments must overlap at 
 their start or end. For example:

- "ABCDEF" and "DEFG" overlap with overlap length 3
- "ABCDEF" and "XYZABC" overlap with overlap length 3
- "ABCDEF" and "BCDE" overlap with overlap length 4
- "ABCDEF" and "XCDEZ" do *not* overlap (they have matching characters in the middle, but the 
overlap does not extend to the end of either string).
Fear not - any test inputs given to you will satisfy the property that the tie-breaking order 
will not change the result, as long as you only ever merge maximally-overlapping fragments. 
Bonus points if you can come up with an input for which this property does not hold 
(ie, there exists more than 1 different final reconstruction, depending on the order in 
which different maximal-overlap merges are performed) -- if you find such a case, submit 
it in the comments to your code!

All characters must match exactly in a sequence (case-sensitive). Assume that your undergraduate 
has provided you with clean data (i.e., there are no typos).
Input sample:

Your program should accept as its first argument a path to a filename. Each line in this file 
represents a test case. Each line contains fragments separated by a semicolon, which your assistant
 has painstakingly transcribed from the shreds left by the Illuminati. You may assume that every 
 fragment has length at least 2 and at most 1022 (excluding the trailing newline, which should
 *not* be considered part of the fragment). e.g. Here are two test cases.

O draconia;conian devil! Oh la;h lame sa;saint!
m quaerat voluptatem.;pora incidunt ut labore et d;, consectetur, adipisci velit;olore magnam 
aliqua;idunt ut labore et dolore magn;uptatem.;i dolorem ipsum qu;iquam quaerat vol;psum quia 
dolor sit amet, consectetur, a;ia dolor sit amet, conse;squam est, qui do;Neque porro quisquam 
est, qu;aerat voluptatem.;m eius modi tem;Neque porro qui;, sed quia non numquam ei;lorem ipsum 
quia dolor sit amet;ctetur, adipisci velit, sed quia non numq;unt ut labore et dolore magnam 
aliquam qu;dipisci velit, sed quia non numqua;us modi tempora incid;Neque porro quisquam est, 
qui dolorem i;uam eius modi tem;pora inc;am al
Output sample:

Print out the original document, reassembled. e.g.

O draconian devil! Oh lame saint!
Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, 
sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat 
voluptatem.

*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include<algorithm>
#include <string>
#include<fstream>

//as defined in problem 
#define LONGEST_WORD 1024

using namespace std;

//structure containing information required to merge strings
struct merge_info{
	int merge_index;
	int len_overlap;
	int merge_type;	
};

void da_vinci_decode(vector<string>& input_string_frags);
int commonprefix(string& str1, string& str2);
void Tokenize(const string& str,vector<string>& tokens,const string& delimiters );
void print_string_frags(vector<string>& input_string_frags);
void find_overlap(string& str1, string& str2, int& overlap_len, int& overlap_idx);
merge_info find_overall_overlap(string& str1,string& str2);
void find_is_substring(string& str1, string& str2, int& overlap_length);
string merge_strings(string& str1, string& str2, merge_info& info);

//tokenize a string by specific delimiters
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

//find out if string 1 is a substring of string 2 
//if string 1 is a substring then ovelap is the length of string 1
void find_is_substring(string& str1, string& str2, int& overlap_length){
	unsigned found = str2.find(str1);
	if(found<LONGEST_WORD){
		overlap_length = str1.length();
		return;
	}
	overlap_length=-1;
	return;
}

//find the common prefix between strings
int commonprefix(string& str1, string& str2){
	int len_str1 = str1.length();
	int len_str2 = str2.length();
	int len_small_string;
	char curr_char;
	string s1,s2;
    
	if(len_str2 > len_str1){
		s1 = str1;
		s2 = str2;
		len_small_string = len_str1;
	}
	else{
		s1 = str2;
		s2 = str1;
		len_small_string = len_str2;
	}
     
	for(int i=0;i<len_small_string;i++){
		if(s1[i] != s2[i])
			return(0);
	}	
	return(s1.length());
}

//find out if string 2 overlaps with string 1 and return index of overlap and the amount of overlap
void find_overlap(string& str1, string& str2, int& overlap_len, int& overlap_idx){
	int str_1_len= str1.length();
	int str_2_len= str2.length();
	int overlap_prefix_len;
	char str1_first_char = str1[0];
	unsigned found;
	string  s2_substr;
	
	overlap_len = -1;
	overlap_idx = -1;
    
	found = str2.find(str1_first_char);
	while(found<LONGEST_WORD){
		if(str_1_len>=(str_2_len-found)){
			s2_substr = str2.substr (found);
			overlap_prefix_len = commonprefix(str1,s2_substr);
			if(overlap_prefix_len>0){
				overlap_len = str_2_len-found;
				overlap_idx = found;
				break;
			}
		}
		found = str2.find(str1_first_char,found+1);
	}
}

/*find out overall overlap
4 cases
1 - str 1 is a substring of string 2
2 - str2 is a substring of string 1
3 - str1-str2 overlap
4 - str2-str1 overlap
return a strucutre containng the overlap length, merge idx and merge type
*/
merge_info find_overall_overlap(string& str1,string& str2){
	int merge_idx = -1;
	int overlap_length = -1;
	merge_info info;
	
	//test 1  str 1 is a substring of string 2
	find_is_substring(str1, str2, overlap_length);
	if(overlap_length>0){
		info.merge_index = merge_idx;
		info.len_overlap = overlap_length;
		info.merge_type = 1;
		return(info);
	}
	
	//test 2  str 2 is a substring of string 1
	find_is_substring(str2, str1, overlap_length);
	if(overlap_length>0){
		info.merge_index = merge_idx;
		info.len_overlap = overlap_length;
		info.merge_type = 2;
		return(info);
	}
	
	//test3 str1-str2 overlap
	find_overlap(str1, str2, overlap_length, merge_idx);
	if(overlap_length>0){
		info.merge_index = merge_idx;
		info.len_overlap = overlap_length;
		info.merge_type = 3;
		return(info);
	}
	
	//test4 str2-str1 overlap
	find_overlap(str2, str1, overlap_length, merge_idx);
	if(overlap_length>0){
		info.merge_index = merge_idx;
		info.len_overlap = overlap_length;
		info.merge_type = 4;
		return(info);
	}
	info.merge_index = merge_idx;
	info.len_overlap = overlap_length;
	info.merge_type = -1;
	return(info);
}

//merge strings based on type of merge and the index of the merge
string merge_strings(string& str1, string& str2, merge_info& info){
	string return_str,s1,s2;
	
	//if no overlap new_string is the two strings put together
	if(info.merge_type == -1)
		return_str = str1+str2;
	//if string 1 is a substring of string 2 then return string 2
	else if(info.merge_type == 1)
		return_str  = str2;
	//if string 2 is a substring of string 1 then return string 1
	else if(info.merge_type == 2)
		return_str  = str1;
	//if overlap remove overlap and combine strings
	else if(info.merge_type == 3)
		return_str  = str2.substr(0,info.merge_index)+str1;
	else if(info.merge_type == 4)
		return_str  = str1.substr(0,info.merge_index)+str2;
		
	return(return_str);
}

//print string fragments
void print_string_frags(vector<string>& input_string_frags){
	for(int i=0; i<input_string_frags.size();i++)
		cout << input_string_frags[i] << endl;
}

/*davinci decoder
Technically a table containing the overlaps between each strings, the merge indices and merge types can be computed
once and then updating the merge indices after each string merge.
The current soluton recomputes the merge informations every time and is somewhat slower than creating the table
once and adjusting the merge indices
*/
void da_vinci_decode(vector<string>& input_string_frags){
	int max_overlap, string_frag_idx1, string_frag_idx2, len_string_frags;
	int num_runs =  input_string_frags.size()-1;
	merge_info max_merge_info, info;
	
	for(int run_idx=0; run_idx<num_runs; run_idx++){
		max_overlap = -2;	//smaller than the default -1 for overlap length
		len_string_frags = input_string_frags.size();
		for(int idx1=0; idx1<len_string_frags;idx1++){
			for(int idx2=idx1+1; idx2<len_string_frags;idx2++){
				info = find_overall_overlap(input_string_frags[idx1],input_string_frags[idx2]);
				if(info.len_overlap>max_overlap){
					max_overlap = info.len_overlap;
					string_frag_idx1 = idx1;
					string_frag_idx2 = idx2;
					max_merge_info = info;
				}
			}
		}
		input_string_frags[string_frag_idx1] = merge_strings(input_string_frags[string_frag_idx1] , input_string_frags[string_frag_idx2] , max_merge_info);
		//remove one item of the string fragments that were merged
		input_string_frags.erase(input_string_frags.begin()+string_frag_idx2);
	}
	print_string_frags(input_string_frags);

}

int 
main(int argc, char* argv[]){
	vector<string> tokens;
	ifstream file;
	string lineBuffer, curr_line;

	merge_info info;
	file.open(argv[1]);

	while (!file.eof()){
		getline(file, lineBuffer);
		if (lineBuffer.length() == 0)
			continue; //ignore all empty lines
		else{
			tokens.clear();
			Tokenize(lineBuffer, tokens, ";\r\n");
			if(tokens.size()){
				da_vinci_decode(tokens);
			}
		}
	}
	return(0);
}
