//Rishi Govindan
//rigovind
//pa8


#include "Dictionary.h"

#define black 0
#define red 1

Dictionary::Node::Node(keyType k, valType v) : key(k), val(v), parent(nullptr), left(nullptr), right(nullptr),
                                               color(black) {
}

Dictionary::Dictionary() {
    	nil = new Node("", 0);
    	nil->left = nil;
    	nil->right = nil;
    	nil->parent = nil;
    	root = nil;
    	current = nil;
    	num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary&D) {
    	nil = new Node("", 0);
    	nil->color = black; // Ensure nil nodes are black
    	root = nil;
    	current = nil;
    	num_pairs = 0;
    	preOrderCopy(D.root, D.nil); // Start copying from the root of D
}

Dictionary::~Dictionary() {
    	postOrderDelete(root);
    	delete nil;
}

void Dictionary::inOrderString(std::string&s, Node* R) const {
    	if (R != nil) {
        	inOrderString(s, R->left);
        	s += R->key + " : " + std::to_string(R->val) + "\n";
        	inOrderString(s, R->right);
    	}
}

void Dictionary::preOrderString(std::string&s, Node* R) const {
    	if (R != nil) {
        	s += R->key;
        	s += (R->color == red) ? " (RED)\n" : "\n";
        	preOrderString(s, R->left);
        	preOrderString(s, R->right);
    	}
}

void Dictionary::BST_insert(Node* M) {
    	if (M == nil) {
        	return;
    	}

	Node* parentNode = nil;
    	Node* searchNode = root;

	Node* newNode = new Node(M->key, M->val);
    	newNode->color = M->color;
	newNode->left = nil;
    	newNode->right = nil;

	while (searchNode != nil) {
		parentNode = searchNode;
        	if (newNode->key < searchNode->key) {
			searchNode = searchNode->left;
		}
		else{
			searchNode = searchNode->right;
		}
	}

	newNode->parent = parentNode;

	if (parentNode == nil) {
        	root = newNode;
    	}
	else if(newNode->key < parentNode->key) {
		parentNode->left = newNode;
	}
	else{
		 parentNode->right = newNode;
	}

	num_pairs++;
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
	if (R->key == N->key) {
        	return;
    	}

	BST_insert(R);
    	preOrderCopy(R->left, N);
    	preOrderCopy(R->right, N);
}

void Dictionary::postOrderDelete(Node* R) {
    	if (R != nil) {
        	postOrderDelete(R->left);
        	postOrderDelete(R->right);
        	delete R;
    	}
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    	Node* current = R;
    	while (current != nil) {
        	if (k == current->key) return current;
        		current = (k < current->key) ? current->left : current->right;
    	}
    	return nil;
}

Dictionary::Node* Dictionary::findMin(Node* R) {
	if (R != nil) {
        	while (R->left != nil) {
            		R = R->left;
        	}
    	}
    	return R;
}

Dictionary::Node* Dictionary::findMax(Node* R) {
    	if (R != nil) {
        	while (R->right != nil) {
            		R = R->right;
        	}
    	}
    	return R;
}

Dictionary::Node* Dictionary::findNext(Node* N) {
    	if (N == nil) {
        	return nil;
    	}

	if (N->right != nil) {
        	return findMin(N->right);
    	}

	Node* parentN = N->parent;
    	while (parentN != nil && N == parentN->right) {
        	N = parentN;
        	parentN = parentN->parent;
    	}
    	return parentN;
}

Dictionary::Node* Dictionary::findPrev(Node* N) {
    	if (N == nil) {
        	return nil;
    	}

	if (N->left != nil) {
        	return findMax(N->left);
    	}

	Node* parentN = N->parent;
    	while (parentN != nil && N == parentN->left) {
        	N = parentN;
        	parentN = parentN->parent;
    	}
    	return parentN;
}

void Dictionary::LeftRotate(Node* x) {
    	Node* y = x->right;
    	x->right = y->left;
    	if (y->left != nil){
		y->left->parent = x;
	}
    	y->parent = x->parent;
    	if (x->parent == nil){
		root = y;
	}
    	else if(x == x->parent->left){
		x->parent->left = y;
	}
    	else{
		x->parent->right = y;
	}
    	y->left = x;
    	x->parent = y;
}

void Dictionary::RightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != nil) x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == nil) root = x;
    else if (y == y->parent->right) y->parent->right = x;
    else y->parent->left = x;
    x->right = y;
    y->parent = x;
}

void Dictionary::RB_InsertFixUp(Node* z) {
    	while (z->parent->color == red) {
        	if (z->parent == z->parent->parent->left) {
            		Node* y = z->parent->parent->right;
            		if (y->color == red) {
                		z->parent->color = black;
                		y->color = black;
                		z->parent->parent->color = red;
                		z = z->parent->parent;
            		}
			else {
                		if (z == z->parent->right) {
                    			z = z->parent;
                    			LeftRotate(z);
                		}
                		z->parent->color = black;
                		z->parent->parent->color = red;
                		RightRotate(z->parent->parent);
            		}
        	}
		else{
			Node* y = z->parent->parent->left;
            		if (y->color == red) {
                		z->parent->color = black;
                		y->color = black;
                		z->parent->parent->color = red;
                		z = z->parent->parent;
            		}
			else{
				if (z == z->parent->left) {
                    			z = z->parent;
                    			RightRotate(z);
                		}
                		z->parent->color = black;
                		z->parent->parent->color = red;
                		LeftRotate(z->parent->parent);

			}
		}
	}
	root->color = black;
}

void Dictionary::RB_Transplant(Node* u, Node* v) {
    	if (u->parent == nil) root = v;
    	else if (u == u->parent->left) u->parent->left = v;
    	else u->parent->right = v;
    	v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N) {
	while (N != root && N->color == black) {
        	if (N == N->parent->left) {
            		Node* sibling = N->parent->right;
            		if (sibling->color == red) {
                		sibling->color = black;
                		N->parent->color = red;
                		LeftRotate(N->parent);
                		sibling = N->parent->right;
            		}

			if (sibling->left->color == black && sibling->right->color == black) {
                		sibling->color = red;
                		N = N->parent;
            		}

			else{
				if (sibling->right->color == black) {
                    			sibling->left->color = black;
                    			sibling->color = red;
                    			RightRotate(sibling);
                    			sibling = N->parent->right;
                		}

				sibling->color = N->parent->color;
                		N->parent->color = black;
                		sibling->right->color = black;
                		LeftRotate(N->parent);
                		N = root;
			}
		}
		else{
			Node* sibling = N->parent->left;
            		if (sibling->color == red) {
                		sibling->color = black;
                		N->parent->color = red;
                		RightRotate(N->parent);
                		sibling = N->parent->left;
            		}
			if (sibling->right->color == black && sibling->left->color == black) {
                		sibling->color = red;
                		N = N->parent;
            		}
			else{
				if (sibling->left->color == black) {
                    			sibling->right->color = black;
                    			sibling->color = red;
                    			LeftRotate(sibling);
                    			sibling = N->parent->left;
                		}
				sibling->color = N->parent->color;
                		N->parent->color = black;
                		sibling->left->color = black;
                		RightRotate(N->parent);
                		N = root;
			}
		}
	}
	N->color=black;
}

void Dictionary::RB_Delete(Node* N) {
    	Node* y = N;
    	Node* x = nil;
    	int y_original_color = y->color;
    	if (N->left == nil) {
        	x = N->right;
        	RB_Transplant(N, N->right);
    	}
	else if (N->right == nil) {
        	x = N->left;
        	RB_Transplant(N, N->left);
    	}
    	else {
        	y = findMin(N->right);
        	y_original_color = y->color;
        	x = y->right;
        	if (y->parent == N) {
            		x->parent = y;
        	}
		else {
            		RB_Transplant(y, y->right);
            		y->right = N->right;
            		y->right->parent = y;
        	}
        	RB_Transplant(N, y);
        	y->left = N->left;
        	y->left->parent = y;
        	y->color = N->color;
    	}
	if (y_original_color == black) {
        	RB_DeleteFixUp(x);
    	}
}

int Dictionary::size() const {
    	return num_pairs;
}

bool Dictionary::contains(keyType k) const {
    	return search(root, k) != nil;
}

valType& Dictionary::getValue(keyType k) const {
    	Node* N = search(root, k);
    	if (N == nil) {
        	throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    	}
    	return N->val;
}

bool Dictionary::hasCurrent() const {
    	return current != nil;
}

keyType Dictionary::currentKey() const {
    	if (current == nil) {
        	throw std::logic_error("Dictionary: currentKey(): current undefined");
    	}
    	return current->key;
}

valType& Dictionary::currentVal() const {
    	if (current == nil) {
        	throw std::logic_error("Dictionary: currentVal(): current undefined");
    	}
    	return current->val;
}

void Dictionary::clear() {
    	postOrderDelete(root);
    	root = nil;
    	current = nil;
    	num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
    	Node* parentNode = nil;
    	Node* searchNode = root;

	while (searchNode != nil) {
        	parentNode = searchNode;
        	if (k == searchNode->key) {
            		if (searchNode->val != v) {
                		searchNode->val = v;
            		}
            		return; // Key exists, value updated if different, then exit
        	}
        	searchNode = (k < searchNode->key) ? searchNode->left : searchNode->right;
    	}
	Node* newNode = new Node(k, v);
    	newNode->parent = parentNode;
    	if (parentNode == nil) {
        	root = newNode;
    	}
    	else if (k < parentNode->key) {
        	parentNode->left = newNode;
    	}
    	else {
        	parentNode->right = newNode;
    	}
    	newNode->left = newNode->right = nil;
    	newNode->color = red;
    	RB_InsertFixUp(newNode);
    	num_pairs++;
}

void Dictionary::remove(keyType k) {
    	Node* z = search(root, k);
    	if (z == nil) {
    		throw std::invalid_argument("Dictionary: remove(): key \"" + k + "\" does not exist");
    	}
	Node* y = z;
	Node* x;
	int originalColor = y->color;

	if (z->left == nil) {
        	x = z->right;
        	RB_Transplant(z, z->right);
    	}
    	else if (z->right == nil) {
        	x = z->left;
        	RB_Transplant(z, z->left);
    	}
    	else {
        	y = findMin(z->right);
        	originalColor = y->color;
        	x = y->right;
        	if (y->parent == z) {
            		x->parent = y;
        	}
        	else {
            		RB_Transplant(y, y->right);
            		y->right = z->right;
            		y->right->parent = y;
        	}
        	RB_Transplant(z, y);
        	y->left = z->left;
        	y->left->parent = y;
        	y->color = z->color;
    	}
	if (current == z) {
        	current = nil;
	}

	delete z;
    	if (originalColor == black) {
        	RB_DeleteFixUp(x);
    	}

    	num_pairs--;
}

void Dictionary::begin() {
    	current = findMin(root);
}

void Dictionary::end() {
    	current = findMax(root);
}

void Dictionary::next() {
	if (current != nil) {
        	current = findNext(current);
    	}
    	else {
        	throw std::logic_error("Dictionary: next(): current undefined");
    	}
}

void Dictionary::prev() {
    	if (current != nil) {
        	current = findPrev(current);
    	}
    	else {
        	throw std::logic_error("Dictionary: prev(): current undefined");
    	}
}

std::string Dictionary::to_string() const {
    	std::string s;
    	inOrderString(s, root);
    	return s;
}

std::string Dictionary::pre_string() const {
    	std::string s;
    	preOrderString(s, root);
    	return s;
}

bool Dictionary::equals(const Dictionary&D) const {
    	return to_string() == D.to_string();
}

std::ostream& operator<<(std::ostream&stream, Dictionary&D) {
    	return stream << D.to_string();
}

bool operator==(const Dictionary&A, const Dictionary&B) {
    	return A.equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary&D) {
    	if (this != &D) {
        	clear();
        	preOrderCopy(D.root, nil);
    	}
    	return *this;
}




		






