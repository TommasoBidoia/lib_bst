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

Node* Rc_Del(Node* r, int num) {
    if (r == nullptr) {
        return r;
    }
    if (num < r->data) {
        r->left = Rc_Del(r->left, num);
    } else if (num > r->data) {
        r->right = Rc_Del(r->right, num);
    } else {
        if (r->left == nullptr) {
            Node* temp = r->right;
            delete r;
            return temp;
        } else if (r->right == nullptr) {
            Node* temp = r->left;
            delete r;
            return temp;
        }
        Node* succparent = r;
        Node* succ = r->right;
        while (succ->left != nullptr) {
            succparent = succ;
            succ = succ->left;
        }
        
        if (succparent != r) {
            succparent->left = succ->right;
        } else {
            succparent->right = succ->right;
        }
        r->data = succ->data;
        delete succ;
    }
    return r;
}


Node* It_Del(Node* r, int num) {
    if (r == nullptr) return r;
    Node* parent = nullptr;
    Node* curr = r;
    while (curr != nullptr && curr->data != num) {
        parent = curr;
        if (num < curr->data) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    if (curr == nullptr) return r;
    if (curr->left == nullptr && curr->right == nullptr) {
        if (curr != r) {
            if (parent->left == curr) parent->left = nullptr;
            else parent->right = nullptr;
        } else {
            r = nullptr;
        }
    }
    else if (curr->left && curr->right) {
        Node* succparent = curr;
        Node* succ = curr->right;
        while (succ->left != nullptr) {
            succparent = succ;
            succ = succ->left;
        }
        if (succparent != curr) succparent->left = succ->right;
        else succparent->right = succ->right;
        curr->data = succ->data;
        curr = succ;
    }
    else {
        Node* child = (curr->left) ? curr->left : curr->right;
        if (curr != r) {
            if (curr == parent->left) parent->left = child;
            else parent->right = child;
        } else {
            r = child;
        }
    }
    delete curr;
    return r;
}

void preOrder(Node* node) {
	if (node == nullptr) return;
	cout << node->data << " ";
	preOrder(node->left);
	preOrder(node->right);
}

void posOrder(Node* node) {
	posOrder(node->left);
	posOrder(node->right);
	if (node == nullptr) return;
	cout << node->data << " ";
}


int Rc_height(Node *node){
	if(node == NULL) return 0;
	int l = Rc_height(node->left);
	int r = Rc_height(node->right);
	return max(l,r)+1;
}

int Iter_height(Node* r) {
    if (r == nullptr) return 0;
    int height = 0;
    Node* current = r;
    while (true) {
        int levelNodes = 0;
        Node* tmp = current;
        while (tmp != nullptr) {
            if (tmp->left != nullptr) levelNodes++;
            if (tmp->right != nullptr) levelNodes++;
            if( tmp->left != nullptr){
				tmp = tmp->left;
			}
			else{
				tmp = tmp->right;
			}
        }
        if (levelNodes == 0) break;
        height++;
        if( current->left != nullptr){
			current = current->left;
		}
		else{
			current = current->right;
		}
    }
    return height + 1; 
}

bool isBST( Node *node , int max = INT_MAX , int min = INT_MIN){
	if( node == nullptr) return true;
	if( node->data > max || node->data < min) return false;
	isBST( node->right , node->data, min) && isBST( node->left , max , node->data);
}