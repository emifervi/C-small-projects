/*
	Jose Guillermo Saldana Cardenas
	A01039888
	BST
*/

#include "NodeT.h"
#include <algorithm>
#include <stack>
#include <queue>
 
class BST
{
public:

	// Constructor & destroyer
	BST();
	~BST();

	// Insert, search, delete a number
	void add(int data);
	bool search(int data);
	void remove(int data);

	// print 1. preoder 2. inorder 3. postorder 5. level by level
	void print(int c);

	// print leaf nodes only
	void printLeaves();

	// count amount of treenodes the tree has
	int count();

  // return the height of the tree
	int height();

	// return the ancestors of a given treenode
	void ancestors(int data);

	// retur the level of the given node 
	int whatLevelamI(int data);

private:
	NodeT *root;
	int howManyChildren(NodeT *r);
	int pred(NodeT *r);
	int succ(NodeT *r);
	void preOrder(NodeT *r);
	void inOrder(NodeT *r);
	void postOrder(NodeT *r);
	void freeup(NodeT *r);
	void PL(NodeT *r);
	int getN(NodeT *r);
	int getHeight(NodeT *r);
	void printByLevel();

};


BST::BST(){
	root=NULL;	
}

void BST::freeup(NodeT *r){
	if(r!=NULL){
		freeup(r->getLeft());
		freeup(r->getRight());
		delete r;
	}
}

BST::~BST(){
	freeup(root);
}
int BST::howManyChildren(NodeT *r){
	int c = 0;
	if(r->getLeft() != NULL){
		c++;
	}
	if(r->getRight() != NULL){
		c++;
	}
	return c;
}

int BST::pred(NodeT *r){
	NodeT *aux = r->getLeft();
	while(aux->getRight() != NULL){
		aux = aux->getRight();
	}
	return aux->getData();
}

int BST::succ(NodeT *r){
	NodeT *aux = r->getRight();
	while( aux->getLeft() != NULL){
		aux = aux->getRight();
	}

	return aux->getData();
}

void BST::preOrder(NodeT *r){
	if(r != NULL){
		cout << r->getData() << " ";
		preOrder(r->getLeft());
		preOrder(r->getRight());
	}
}

void BST::inOrder(NodeT *r){
	if(r!=NULL){
		inOrder(r->getLeft());
		cout << r->getData() << " ";
		inOrder(r->getRight());

	}
}

void BST::postOrder(NodeT *r){
	if(r!=NULL){
		postOrder(r->getLeft());
		postOrder(r->getRight());
		cout << r->getData() << " ";

	}
}

void BST::add(int data){
	NodeT *father = NULL;
	NodeT *curr = root;
	while(curr!=NULL){
		father = curr;
		if(curr->getData() == data){
			return;
		}
		curr = (curr->getData() > data) ? 
						curr->getLeft() : curr->getRight();
	}
	if(father == NULL){
		root = new NodeT(data);
	} else {
		if(father->getData() > data){
			father->setLeft(new NodeT(data));
		} else {
			father->setRight(new NodeT(data));
		}
	}
}

bool BST::search(int data){
	NodeT *curr = root;
	while(curr!=NULL){
		if(curr->getData() == data){
			return true;
		}
		curr = (curr->getData() > data) ?
						curr->getLeft() : curr->getRight();
	}
	return false;
}
void BST::remove(int data){
	NodeT *curr = root;
	NodeT *father = NULL;
	
	while(curr != NULL && curr -> getData() != data){
		father = curr;
		curr = (curr->getData() > data) ?
						curr->getLeft() : curr->getRight();
	}
	
	if(curr == NULL){
		return;
	} 		
	int c = howManyChildren(curr);

	switch(c){
		case 0:
			if (father == NULL){
				root = NULL;
			}
			else {
				if(father->getData() > data){
					father->setLeft(NULL);
				}
				else{
					father->setRight(NULL);
				}
			}
			delete curr;
			break;

		case 1:
			if(father == NULL){
				if(curr->getLeft() != NULL){
					root = curr->getLeft();
				}
				else{
					root = curr->getRight();
				}
			}
			else {
				if (father->getData() > data){
					if(curr->getLeft() !=NULL){
						father->setLeft(curr->getLeft());
					}
					else{
						father->setLeft(curr->getRight());
					}
				}
				else{
					if(curr->getLeft() != NULL){
						father->setRight(curr->getLeft());
					}
					else{
						father->setRight(curr->getRight());
					}
				}
			}
			delete curr;
			break;

		case 2:
			int x = succ(curr);
			remove (x);
			curr->setData(x);
			break;
	}
}

void BST::print(int c){
	switch(c){
		case 1: 
			preOrder(root);
			break;
		case 2: 
			inOrder(root);
			break;
		case 3:
			postOrder(root);
			break;
		case 4:
			printLeaves();
			break;
		case 5:
			printByLevel();
			break;
	}
	cout<<endl;
}

void BST::PL(NodeT *r){
	if(r!=NULL){
		if(r->getLeft() == NULL && r->getRight() == NULL){
			cout<<r->getData()<<' ';
		} else {
			PL(r->getLeft());
			PL(r->getRight());
		}
	}
}

void BST::printLeaves(){
	PL(root);
}

int BST::getN(NodeT *r){
	if(r == NULL){
		return 0;
	} else {
		return 1 + getN(r->getLeft()) + getN(r->getRight());
	}
}

int BST::count(){
	return getN(root);
}

int BST::getHeight(NodeT *r){
	if(r!=NULL){
		return 1 + max(getHeight(r->getLeft()),getHeight(r->getRight()));
	
	}
	else{
		return 0;
	}
}

int BST::height(){
	return getHeight(root);
}

void BST::ancestors(int data){
	stack<NodeT *> stack;
	NodeT *curr = root;
	while(curr!= NULL){
		if( curr->getData() == data ){
			if(stack.empty()){
				cout<<"Ese dato no tiene ancestros."<<endl;
			}
			else{
				while(!stack.empty()){
					cout<<stack.top()->getData()<<" ";
					stack.pop();
				}
				cout<<endl;
			}
			return;
		}
		stack.push(curr);
		curr = (data > curr->getData() ) ? curr->getRight() : curr->getLeft();
	}
	cout<<"El dato no esta en el arbol."<<endl;
}



int BST::whatLevelamI(int data){
	NodeT *curr = root;
	int level = 0;
	while(curr != NULL){
		if(curr->getData() == data){
			return level;
		} 
		
		curr = (data > curr->getData()) ? curr->getRight(): curr->getLeft();
			
		level++;
	}
	return -1;
}

void BST::printByLevel(){
	if(root!=NULL){
		queue<NodeT *> q;
		q.push(root);
		NodeT *temp;
		while(!q.empty()){
			temp = q.front();
			q.pop();
			cout << temp->getData() << " ";

      if(temp->getLeft()!=NULL){
	      q.push(temp->getLeft());
	    }
	    if(temp->getRight()!=NULL){
	    	q.push(temp->getRight());
	    }


		}		
	}

}