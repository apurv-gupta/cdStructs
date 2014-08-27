#include"bst.h"
#include<cstdio>

using namespace std;
using namespace bst;

main() {
	
	//int treeSeq[] = {5000,40,30,20,10,8,2,5004,5002,5003,70000};
	int treeSeq[] = {0,6,2,8,1,1000,900,10000,800,950,2000,20000,700,940,960,3000,15000,750,970,2500,16000,755,965,980,760,963,967,757,765,756,758,770,50,30,90,7,-432,-23,-543,-9,-2,-3,-10,-654,-31,-21,-24,-27,-45,-63,-1,-32,-73,-83,-93,-103,-87,-67,-77,-113,-100,};

	Node* root = NULL;
	for(int i=0;i<sizeof(treeSeq)/sizeof(int);i++) {
		root = insert(root,treeSeq[i]);
	}
	printInOrder(root);
	printf("\n");
	draw(root);
	
}

//root = insert(root,800);
//root = insert(root,400);
//root = insert(root,1200);
//root = insert(root,600);
//root = insert(root,1000);
//root = insert(root,200);
//root = insert(root,700);
//root = insert(root,300);
//root = insert(root,100);
//root = insert(root,500);
