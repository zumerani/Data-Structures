//
//  binary.cpp
//  Binary Tree Implementation
//
//  Created by Zain Umerani on 3/5/16.
//  Copyright (c) 2016 Zain Umerani. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <iomanip>
#include <vector>

using namespace std;

template <class Data>
class BinaryTree {
    
    protected:
        class BNode {
            private:
                Data data;
                BNode* left;
                BNode* right;
                
            public:
                BNode( BNode* left , BNode* right, Data data ) {
                    this->left = left;
                    this->right = right;
                    this->data = data;
                }
                
                BNode*& getLeft() {
                    return this->left;
                }
                
                BNode*& getRight() {
                    return this->right;
                }
                
                Data& getData() {
                    return this->data;
                }
                
                static void tree_clear( BNode* root ) {
                    if( root == NULL )
                        return;
                    
                    tree_clear( root->getLeft() );
                    tree_clear( root->getRight() );
                    
                    delete root;
                    
                }
        }; //End of 'BNode' class
        
        BNode* root;
        BNode* current;
        size_t size;
    
        /* Constant Member Functions to find height and size */
        size_t getSizeRecursively( BNode* root ) const;
        size_t getHeight( BNode* root ) const;
        void print(BNode* node_ptr, size_t depth) const
        // Library facilities used: iomanip, iostream, stdlib
        {
            if (node_ptr != NULL)
            {
                print(node_ptr->getRight(), depth+1);
                std::cout << std::setw(4*depth) << ""; // Indent 4*depth spaces.
                std::cout << node_ptr->getData() << std::endl;
                print(node_ptr->getLeft() ,  depth+1);
            }
        }
    
    public:
        //Constructors
        BinaryTree( Data data );
        BinaryTree( Data data , BNode* left , BNode* right );
        
        //Copy Constructor
        BinaryTree( const BinaryTree& other );
        
        //Deconstructor
        ~BinaryTree();
        
        //Assignment Operator
        BinaryTree& operator = ( const BinaryTree& other );
        
        //Modification Member Functions
        BNode* copy( BNode* root );
        void shift_to_root(); //done
        void shiftUp();
        void shiftLeft(); //done
        void shiftRight(); //done
        void change( const Data data ); //done
        void addLeft( const Data data ); //done
        void addRight( const Data data ); //done
        
        //Constant Member Functions
        void printTree();
        size_t height() const;
        size_t getSize() const; //done
        bool has_left() const; //done
        bool has_right() const; //done
        Data retrieve() const; //done
        bool hasParent() const; //done

};

/* ------------------ Implementation for Binary Tree ------------------ */

//Constructors
template <class Data>
BinaryTree<Data>::BinaryTree( Data data ) {
    this->root = new BNode( NULL , NULL , data );
    this->current = root;
    this->size = this->size + 1;
}

template <class Data>
BinaryTree<Data>::BinaryTree( Data data , BNode* left , BNode* right ) {
    this->root = new BNode( left , right , data );
    this->current = root;
    this->size = this->size + 1;
}

//Copy Constructor
template <class Data>
BinaryTree<Data>::BinaryTree( const BinaryTree& other ) {
    this->root = copy( other.root );
    this->current = root;
}

//Destructor
template <class Data>
BinaryTree<Data>::~BinaryTree() {
    BNode::tree_clear( this->root );
    this->size = 0;
}

//Assignment Operator
template <class Data>
BinaryTree<Data>& BinaryTree<Data>::operator = ( const BinaryTree& other ) {
    if( this == &other )
        return *this;
    
    BNode::tree_clear( this->root );
    
    if( other.getSize() == 0 ) {
        this->size = 0;
        this->root = NULL;
        this->current = NULL;
        return *this;
    }
    
    /* There are some nodes in 'other' */
    this->root = copy( other.root );
    this->size = other.size;
    this->current = this->root;
    
    return *this;
    
}



//Modification Member Functions
template <class Data>
typename BinaryTree<Data>::BNode* BinaryTree<Data>::copy( BNode* root ) {
    if( root == NULL )
        return NULL;
    
    return new BNode( copy( root->getLeft() ) , copy( root->getRight() ) , root->getData() );
}

template <class Data>
void BinaryTree<Data>::shift_to_root() {
    if( this-size > 0 )
        this->current = this->root;
    else
        cout << "There is nothing in the tree." << endl;
}

template <class Data>
void BinaryTree<Data>::shiftLeft() {
    if( has_left() )
        this->current = this->current->getLeft();
    else
        cout << "There is nothing in the tree." << endl;
}

template <class Data>
void BinaryTree<Data>::shiftRight() {
    if( has_right() )
        this->current = this->current->getRight();
    else
        cout << "There is nothing in the tree." << endl;
}

template <class Data>
void BinaryTree<Data>::change( const Data data ) {
    if( this->size > 0 )
        this->current->getData() = data;
    else
        cout << "There is nothing in the tree." << endl;
}

template <class Data>
void BinaryTree<Data>::addLeft( const Data data ) {
    if( this->size > 0 && !has_left() ) {
        BNode* temp = new BNode( NULL , NULL , data );
        this->current->getLeft() = temp;
        this->size = this->size + 1;
    }
}

template <class Data>
void BinaryTree<Data>::addRight( const Data data ) {
    if( this->size > 0 && !has_right() ) {
        BNode* temp = new BNode( NULL , NULL , data );
        this->current->getRight() = temp;
        this->size = this->size + 1;
    }
}

//Constant Member Functions
template <class Data>
void BinaryTree<Data>::printTree() {
    print( this->root , 0 );
}

template <class Data>
size_t BinaryTree<Data>::getHeight( BNode* root ) const {
    if( root == NULL )
        return -1;
    
    return 1 + std::max( getHeight( root->getLeft() ) , getHeight( root->getRight() ) );
    
}

template <class Data>
size_t BinaryTree<Data>::height() const {
    return getHeight( this->root );
}

template <class Data>
size_t BinaryTree<Data>::getSizeRecursively( BNode* root ) const {
    if( root == NULL )
        return 0;
    
    return 1 + getSizeRecursively( root->getLeft() ) + getSizeRecursively( root->getRight() );
    
}

template <class Data>
size_t BinaryTree<Data>::getSize() const {
    return getSizeRecursively(this->root);
}

template <class Data>
bool BinaryTree<Data>::has_left() const {
    if( this->current->getLeft() )
        return true;
    
    return false;
    
}

template <class Data>
bool BinaryTree<Data>::has_right() const {
    if( this->current->getRight() )
        return true;
    
    return false;
}

template <class Data>
Data BinaryTree<Data>::retrieve() const {
    return this->current->getData();
}

template <class Data>
bool BinaryTree<Data>::hasParent() const {
    if( this->current != this->root )
        return true;
}
    
/* ------------------ End of Implementation ------------------ */




/* -------------------------------------------------------------------------------------------------------*/





template <class Data>
class BST : public BinaryTree<Data> {
    
    private:
        void insertInTree( typename BinaryTree<Data>::BNode*& root , Data data );
        void removeFromTree( typename BinaryTree<Data>::BNode*& root , Data data );
        Data findMin( typename BinaryTree<Data>::BNode* root ) const;
        Data getSizeP( typename BinaryTree<Data>::BNode* root ) const;
        Data getHeightP( typename BinaryTree<Data>::BNode* root ) const;
        
        
    public:
        //Constructor
        BST(Data data) : BinaryTree<Data>(data) { }
        
        //Destructor
        ~BST() { }
        
        //Copy Constructor
        BST( const BST& other ) : BinaryTree<Data>( other ) { }
        
        //Assignment Operator
        BST& operator = ( const BST& other ) {
            BinaryTree<Data>::operator = ( other );
            return *this;
        }
        
        //Modification Member Functions
        void insert( Data x );
        void remove( Data data );
        
        //Constant Member Functions
        Data findMinimum( typename BinaryTree<Data>::BNode* root ) const;
        Data getSize() const;
        Data getHeight() const;
    
    
};

/* ------------------ Implementation of BST ------------------ */

//Modification Member Functions

//private functions
template <class Data>
void BST<Data>::insertInTree(typename BinaryTree<Data>::BNode*& r, Data data) {
    if( r == NULL ) {
        r = new typename BinaryTree<Data>::BNode( NULL , NULL , data );
        this->size = this->size + 1;
    }
    else if( data < r->getData() )
        insertInTree( r->getLeft() , data );
    else
        insertInTree( r->getRight() , data );
}

template <class Data>
void BST<Data>::removeFromTree( typename BinaryTree<Data>::BNode *&r , Data data ) {
    if( r == NULL )
        return;
    
    if( r->getData() == data && ( r->getLeft() && r->getRight() ) ) {
        Data x = findMinimum( r->getRight() );
        r->getData() = x;
        removeFromTree( r->getRight() , x );
    } else if( r->getData() == data && ( r->getLeft() && r->getRight() == NULL ) ) {
        typename BinaryTree<Data>::BNode* temp = r;
        r = r->getLeft();
        delete temp;
    } else if( r->getData() == data && ( r->getLeft() == NULL && r->getRight() ) ) {
        typename BinaryTree<Data>::BNode* temp = r;
        r = r->getRight();
        delete temp;
    } else if( r->getData() == data ) { // no children
        delete r;
        r = NULL;
    } else if( data < r->getData() ) {
        removeFromTree( r->getLeft() , data );
    } else {
        removeFromTree( r->getRight() , data );
    }
    
}

template <class Data>
Data BST<Data>::findMin( typename BinaryTree<Data>::BNode* r ) const {
    while( r->getLeft() != NULL )
        r = r->getLeft();
    
    return r->getData();
}

template <class Data>
Data BST<Data>::getSizeP( typename BinaryTree<Data>::BNode* r ) const {
    if( r == NULL )
        return 0;
    else
        return 1 + getSizeP( r->getLeft() ) + getSizeP( r->getRight() );
}

template <class Data>
Data BST<Data>::getHeightP( typename BinaryTree<Data>::BNode* r ) const {
    if( r == NULL )
        return -1;
    else
        return 1 + std::max( getHeightP( r->getLeft() ) , getHeightP( r->getRight() ) );
}


//public functions
template <class Data>
void BST<Data>::insert( Data x ) {
    insertInTree( this->root , x );
}

template <class Data>
void BST<Data>::remove( Data data ) {
    removeFromTree( this->root , data );
}

template <class Data>
Data BST<Data>::findMinimum( typename BinaryTree<Data>::BNode* r ) const {
    return findMin( r );
}

template <class Data>
Data BST<Data>::getSize() const {
    return getSizeP( this->root );
}

template <class Data>
Data BST<Data>::getHeight() const {
    return getHeightP( this->root );
}


int main(int argc, const char * argv[]) {
    
    /* ------ Binary Tree Stuff ------ */
    
//    BinaryTree<int> b1(1);
//    BinaryTree<int> b2(4);
//    
//    b1.addLeft(2);
//    b1.addRight(3);
//    b1.shiftRight();
//    b1.addLeft(6);
//    b1.shift_to_root();
//    b1.shiftLeft();
//    b1.addLeft(14);
//    b1.addRight(15);
//    
//    b1.printTree();
//    
//    b1 = b2;
    
    
    
    /* ------ BST Stuff ------ */
    BST<int> b1(18);
    
//    b1.insert(15);
//    b1.insert(30);
//    b1.insert(10);
//    b1.insert(13);
//    
//    b1.printTree();
//    
//    b1.remove(20);
//    
//    cout << endl << endl << endl;
//    
//    b1.printTree();
//    
//    b1.remove(15);
//    
//    cout << endl << endl << endl;
//    
//    b1.printTree();
//    
//    cout << endl << endl << "the size of 'b1' is: " << b1.getSize() << endl;
//    
//    cout << endl << endl << "the height of 'b1' is: " << b1.getHeight() << endl;
    
    b1.insert(16);
    b1.insert(15);
    b1.insert(20);
    b1.insert(25);
    
    b1.printTree();
    
    b1.remove(18);
    
    cout << endl << endl;
    
    b1.printTree();
    
    vector< vector< int > > v1(10);
    
    
}












