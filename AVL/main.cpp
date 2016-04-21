#include <iostream>
#include <algorithm> // std::max
#include <math.h>
#include <iomanip>

struct Node {
    int data;
    Node* left;
    Node* right;
};

class Tree {
public:
    Tree() : root_(nullptr) { }
    
    int GetHeight(Node* root);
    int Diff(Node* root);
    Node* RightRight_Rotation(Node*& root);
    Node* LeftLeft_Rotation(Node*& root);
    Node* LeftRight_Rotation(Node*& root);
    Node* RightLeft_Rotation(Node*& root);
    void Balance(Node*& root);
    void Insert(Node*& root, int value);
    void Display(Node* root, int level);
    void Inorder(Node* root);
    void Preorder(Node* root);
    void Postorder(Node* root);
    
    Node*& root() { return this->root_; }
    
private:
    Node* root_;
};


int Tree::GetHeight(Node *temp) {
    int h = 0;
    if (temp) {
        int l_GetHeight = GetHeight(temp->left);
        int r_GetHeight = GetHeight(temp->right);
        int max_GetHeight = std::max(l_GetHeight, r_GetHeight);
        h = max_GetHeight + 1;
    }
    
    return h;
}


int Tree::Diff(Node* temp) {
    int l_GetHeight = GetHeight(temp->left);
    int r_GetHeight = GetHeight(temp->right);
    int b_factor = (l_GetHeight - r_GetHeight);
    return b_factor;
}

Node* Tree::RightRight_Rotation(Node*& parent) {
    Node* temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

Node* Tree::LeftLeft_Rotation(Node*& parent) {
    Node* temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

Node* Tree::LeftRight_Rotation(Node*& parent) {
    //Node* temp = parent->left;
    parent->left = RightRight_Rotation(parent->left);
    return LeftLeft_Rotation(parent);
}

Node* Tree::RightLeft_Rotation(Node*& parent) {
    Node* temp = parent->right;
    parent->right = LeftLeft_Rotation(temp);
    return RightRight_Rotation(parent);
}

void Tree::Balance(Node*& temp) {
    int balanceFactor = Diff(temp);
    
    if (balanceFactor > 1) {
        if (Diff (temp->left) > 0) {
            temp = LeftLeft_Rotation(temp);
        } else {
            temp = LeftRight_Rotation(temp);
        }
    } else if (balanceFactor < -1) {
        if (Diff(temp->right) > 0) {
            temp = RightLeft_Rotation(temp);
        } else {
            temp = RightRight_Rotation(temp);
        }
    }
    
    //return temp;
}

void Tree::Insert(Node*& root, int value) {
    if (!root) {
        root = new Node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
    } else if (value < root->data) {
        Insert(root->left, value);
        Balance(root);
    } else if (value >= root->data) {
        Insert(root->right, value);
        Balance(root);
    }
    
    //return root;
}

void Tree::Display(Node* current, int level) {
    if (current != NULL)
    {
        Display(current->right, level+1);
        std::cout << std::setw(4*level) << ""; // Indent 4*depth spaces.
        std::cout << current->data << std::endl;
        Display(current->left ,  level+1);
    }
}

void Tree::Inorder(Node* root) {
    if (!root) {
        return;
    }
    
    Inorder(root->left);
    std::cout << root->data<< "      ";
    Inorder(root->right);
}

void Tree::Preorder(Node* root) {
    if (!root) return;
    
    std::cout << root->data << "  ";
    Preorder(root->left);
    Preorder(root->right);
}

void Tree::Postorder(Node* root) {
    if (!root) return;
    
    Postorder(root->left);
    Postorder(root->right);
    std::cout<<root->data<<"  ";
}

/**
 *  * Prompts user for input selection using stdin.
 *   */
int main() {
    int choice = 0, item = 0;
    Tree avl;
    
    while(1) {
        std::cout << "Enter your choice: " << std::endl;
        std::cout << "1: Insert a value" << std::endl;
        std::cout << "2: Display balanced AVL Tree" << std::endl;
        std::cout << "3: Print Inorder traversal" << std::endl;
        std::cout << "4: Print Preorder traversal" << std::endl;
        std::cout << "5: Print Postorder traversal" << std::endl;
        std::cout << "6: Exit" << std::endl;
        std::cin >> choice;
        switch(choice) {
            case 1:
                std::cout << "Enter value to be Inserted: ";
                std::cin >> item;
                avl.Insert(avl.root(), item);
                break;
            case 2:
                if (!avl.root()) {
                    std::cout << "Tree is empty!" << std::endl;
                    continue;
                }
                std::cout << "Balanced AVL Tree:" <<std::endl;
                avl.Display(avl.root(), 0);
                break;
                
            case 3:
                std::cout << "Inorder:" << std::endl;
                avl.Inorder(avl.root());
                std::cout << std::endl;
                break;
                
            case 4:
                std::cout << "Preorder: " << std::endl;
                avl.Preorder(avl.root());
                std::cout << std::endl;
                break;
                
            case 5:
                std::cout << "Postorder: " << std::endl;
                avl.Inorder(avl.root());
                std::cout << std::endl;    
                break;
                
            case 6: 
                exit(1);
                break;
                
            default:
                std::cout << "Wrong choice" << std::endl;
        }
    }
    
    return 0;
}
