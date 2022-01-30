#include <iostream>
#include <fstream>
#include <string>
#include "priority_queue_min.h"
using namespace std;

void symbol_count(ifstream &input, unsigned long long* frequencies){
	string s;
	while (getline(input, s, '\0'))
		for (int i = 0; i < s.size(); i++){
			frequencies[s[i]]++; 
		}
}

char replace_one(int i, char c){
        char one = 'b' - 'a';
        char n = one << i;
        return c | n;
}

char code_symbol(string s){
	char c = 'a' - 'a';
	for (int i = 0; i < s.size(); i++){
		if (s[i] != '0')
			c = replace_one(s.size() - i - 1, c);
	}
	return c;
}

void huffman_coding(ifstream &input_code, ofstream &output_code){
	char c;
        string str;
        int count = 0;
        while(input_code >> c){
                str.append(1, c);
                count++;
                if (count == 8){
                        c = code_symbol(str);
                        output_code << c;
                        count = 0;
                        str.clear();
                }
        }
}

char ith_bit(int i, char c){
        char one = 'b' - 'a';
        int n = one << i;
        if (c == replace_one(i, c))
                return '1';
        else
                return '0';
}

int main(int argc, char* argv[]){
//input file: "input1.txt"
	ifstream input(argv[1]);
	ofstream output("output.txt");
	ifstream input_code("output.txt");
//argv[2]: "code.txt"
	ofstream output_code(argv[2]);
	ofstream output_bin("bin_code.txt");
	ifstream input_bin("bin_code.txt");
//argv[3]: "decode.txt"
	ofstream output_decode(argv[3]);
	unsigned long long* frequencies = new unsigned long long[128]; 
	for (int i = 0; i < 128; i++)
		frequencies[i] = 0;
	symbol_count(input, frequencies);
	unsigned long long j = 0, num = 0, num_of_codes = 0;
	int size = 0;
	for (int i = 0; i < 128; i++)
		if (frequencies[i] != 0)
			size++;
	unsigned long long* freq = new unsigned long long[size];
	char* symbols = new char[size];
	for (int i = 0; i < 128; i++)
		if (frequencies[i] != 0){
			freq[j] = frequencies[i];
			symbols[j] = i;
			j++;
		}
	Priority_Queue_Min heap(j, symbols, freq);
	Node *root = heap.Build_Huffman_Tree(); 
	string *s = new string[j];
	heap.symbol_code(root, symbols, s, "", num);
	string read; 
	ifstream rewrite("input1.txt");
	while (getline(rewrite, read, '\0')){
		for (int i = 0; i < read.size(); i++){
			for (unsigned long long k = 0; k < j; k++)
				if (symbols[k] == read[i]){
					output << s[k];
					num_of_codes += s[k].size();
					break;
				}
		}
	}
	int res = (num_of_codes / 8 + 1) * 8 - num_of_codes;
	if (res == 8)
		res = 0;
	if (res != 8)
		for (int i = 0; i < res; i++)
			output << '0';
	output.close();	
	huffman_coding(input_code, output_code);
	heap.Print_Huffman_Tree(root, "");
	input_code.close();
	output_code.close();
	char c;
	unsigned long long count = 0;
	output_bin.close();
	string str("");
	ifstream f("code.txt");
	char sym;
	unsigned long long num_of_codes_1 = 0;
	while (f.get(sym)){		
		for (int i = 0; i < 8; i++)
			str.append(1, ith_bit(7 - i, sym));
		for (unsigned long long i = 0; i < j; i++)
			if (str.find(s[i]) == 0){
				output_decode << symbols[i];
				num_of_codes_1 += s[i].size();
				str.erase(0, s[i].size());
				i = 0;
			}
		if (num_of_codes_1 == num_of_codes){
//			cout << num_of_codes << ' ' << num_of_codes_1;
			break;
		}	
	}
	f.close();
	delete [] frequencies;
	delete [] freq;
	delete [] symbols;
	delete [] s;
	input.close();
	rewrite.close();
	output_decode.close();
	return 0;
}

