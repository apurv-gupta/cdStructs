#include"llist.h"
#include<cstdio>

using namespace std;
using namespace llist;

main() {
	
	Node* l1;
	//addToBeg(&l1,7);
	//addToBeg(&l1,6);
	//addToBeg(&l1,5);
	//addToBeg(&l1,4);
	//addToBeg(&l1,3);
	//addToBeg(&l1,2);
	addToBeg(&l1,1);
	printList(l1);
	//l1 = reverseList(l1);
	//printList(l1);
	if(!createLoop(l1,2)) {
		printf("Not able to create loop at position 2\n");
		if(!createLoop(l1,0)) {
			printf("Not able to create loop at position 0\n");
		} else {
			printf("Able to create loop at position 0\n");
		}
	} else {
		printf("Able to create loop at position 2\n");
	}
	
	if(isLooped(l1)) {
		printf("Able to detect loop in list\n");
	} else {
		printf("Not able to detect loop in list\n");
	}
	
	if(detectAndRemoveLoop(l1)) {
		printf("Able to remove loop in list\n");
		printList(l1);
	} else {
		printf("Not able to remove loop in list\n");
	}
}
