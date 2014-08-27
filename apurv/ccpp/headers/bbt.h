#ifndef BBT_H
#define BBT_H

namespace bbt {

	struct Node {
		int data;
		Node* left;
		Node* right;
		int height;
	};
	
	extern Node* createNode(int);
	extern int getHeight(Node*);
	extern Node* insert(Node*, int);
	extern int getBalance(Node*);
	extern Node* remove(Node*,int);

}

#endif


