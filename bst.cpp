// Necessary Libraries
#include "bst.h"
#include "dna.h"
#include <iostream>
#include <string>
#include <stdexcept>

/*
---------------------------------------------------------
Default Constructor: sets the left & right children to null
& sets content to a new type pointer
---------------------------------------------------------
*/
template <typename T>
BST<T>::BST() {
	/*
	slightly ugly: because we don't have a parameter of type T,
	we have to call new and dereference the pointer.
	Other constructors should NOT do this.
	*/
	this->content = *(new T);
	this->left = nullptr;
	this->right = nullptr;
}

/*
---------------------------------------------------------
Default Destructor: Traverses any subtrees
---------------------------------------------------------
*/
template <typename T>
BST<T>::~BST() {
	// Recursively call delete on left and right subtrees.
	if (this->left != nullptr) delete(this->left);
	if (this->right != nullptr) delete(this->right);
}

/*
---------------------------------------------------------
Single Instance Constructor: Sets content to the argument content
& the left and right children to nullptr like before
---------------------------------------------------------
*/
template <typename T>
BST<T>::BST(T content){
	// setting content to content
	this->content = content;
	// setting left & right children to nullptr like above
	this->left = nullptr; 
	this->right = nullptr;
}

/*
---------------------------------------------------------
Vector constructor: Given a vector<T> and a comparator function, 
inserts every element of the vector into a BST. The comparator 
is used to determine a "less-than" relationship.
The BST object returned by this constructor is the
root of the binary search tree.
---------------------------------------------------------
*/
template <typename T>
BST<T>::BST(std::vector<T> contents, bool comparator(T&, T&)){
	// setting the pointers to null
	this->left = nullptr;
	this->right = nullptr;
	// calls the insert constructor to the current BST object
	for(unsigned long i = 0; i <= contents.size()-1; i++){ 
		this->insert(contents[i], comparator); 
	}
}

/*
---------------------------------------------------------
Getter for the content field
---------------------------------------------------------
*/
template <typename T>
T BST<T>::getContent() {
	return this->content;
}

/*
---------------------------------------------------------
Performs a binary search on the BST, given a comparator function.
Returns the content of the BST node if a match is found.
Throws a std::runtime_error if no matching item can be found.
This uses a notion of equality based on the "less-than" comparator:
(a == b) if and only if !(a<b) && !(b<a)
---------------------------------------------------------
*/
template <typename T>
T BST<T>::find(T query, bool comparator(T&, T&)) {
	// "less-than" comparator using a notion of equality
	if(!comparator(query, this->content) && !comparator(this->content, query)) {
		return this->content;
	}		
	// if "less-than" comparator does not run
// start of else loop for left node if less than content
	else if (comparator(query, this->content)) { 
		// matching item on left cannot be found
		if (this->left == nullptr) { 
			throw std::runtime_error("Does not exist");
		}
		else { 
			// returns content of left BST node
  			return this->left->find(query, comparator);			
  		}
  	}
// end of else loop for left node

// start of else loop for right node if greater than content
		else { 
			// matching item on right cannot be found
			if (this->right == nullptr) { 
			throw std::runtime_error("Does not exist");
		} 			
		else {
			// returns content of right BST node
			return this->right->find(query, comparator);
		}
	}
}

/*
---------------------------------------------------------
Inserts element x, of type T, into the BST. This preserves 
the BST invariant: a left child is always less than its 
parent, while a right child is always not less than its parent.
This relies on the "less-than" comparator.
---------------------------------------------------------
*/
template <typename T>
void BST<T>::insert(T x, bool comparator(T&, T&)){
	// inserts element x into left BST
	if (comparator(x, this->content)) { 
		// searches BST until nullptr is found
  		if (this->left != nullptr) { 
     		this->left->insert(x, comparator);
	 	}
    	else {
    		// when it is null, insert x there 
      		this->left = new BST<T>(x);
    	}
  	}	
  	else {
  		// searches BST until nullptr is found
    	if (this->right != nullptr){ 
      	this->right->insert(x, comparator); 
	}
    	else { 
    		// when it is null, insert x there
      		this->right = new BST<T>(x);
    	}
  	}
}

/*
---------------------------------------------------------
Instantiate this template class for four types.
This is to allow the separation between interface and implementation.
---------------------------------------------------------
*/
template class BST<int>;
template class BST<double>;
template class BST<std::string>;
template class BST<DNA>;