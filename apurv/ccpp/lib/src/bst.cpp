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
	
	
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pretty print a binary tree : Private Structures And Methods/////////////////////////////////////////////////////////////////////////////////
	
	//Pretty node structure
	struct Pnode {
		int data;		//data as in actual node in binary tree
		Pnode* left;	//left pointer of this node as in actual binary tree
		Pnode* right;	//right pointer of this node as in actual binary tree
		int lw;			//width of left subtree
		int rw;			//width of right subtree
		int w;			//width of this root
		int size;		//size of this root (Ex -> root with data 500 has size 3, root with data 50 has size 2)
		int margin;		//leftmost point of tree rooted with this root, on x axis.
	};
	
	/* 
	void printInOrder(Pnode* root) {
		if(!root) {
			return;
		}
		printInOrder(root->left);
		printf("(%d,%d,%d,%d,%d,%d) ",root->data,root->w,root->lw,root->rw,root->size,root->margin);
		printInOrder(root->right);
	}
	*/
	
	//Method to get size of node data
	//For definition of size, see comments in Pretty Node structure declaration (Pnode struct).
	int getSize(int data) {
		int count = 1;
		if(data < 0) {
			data = -data;
			count = 2;
		}
		int dig = data/10;
		while(dig) {
			dig = dig/10;
			count++;
		}
		return count;
	}
	
	//Method to create binary tree with pretty nodes(see Pretty node structure above), using original binary tree.
	//The structure of both trees is identical. Its just that the prettu node tree has more information stored in each node.
	//That extra information is used while pretty printing the binary tree, using pretty node tree.
	Pnode* createPrettyTree(Node* root) {
		if(!root) {
			return NULL;
		}
		
		Pnode *p = (Pnode*)malloc(sizeof(Pnode));
		p->data = root->data;
		p->margin = 0;
		p->size = getSize(root->data);
		p->lw = 0;
		p->rw = 0;
		p->left = createPrettyTree(root->left);
		p->right = createPrettyTree(root->right);
		if(p->left) {
			p->lw = p->left->w;
			if(!(p->left->right)) {
				p->lw += 1;
			}
		}
		if(p->right) {
			p->rw = p->right->w;
			if(!(p->right->left)) {
				p->rw += 1;
			}
		}
		p->w = p->lw + p->rw + p->size;
		return p;
	}
	
	//Method to print a character sequence n times, from current cursor location.
	void printCharSeq(int ch, int n) {
		for(int i=0;i<n;i++) {
			printf("%c",ch);
		}
	}
	
	//updates current cursor location to the margin of the current node in picture, while pretty printing the binary tree.
	//For definition of margin, see comments in Pretty Node structure declaration (Pnode struct).
	bool updateCursor(int margin, int& curPos) {
		if(margin > curPos) {
			printCharSeq(' ',margin-curPos);
			curPos = margin;
		} else if(margin < curPos) {
			printf("Error in tree printing algorithm. Please correct and retry.\n");
			return false;
		}
		return true;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//This method pretty prints a binary tree using pretty node structure and methods.
	void draw(Node* root) {
		Pnode* proot = createPrettyTree(root);									//Creates pretty binary tree structure which will be used below to pretty print binary tree. 
		//printInOrder(proot);
		queue<Pnode*> q[2];														//Two queues are used, q[0] and q[1]
																				//q[0] is used to print nodes at a level and horizontal branches corresponding to each node.
																				//q[1] is used to print vertical branches for the nodes printed by q[0].
		q[0].push(proot);
		while(!q[0].empty() || !q[1].empty()) {
			int curPos = 0;
			printf("\n");
			while(!q[0].empty()) {												//This while loop prints node data and horizontal branches at a level in each iteration.
				Pnode* pn = q[0].front();
				q[0].pop();
				q[1].push(pn);
				if(!updateCursor(pn->margin,curPos)) {							//Updates cursor location to margin of current node in picture.
					return;
				}
				if(pn->left) {													//Print left horizontal branch, if left of node is present(not null).
					int lspace = pn->left->w - pn->left->rw;
					printCharSeq(' ',lspace+1);
					printCharSeq('_',pn->lw-lspace-1);
					pn->left->margin = pn->margin;								//Update margin of left subtree
					curPos += pn->lw;											//Update cursor location, whenever something gets print
				}
				printf("%d",pn->data);											//Print the node itself
				curPos += pn->size;												//Update cursor location, whenever something gets print
				if(pn->right) {													//Print right horizontal branch, if right of node is present(not null)
					int luscore = pn->right->lw - 1;
					printCharSeq('_',luscore);
					pn->right->margin = pn->margin + (pn->w - pn->rw);			//Update margin of right subtree
					if(!pn->right->left) {										//To take care of extra '\' that gets printed and increases the margin of the right subtree by 1 
						pn->right->margin += 1;
					}
					if(luscore > 0) {
						curPos += luscore;										//Update cursor location, whenever something gets print
					}
				}
			}
			
			printf("\n");														//Node at this level as well as horizontal branches of those nodes are printed now, 
			curPos = 0;															//now move to next line and update the cursor position to 0.
			
			while(!q[1].empty()) {												//This while loop prints the vertical branches for the nodes printed by above while loop.
				Pnode* pn = q[1].front();
				q[1].pop();
				if(pn->left) {
					Pnode* pn1 = pn->left;
					q[0].push(pn1);												//pushes left child to main queue q[0].
					if(!updateCursor(pn1->margin,curPos)) {						//Updates cursor location to margin of current node in picture.
						return;
					}
					if(pn1->left) {												//Move towards left vertical branch location for this node.
						curPos += pn1->lw;										//Update cursor location, whenever something gets print
						printCharSeq(' ',pn1->lw);
					}
					curPos += pn1->size;										//Move towards left vertical branch location for this node.
					printCharSeq(' ',pn1->size);
					printf("/");												//prints left vertical branch.
					curPos += 1;												//Update cursor location, whenever something gets print
				}
				if(pn->right) {
					Pnode* pn1 = pn->right;
					q[0].push(pn1);												//pushes right child to main queue q[0].
					if(!updateCursor(pn1->margin-1,curPos)) {					//Updates cursor location to 'margin-1' of current node in picture. -1 because vertical 
																				//branch is printed one cursor before the actual node data gets printed. 
						return;
					}
					if(pn1->left) {												//Move towards right vertical branch location for this node.
						curPos += pn1->lw;										//Update cursor location, whenever something gets print
						printCharSeq(' ',pn1->lw);
					}
					printf("\\");												//prints right vertical branch.
					curPos += 1;												//Update cursor location, whenever something gets print
				}
			}
		}
		//printInOrder(proot);
	}
	
}
