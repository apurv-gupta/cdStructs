#include<cstdio>
#include<cstdlib>
#include "llist.h"

namespace llist {
	
	using namespace std;
	
	//Private Functions (Not Declared in llist.h header
	Node* merge(Node*,Node*);
	
	void addToBeg(Node** head, Node* n) {
		if(!(*head)) {
			n->next = NULL;
			(*head) = n;
			return;
		}
		n->next = (*head);
		(*head) = n;
		return;
	}
	
	void addToBeg(Node** head, int info) {
		Node* n = createNode(info);
		if(!(*head)) {
			n->next = NULL;
			(*head) = n;
			return;
		}
		n->next = (*head);
		(*head) = n;
		return;
	}
	
	void addToEnd(Node** head, Node* n) {
		n->next = NULL;
		if(!(*head)) {
			(*head) = n;
			return;
		}
		Node* temp = (*head);
		while(temp->next) {
			temp = temp->next;
		}
		temp->next = n;
	}
	
	void addToEnd(Node** head, int info) {
		Node* n = createNode(info);
		if(!(*head)) {
			(*head) = n;
			return;
		}
		Node* temp = (*head);
		while(temp->next) {
			temp = temp->next;
		}
		temp->next = n;
	}

	void addToEnd(Node** front, Node** rear, Node* n) {
		n->next = NULL;
		if(!(*front) && !(*rear)) {
			(*front) = (*rear) = n;
			return;
		}
		(*rear)->next = n;
		(*rear) = n;
	}
	
	void addToEnd(Node** front, Node** rear, int info) {
		Node* n = createNode(info);
		if(!(*front) && !(*rear)) {
			(*front) = (*rear) = n;
			return;
		}
		(*rear)->next = n;
		(*rear) = n;
	}
	
	Node* createNode(int info) {
		Node* n = (Node*)malloc(sizeof(Node));
		n->data = info;
		n->next = NULL;
		return n;
	}
	
	void printList(Node *head) {
		while(head) {
			printf("%d ",head->data);
			head = head->next;
		}
		printf("\n");
	}
	
	Node* reverseList(Node* head) {
		
		if(!(head->next)) {
			return head;
		}
		
		Node* ret = reverseList(head->next);
		
		Node* tmp = head->next->next;
		head->next->next = head;
		head->next = tmp;
		
		return ret;
		
	}
	
	int getSize(Node* head) {
		int count = 0;
		while(head) {
			count++;
			head = head->next;
		}
		return count;
	}
	
	Node* mergeSort(Node* a) {
		if(!a || !(a->next)) {
			return a;
		}
		
		Node *m=a,*n=a->next,*tmp=NULL,*c=NULL;
		while(n && n->next) {
			m = m->next;
			n = n->next->next;
		}
		tmp = m->next;
		m->next = NULL;
		m = tmp;
		
		n = a;
		m = mergeSort(m);
		n = mergeSort(n);
		
		c = merge(m,n);
		return c;
	}
	
	Node* merge(Node* a, Node* b) {
		if(!a) {
			return b;
		}
		if(!b) {
			return a;
		}
		Node *c=NULL;
		if(a->data <= b->data) {
			c = a;
			c->next = merge(a->next,b);
		} else {
			c = b;
			c->next = merge(a,b->next);
		}
		return c;
	}
	
	/*
		Creates a loop in a linked list by pointing the last node's next pointer 
		to the node at length defined by param length.
		@Params
			head : linked lists head pointer
			length : position of node at which to create loop (position starts with 0)
		@Return
			bool : true if successfully able to create loop, false otherwise.
	*/
	bool createLoop(Node* head, int length) {
		if(!head) {
			return false;
		}
		if(length < 0) {
			return false;
		}
		Node* last = head;
		while(last->next) {
			last = last->next;
		}
		for(int i=0;i<length;i++) {
			if(!head) {
				return false;
			}
			head = head->next;
		}
		if(!head) {
			return false;
		}
		last->next = head;
		return true;
	}
	
	bool isLooped(Node* head) {
		if(!head) {
			return false;
		}
		Node* first = head;
		Node* second = head;
		while(first && second && second->next && (first!=second)) {
			first = first->next;
			second = second->next->next;
		}
		if(first && second && (first==second)) {
			return true;
		}
		return false;
	}
	
	bool detectAndRemoveLoop(Node* head) {
		if(!head) {
			return true;
		}
		if(!isLooped(head)) {
			return true;
		}
		Node* first = head;
		Node* second = head;
		do {
			first = first->next;
			second = second->next->next;
		} while(first!=second);
		int loopSize = 0;
		do {
			second = second->next;
			loopSize++;
		} while(first!=second);
		printf("Loop Size : %d\n",loopSize);
		first = head;
		second = head;
		for(int i=1;i<loopSize;i++) {
			second = second->next;
		}
		while(first!=second->next) {
			first=first->next;
			second=second->next;
		}
		second->next = NULL;
		return true;
	}	
	
}
