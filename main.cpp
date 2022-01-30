#include <iostream>
#include <fstream>
#include "priority_queue_min.h"
using namespace std;

int main(int argc, char* argv[]){
	ifstream input(argv[1]);
	int size;
	input >> size;
	int *frequencies = new int[size];
	char *symbols = new char[size];
	int i = 0;
	while(input){
		input >> frequencies[i];
		input >> symbols[i];
		i++;
	}
	input.close();	
	Priority_Queue_Min heap(size, symbols, frequencies);
	Node *root = heap.Build_Huffman_Tree();
	heap.Print_Huffman_Tree(root, "");
	delete [] frequencies;
	delete [] symbols;
	return 0;
}
