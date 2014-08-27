#include"bbt.h"
#include<cstdio>
#include<cstdlib>

using namespace std;

namespace bbt {

	Node* rightRotate(Node*);
	Node* leftRotate(Node*);
	Node* minValue(Node*);
	
	inline int max(int a, int b) {
		return ((a>b)?a:b);
	}

	Node* createNode(int info) {
		Node* n = (Node*)malloc(sizeof(Node));
		n->data = info;
		n->height = 1;
		n->left = NULL;
		n->right = NULL;
		return n;
	}
	
	int getHeight(Node *root)
	{
		if(root == NULL)
			return 0;
		return root->height;
	}
	
	int getBalance(Node *root)
	{
		if (root == NULL)
        return 0;
		return getHeight(root->left) - getHeight(root->right);
	}
	
	Node* insert(Node* root, int info) {
	
		if(!root) {
			return createNode(info);
		}
		
		if(root->data < info) {
			root->right = insert(root->right,info);
		} else {
			root->left = insert(root->left,info);
		}
		
		root->height = max(getHeight(root->left),getHeight(root->right)) + 1;
		
		int balance = getBalance(root);
		if(balance > 1 && info < root->left->data) {
			return rightRotate(root);
		}
		
		if(balance < -1 && info > root->right->data) {
			return leftRotate(root);
		}
		
		if(balance > 1 && info > root->left->data) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		
		if(balance < -1 && info < root->right->data) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		
		return root;
		
	}
	
	Node* remove(Node* root,int info) {
		if(!root) {
			return NULL;
		}
		
		//printf("Current root traversed : %d\n",root->data);
		if(root->data < info) {
			root->right = remove(root->right,info);
			//printf("Changed right root.. \n");
		} else if(root->data > info) {
			root->left = remove(root->left,info);
			//printf("Changed left root.. \n");
		} else {
			if(root->left == NULL || root->right == NULL) {
				//printf("Got the root to delete.. %d \n",root->data);
				Node* temp = root->left ? root->left : root->right;
				
				if(!temp) {
					temp = root;
					root = NULL;
				} else {
					*root = *temp;
				}
				
				free(temp);
				//printf("Deleted now... \n");
			} else {
				Node* temp = minValue(root->right);
				
				root->data = temp->data;
				root->right = remove(root->right, temp->data);
			}	
		}
		
		if(!root) {
			return NULL;
		}
		
		root->height = max(getHeight(root->left),getHeight(root->right)) + 1;
		//printf("Updated root height for root : %d\n",root->data);

		int balance = getBalance(root);
		if(balance > 1 && getBalance(root->left) >= 0) {
			return rightRotate(root);
		}
		//printf("Checked for lef left case.. \n");
		
		if(balance < -1 && getBalance(root->right) <= 0) {
			return leftRotate(root);
		}
		//printf("Checked for right right case.. \n");
		
		if(balance > 1 && getBalance(root->left) < 0) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		//printf("Checked for left right case.. \n");
		
		if(balance < -1 && getBalance(root->right) > 0) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		//printf("Checked for right left case.. \n");
		
		//printf("Check and updated root balancing for root : %d\n",root->data);
		
		return root;
	}
	
	Node* minValue(Node* root) {
		while(root->left) {
			root = root->left;
		}
		
		return root;
	}
	
	Node* rightRotate(Node* root) {
		
		Node* y = root->left;
		Node* k = y->right;
		
		y->right = root;
		root->left = k;
		
		root->height = max(getHeight(root->left),getHeight(root->right)) + 1;
		y->height = max(getHeight(y->left),getHeight(y->right)) + 1;
		
		return y;
		
	}
	
	Node* leftRotate(Node* root) {
	
		Node* y = root->right;
		Node* k = y->left;
		
		y->left = root;
		root->right = k;
		
		root->height = max(getHeight(root->left),getHeight(root->right)) + 1;
		y->height = max(getHeight(y->left),getHeight(y->right)) + 1;
		
		return y;
		
	}

}

