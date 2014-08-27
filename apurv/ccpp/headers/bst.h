#ifndef BST_H
#define BST_H

namespace bst {

	struct Node {
		int data;
		Node* left;
		Node* right;
	};

	extern void printInOrder(Node*);
	extern void printPostOrder(Node*);
	extern void printPreOrder(Node*);
	extern Node* createNode(int);
	extern Node* insert(Node*,int);
	extern void draw(Node*);
	extern int getHeight(Node*);
	extern int getMaxWidth(Node*);
	extern int findKthSmallest(Node*, int);
	extern Node* convertTreeToDllist(Node*);
	extern void draw(Node*);
}

#endif
