#include <iostream>
#include <climits>

struct Node {
    int data;
    int weight = 0;
    node* right;
    node* left;
    node(int v) {
        data = v;
        right = nullptr;
        left = nullptr;
    }
};

Node* Rc_Insert( Node* r , int k){
    if(r == NULL){
        return new Node(k);
    }
    if(r->data == k){
        return r;
    }
    if( r->data > k){
        r->left = Rc_insert( r->left , k );
    }
    else{
        r->right = Rc_insert( r->right , k );
    }
    
    return r;
}

Node* It_Insert(Node* r, int val){
	Node* father{nullptr};
	Node* current{r};
	bool lor;
	while(current != nullptr){
		if(val < r->data){
			father = current;
			current = current->left;
			lor = true;
		}
		else if(val > current->data){
			father = current;
			current = current->right;
			lor = false;
		}
	}
	if(lor){
		father->left = new Node(val);
	}else if(!lor){
		father->right = new Node(val);
	}
	return r;
}

bool Rc_search(Node* r, int v) {
    if (r == nullptr) {
        return false;
    }
    if (v == r->data) {
        return true;
    }
    if (v < r->data) {
        return Rc_search(r->left, v);
    }
    return Rc_search(r->right, v);
}

bool It_search(Node* r, int v) {
    while (r != nullptr) {
        if (v == r->data) {
            return true;
        } else if (v < r->data) {
            r = r->left;
        } else {
            r = r->right;
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
void inOrder(Node* node) {
	inOrder(node->left);
	if (node == nullptr) return;
	cout << node->data << " ";
	inOrder(node->right);
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