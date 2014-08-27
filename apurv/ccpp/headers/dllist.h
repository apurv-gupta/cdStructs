#ifndef DLLIST_H
#define DLLIST_H

namespace dllist {

	struct Node {
		int data;
		Node* prev;
		Node* next;
	};
	
	extern Node* createNode(int);
	extern void addToBeg(Node**, int);
	extern void printList(Node*);

}

#endif
