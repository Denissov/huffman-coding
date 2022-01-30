#include <iostream>
#include "priority_queue_min.h"
using namespace std;

bool Priority_Queue_Min :: heap_check_down(int index){
        if (2 * (index + 1) - 1 < heap_size)
                if (heap[index]->frequency >= heap[2 * (index + 1) - 1]->frequency || (2 * (index + 1) < heap_size && heap[index]->frequency >= heap[2 * (index + 1)]->frequency))
                        return false;
        return true;
}

void Priority_Queue_Min :: Sift_Down(int index){
        while (!heap_check_down(index)){
                if ((2 * (index + 1) < heap_size) && (heap[2 * (index + 1)]->frequency <= heap[2 * (index + 1) - 1]->frequency)){
                        swap(heap[index], heap[2 * (index + 1)]);
                        index = 2 * (index + 1);
                }
                else{
                        swap(heap[index], heap[2 * (index + 1) - 1]);
                        index = 2 * (index + 1) - 1;
                }
        }
}

void Priority_Queue_Min :: Sift_Up(int index){
        while((heap[index]->frequency < heap[(index - 1) / 2]->frequency) && (index != 0)){
                swap(heap[index], heap[(index - 1) / 2]);
                index = (index - 1) / 2;
        }
}

//int

Priority_Queue_Min :: Priority_Queue_Min(int n, char* symbols, unsigned long long* frequencies){
        heap_size = n;
        max_size = n;
        heap = new Node*[heap_size];
        for (int i = 0; i < n; i++)
                heap[i] = new Node;
        for (int i = 0; i < n; i++){
                heap[i]->symbol = symbols[i];
                heap[i]->frequency = frequencies[i];
                heap[i]->left = NULL;
                heap[i]->right = NULL;
        }
        for (int i = (heap_size - 1) / 2; i >= 0; i--)
                Sift_Down(i);
}

Node *Priority_Queue_Min :: Extract_Min(){
        Node *tmp = new Node;
        tmp->frequency = heap[0]->frequency;
        tmp->symbol = heap[0]->symbol;
        tmp->left = heap[0]->left;
        tmp->right = heap[0]->right;
        heap[0]->frequency = heap[heap_size - 1]->frequency;
        heap[0]->symbol = heap[heap_size - 1]->symbol;
        heap[0]->left = heap[heap_size - 1]->left;
        heap[0]->right = heap[heap_size - 1]->right;
//      swap(heap[0], heap[heap_size - 1]);
        heap_size = heap_size - 1;
        Sift_Down(0);
        return tmp;
}

void Priority_Queue_Min :: Insert(Node *new_elem){
        if (heap_size + 1 > max_size){
                cout << "queue is full\n";
                return;
        }
        else{
                heap_size = heap_size + 1;
                heap[heap_size - 1]->frequency = new_elem->frequency;
                heap[heap_size - 1]->symbol = new_elem->symbol;
                heap[heap_size - 1]->left = new_elem->left;
                heap[heap_size - 1]->right = new_elem->right;
                Sift_Up(heap_size - 1);
        }
}

Priority_Queue_Min :: ~Priority_Queue_Min(){
        for (int i = 0; i < max_size; i++)
                delete heap[i];
        delete [] heap;
}

void Priority_Queue_Min :: Print_Heap(){
        for(int i = 0; i < heap_size; i++)
                cout << heap[i]->frequency << ' ';
        cout << '\n';
}

Node * Priority_Queue_Min :: Build_Huffman_Tree(){
        Node *root;
        Node *tmp_1 = NULL;
        Node *tmp_2 = NULL;
        while (heap_size != 1){
                root = new Node;
                root->symbol = '\n';
                tmp_1 = (*this).Extract_Min();
                tmp_2 = (*this).Extract_Min();
                root->left = tmp_1;
                root->right = tmp_2;
                root->frequency = tmp_1->frequency + tmp_2->frequency;
                Insert(root);
        }
        return root;
}

int Priority_Queue_Min :: depth(Node* root){
        if (root == NULL)
                return 0;
        else{
                int l = depth(root->left);
                int r = depth(root->right);
                if (l > r)
                        return (l+1);
                else
                        return (r+1);
        }
}

void Priority_Queue_Min :: printLevel(Node* root, unsigned long long level){
        if (root == NULL)
                return;
        if (level == 1)
                cout << root->frequency << ' ';
        else if (level > 1){
                printLevel(root->left, level-1);
                printLevel(root->right, level-1);
        }
}

void Priority_Queue_Min :: Print(Node* root){
        int h = depth(root);
        for (int i = 1; i <= h; i++){
                printLevel(root, i);
                cout << '\n';
        }
}

int Priority_Queue_Min :: Tree_Size(Node* root){
        if (root == NULL)
                return 0;
        else
                return (1 + Tree_Size(root->left) + Tree_Size(root->right));
}

bool Priority_Queue_Min :: Leaf_Test(Node* x){
        if (x->left == NULL && x->right == NULL && x != NULL)
                return true;
        return false;
}

void Priority_Queue_Min :: Print_Huffman_Tree(Node* root, string s){
        if (Leaf_Test(root)){
                cout << root->symbol << ": " << s << '\n';
        }
        else{
                Print_Huffman_Tree(root->left, s + '0');
                Print_Huffman_Tree(root->right, s + '1');
        }

}

void Priority_Queue_Min :: symbol_code(Node *root, char* symbols, string* codes, string s, unsigned long long &num){
	if (Leaf_Test(root)){
		codes[num] = s;
		symbols[num] = root->symbol;
		num++;
//		cout << s << '\n';
	}
	else{
		symbol_code(root->left, symbols, codes, s + '0', num);
		symbol_code(root->right, symbols, codes, s + '1', num);
        }
}
