#include <iostream>
using namespace std;

#ifndef _NODE_H_
#define _NODE_H_
class Node{
		int data;
		int weight;
		Node* lchild;
		Node* rchild;
public:
	Node(int k){
		data = k;
		weight = 0;
		rchild = nullptr;
		lchild = nullptr;
	}
	Node* insertR(int k){
		if(this->data == k){
			this->weight++;
			return this;
		}
		if( this->data > k){
			 if (this->lchild == nullptr) {
				this->lchild = new Node(k);
        } else {
            this->lchild = this->lchild->insertR(k);  
        }
		}
		else {
			if (this->rchild == nullptr) {
				this->rchild = new Node(k);
			} else {
				this->rchild = this->rchild->insertR(k); 
			}
		}
		return this;
	}
	void inOrder(){
		if(this->lchild == nullptr) this->lchild->inOrder();
		cout << this->data << " ";
		if(this->rchild == nullptr) this->rchild->inOrder();
	}
};

#endif