#ifndef LLIST_H
#define LLIST_H

namespace llist {

	struct Node {
		int data;
		Node* next;
	};
	
	extern void addToBeg(Node**, Node*);
	extern void addToBeg(Node**, int);
	extern void addToEnd(Node**, Node*);
	extern void addToEnd(Node**, int);
	extern void addToEnd(Node**, Node**, Node*);
	extern void addToEnd(Node**, Node**, int);
	extern void printList(Node*);
	extern Node* createNode(int info);
	extern Node* reverseList(Node*);
	extern int getSize(Node*);
	extern Node* mergeSort(Node*);
	extern bool createLoop(Node*, int);
	extern bool isLooped(Node*);
	extern bool detectAndRemoveLoop(Node*);
	//extern Node* merge(Node*,Node*);

}

#endif


