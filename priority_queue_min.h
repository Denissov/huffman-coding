using namespace std;

struct Node{
        char symbol;
//      int frequency;
	unsigned long long frequency;
        Node *left;
        Node *right;
};

class Priority_Queue_Min{
        Node ** heap;
//        unsigned long long heap_size;
//        unsigned long long max_size;
	int heap_size;
	int max_size;
        bool heap_check_down(int index);
        void Sift_Up(int index);
        void Sift_Down(int index);
	int depth(Node* root);
public:
        Priority_Queue_Min(int n, char * symbols, unsigned long long * frequencies);
        Node * Extract_Min();
        void Insert(Node * new_elem);
        Node * Build_Huffman_Tree();
        ~Priority_Queue_Min();
        void Print_Heap();
	void printLevel(Node* root, unsigned long long level);
	void Print(Node* root);
        bool Leaf_Test(Node* x);
        void Print_Huffman_Tree(Node* root, string s);
        int Tree_Size(Node* root);
	void symbol_code(Node *root, char* symbols, string* codes, string s, unsigned long long &num);
};

