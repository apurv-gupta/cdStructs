#include"dllist.h"
#include"bst.h"
#include<cstdio>
#include<cstdlib>

using namespace std;

namespace dllist {
	
	Node* createNode(int info) {
		Node* n = (Node*)malloc(sizeof(Node));
		n->prev = NULL;
		n->next = NULL;
		n->data = info;
	}
	
	void addToBeg(Node** head, int info) {
		Node* n = createNode(info);
		n->next = (*head);
		if((*head)) {
			(*head)->prev = n;
		}
		(*head) = n;
	}
	
	void printList(Node* head) {
		while(head) {
			printf("%d ",head->data);
			head = head->next;
		}
	}
	
}
