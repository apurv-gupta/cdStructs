#include"bst.h"
#include<cstdio>
#include<cstdlib>
#include<queue>

using namespace std;

namespace bst {

	inline int max(int a, int b) {
		return (a>b?a:b);
	}
	
	void fillWidths(Node*,int*,int);
	int _findKthSmallest(Node*,int*);

	void printInOrder(Node* root) {
		if(!root) {
			return;
		}
		printInOrder(root->left);
		printf("%d ",root->data);
		printInOrder(root->right);
	}
	
	void printPostOrder(Node* root) {
		if(!root) {
			return;
		}
		printPostOrder(root->left);
		printPostOrder(root->right);
		printf("%d ",root->data);
	}
	
	void printPreOrder(Node* root) {
		if(!root) {
			return;
		}
		printf("%d ",root->data);
		printPreOrder(root->left);
		printPreOrder(root->right);
	}
	
	Node* createNode(int info) {
		Node* n = (Node*)malloc(sizeof(Node));
		n->left = NULL;
		n->right = NULL;
		n->data = info;
		return n;
	}
	
	Node* insert(Node* root,int info) {
		if(!root) {
			Node* n = createNode(info);
			return n;
		}
		
		if(root->data > info) {
			root->left = insert(root->left,info);
		} else {
			root->right = insert(root->right,info);
		}
		
		return root;
	}	
	
	int getHeight(Node* root) {
		if(!root) {
			return 0;
		}
		return (max(getHeight(root->left),getHeight(root->right)) + 1);
	}
	
	int getMaxWidth(Node* root) {
		if(!root) {
			return 0;
		}
		
		int n = getHeight(root);
		int* count = (int*)calloc(n,sizeof(int));
		
		fillWidths(root,count,0);
		
		int max = count[0];
		for(int i=1;i<n;i++) {
			if(count[i] > max) {
				max = count[i];
			}
		}
		
		return max;
	}
	
	void fillWidths(Node* root, int* count, int level) {
		if(root) {
			count[level]++;
			fillWidths(root->left,count,level+1);
			fillWidths(root->right,count,level+1);
		}
	}
	
	int findKthSmallest(Node* root, int k) {
		if(!root) {
			return -1;
		}
		int *kp;
		*kp = k;
		return _findKthSmallest(root,kp);
	}
	
	int _findKthSmallest(Node* root, int* k) {
		if(!root) {
			return -1;
		}
		int lk = _findKthSmallest(root->left,k);
		if(lk > -1) {
			return lk;
		}
		if(*k == 1) {
			return root->data;
		} else if(*k < 1) {
			return -1;
		} else {
			(*k)--;
		}
		int rk = _findKthSmallest(root->right,k);
		if(rk > -1) {
			return rk;
		}
		return -1;
	}
	
	Node* convertTreeToDllist(Node* root) {
		if(!root) {
			return NULL;
		}
		
		root->left = convertTreeToDllist(root->left);
		root->right = convertTreeToDllist(root->right);
		
		Node* head = NULL;
		if(root->left) {
			head = root->left;
		} else {
			head = root;
		}
		
		if(root->left) {
			Node* temp = root->left;
			while(temp->right) {
				temp = temp->right;
			}
			temp->right = root;
			root->left = temp;
		}
		if(root->right) {
			root->right->left = root;
		}
		
		return head;
	}

	
}
