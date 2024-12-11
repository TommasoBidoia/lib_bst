#include <iostream>
#include <climits>

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

Node* insertI(int k){
	Node* father{nullptr};
	Node* current{this};
	bool check;
	while(current != nullptr){
		if(k < current->data){
			father = current;
			current = current->left;
			check = true;
		}
		else if(k > current->data){
			father = current;
			current = current->right;
			check = false;
		}
	}
	if(check){
		father->left = new Node(k);
	}else if(!check){
		father->right = new Node(k);
	}
	return this;
}

bool searchR(int k) {
    if (this == nullptr) {
        return false;
    }
    if (k == this->data) {
        return true;
    }
    if (k < this->data) {
        return this->left->searchR(k);
    }
    return this->right->searchR(k);
}

bool searchI( int k) {
	Node* current = this;
    while (current != nullptr) {
        if (k == current->data) {
            return true;
        } else if (k < current->data) {
            current = current->left;
        } else {
           current = current->right;
        }
    }
    return false;
}

Node* deleteNode(int k) {
    if (k < this->data) {
        if (this->left != nullptr) {
            this->left = this->left->deleteNode(k);
        }
    } else if (k > this->data) { 
        if (this->right != nullptr) {
            this->right = this->right->deleteNode(k);
        }
    } else { 
        
        if (this->left == nullptr) {
            Node* temp = this->right;
            delete this;
            return temp;
        }
        
        if (this->right == nullptr) {
            Node* temp = this->left;
            delete this;
            return temp;
        }
        
        Node* succ = this->right; 
        while (succ->left != nullptr) {
            succ = succ->left;
        }
        this->data = succ->data; 
        this->right = this->right->deleteNode(succ->data); 
    }
    return this;
}

void preOrder() {
        cout << data << " ";
        if (left != nullptr) {
            left->preOrder();
        }
        if (right != nullptr) {
            right->preOrder();
        }
}

void inOrder(){
		if(this->lchild == nullptr) this->lchild->inOrder();
		cout << this->data << " ";
		if(this->rchild == nullptr) this->rchild->inOrder();
	}
};
void postOrder() {
        if (left != nullptr) {
            left->postOrder();
        }
        if (right != nullptr) {
            right->postOrder();
        }
		cout << data << " ";
}

bool isBST() {
    Node* prev = nullptr;
    Node* stack[100];
    int top = -1;
    Node* current = this;
    while (current != nullptr || top >= 0) {
        while (current != nullptr) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        if (prev != nullptr && current->data <= prev->data)
            return false;
        prev = current;
        current = current->right;
    }
    return true;
}
