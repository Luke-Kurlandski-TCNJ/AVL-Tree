#include <iostream>
#include <string>
#include "AVLTree.h"
#include <iomanip>
#include <queue>
using namespace std;

AVLTree::AVLTree(){
    root = nullptr;
}

AVLTree::~AVLTree(){
    

}

AVLNode* AVLTree::getRoot(){
    return root;
}


// search value ss in the AVL tree
bool AVLTree::find(string ss){
    if (root == nullptr) {
        return false;
    }
    
    AVLNode* node = root;
    
    while (node != nullptr) {
        if (ss.compare(node->ssn) == 0) {
            return true;
        }
        if (ss.compare(node->ssn) < 0) {
            node = node->left;
        }
        else{
            node = node->right;
        }
    }
    return false;
}

// return the height of the subtree rooted at node
// if subtree is empty, height is -1
// if subtree has one node, height is 0
int AVLTree::height(AVLNode* node){
    
    if(node != nullptr){
        return node->height;
    }
    else{
        return -1;
    }
}

// return the balance factor of the node
int AVLTree::balanceFactor(AVLNode* node){
    return height(node->left) - height(node->right);
}

// update the height of the node
// this should be done whenever the tree is modified
void AVLTree::updateHeight(AVLNode* node){
    int hl = height(node->left);
    int hr = height(node->right);
    node->height = (hl>hr ? hl : hr) + 1;
}


// rotate right the subtree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::rotateRight(AVLNode* node){
    AVLNode* lp = node->left;      // left child of node
    if (node->parent!=nullptr) {  // node is not root
        if (node->parent->left == node) { // node is a left child
            node->parent->left = lp;
        }else{
            node->parent->right = lp;     // node is a right child
        }
    }

    if (lp->right != nullptr) {           // pointer update
        lp->right->parent = node;
    }
    
    lp->parent = node->parent;
    node->left = lp->right;
    lp->right = node;
    node->parent = lp;
    updateHeight(node);                   // after rotation, update height
    updateHeight(lp);                     // after rotation, update height
    if (node == root) {
        root = lp;
    }
    return lp; // lp is the new root of the subtree
}


// rotate left the subtree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::rotateLeft(AVLNode* node){
    AVLNode* rp = node->right;
    if (node->parent!=nullptr) {
        if (node->parent->left == node) {
            node->parent->left = rp;
        }else{
            node->parent->right = rp;
        }
    }

    if (rp->left != nullptr) {
       rp->left->parent = node;
    }
    
    rp->parent = node->parent;
    
    node->right = rp->left;
    rp->left = node;
    node->parent = rp;
    node->parent = rp;
    updateHeight(node);
    updateHeight(rp);
    if (node == root) {
        root = rp;
    }
    return rp;
}


// rebalance a tree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::balance(AVLNode* node){
    updateHeight(node);
    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left); // for left right case
        }
        
        AVLNode* temp = rotateRight(node);
        updateHeight(temp);
        return temp;
    }
    
    if (balanceFactor(node) == -2) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);  // for right left case
        }
        AVLNode* temp2 = rotateLeft(node);
        updateHeight(temp2);
        return temp2;
    }
    return node;
}

// insert a new node with (ss, na) to the AVL tree
// if there exists ss value, return false
// otherwise, insert it, balance the tree, return true
bool AVLTree::insert(string ss, string na){
    // please implement here
    //cout << "insert called, ss/name: " << ss << "/" << na << endl;
    AVLNode *newNode = new AVLNode(ss, na);
    if(root == nullptr) {
        root = newNode;
        return true;
    }

    AVLNode *temp = root;
    int newNodeSSN = stoi(ss);
    int tempSSN;
    while(true) {
        //cout << temp->ssn << ": " << temp->height << endl;
        //sends node left
        tempSSN = stoi(temp->ssn);
        if(newNodeSSN < tempSSN) {
            if(temp->left == nullptr) {
                temp->left = newNode;
                newNode->parent = temp;
                //updates the height of all the parents
                AVLNode *temp2 = temp;
                while(temp2 != nullptr) {
                    updateHeight(temp2);
                    temp2 = temp2->parent;
                }
                //cout << "inserted element" << endl;
                //this->print();
                //rebalances grandparent and up
                while(temp != nullptr && temp->parent != nullptr) {
                    //cout << "rebalancing: " << temp->parent->ssn << endl;
                    balance(temp->parent);
                    temp = temp->parent;
                }
                //this->print();
                return true;
            }
            else {
                temp = temp->left;
                continue;
            }
        }
        //sends node right
        if(newNodeSSN > tempSSN) {
            if(temp->right == nullptr) {
                temp->right = newNode;
                newNode->parent = temp;
                //updates the height of all the parents
                AVLNode *temp2 = temp;
                while(temp2 != nullptr) {
                    updateHeight(temp2);
                    temp2 = temp2->parent;
                }
                //cout << "inserted element: " << newNode->ssn << endl;
                //this->print();
                //rebalances grandparent and up
                while(temp != nullptr && temp->parent != nullptr) {
                    //cout << "rebalancing: " << temp->parent->ssn << endl;
                    balance(temp->parent);
                    temp = temp->parent;
                }
                //this->print();
                return true;
            }
            else {
                temp = temp->right;
                continue;
            }
        }
        //handles a duplicate
        if(newNodeSSN == tempSSN) {
           //cout << "Duplicate found: " << newNode->ssn << endl; 
            delete newNode;
            return false;
        }
    }
    return false;
}


AVLNode* AVLTree::maxOfSubtree(AVLNode* node){
    if (node == nullptr) {
        return nullptr;
    }
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

// delete the node containing value ss
// if there is not such node, return false
// otherwise, delete the node, balance the tree, return true
bool AVLTree::deleteNode(string ss) {
    AVLNode *temp = root;
    int tempSSN;
    int searchSSN = stoi(ss);
    while(true) {
        //Traverses the Tree
        if(temp == nullptr) {
            return false;
        }
        else {
            tempSSN = stoi(temp->ssn);
        }
        if(searchSSN < tempSSN) {
            temp = temp->left;
            continue;
        }
        if(searchSSN > tempSSN) {
            temp = temp->right;
            continue;
        }
        //Otherwise, a match was found

        //Handle no child scenario
        if(temp->left == nullptr && temp->right == nullptr) {
            //Handle deleting the root
            if(temp->ssn == root->ssn) {
                //cout << "Deleted the root: " << root->ssn << " new root: none" << endl;
                root = nullptr;
                delete temp;
                return true;
            }

            //Non Root Deletion
            //cout << "Performing no-child deletion on node " << temp->ssn << endl;
            //Determines if temp is right/left child
            //Sets that link to null
            if(temp->parent->left != nullptr && temp->parent->left->ssn == temp->ssn) {
                temp->parent->left = nullptr;
            }
            if(temp->parent->right != nullptr && temp->parent->right->ssn == temp->ssn) {
                temp->parent->right = nullptr;
            }
            AVLNode *temp2 = temp->parent;
            delete temp;
            //Update height and balance
            while(temp2 != nullptr) {
                balance(temp2);
                temp2 = temp2->parent;
            }
            return true;
        }

        //Handle one child scenario
        if((temp->left == nullptr && temp->right != nullptr) || (temp->left != nullptr && temp->right == nullptr)) {
            //cout << "Performing child deletion on " << temp->ssn;
            //Find the child tree
            AVLNode *child;
            if(temp->left == nullptr && temp->right != nullptr) {
                child = temp->right;
                //cout << " has a right child" << endl;
            }
            if(temp->left != nullptr && temp->right == nullptr) {
                child = temp->left;
                //cout << " has a left child" << endl;
            }
            //Determines if temp is right/left child non-root only
            if(temp->ssn != root->ssn) {
                //Connect temp's parent to temp's child
                if(temp->parent->left != nullptr && temp->parent->left->ssn == temp->ssn) {
                    temp->parent->left = child;
                }
                if(temp->parent->right != nullptr && temp->parent->right->ssn == temp->ssn) {
                    temp->parent->right = child;
                }
            }
            child->parent = temp->parent;
            //Handles root situation
            if(temp->ssn == root->ssn) {
                //cout << "Deleted the root: " << root->ssn << " new root: " << child->ssn << endl;
                root = child;
            }
            delete temp;
            //Proceed with rebalancing
            AVLNode *temp2 = child;
            while(temp2 != nullptr) {
                balance(temp2);
                temp2 = temp2->parent;
            }
            return true;
        }

        //Handle the two child scenario
        if(temp->left != nullptr && temp->right != nullptr) {
            AVLNode *replace = maxOfSubtree(temp->left);
            //cout << "Performing two child deletion on node " << temp->ssn << endl;
            AVLNode *bottom = replace;

            //Handle replacement with immediate child
            if(replace->ssn == temp->left->ssn) {
                //cout << "Replacing with immediate child " << replace->ssn << endl;
                //Modify the replacement's location in tree
                replace->right = temp->right;
                replace->left = replace->left;
                replace->parent = temp->parent;
                temp->right->parent = replace;
                //Determine if temp is a left or right child for non-root only
                if(temp->ssn != root->ssn) {
                    //Modify temp's parent to point to replacement
                    if(temp->parent->left != nullptr && temp->parent->left->ssn == temp->ssn) {
                        temp->parent->left = replace;
                    }
                    if(temp->parent->right != nullptr && temp->parent->right->ssn == temp->ssn) {
                        temp->parent->right = replace;
                    }
                }
                //Handles root situation
                if(temp->ssn == root->ssn) {
                    //cout << "Deleted the root: " << root->ssn << " new root before balance: " << replace->ssn << endl;
                    root = replace;
                }
                delete temp;
                //Proceed with rebalancing
                while(bottom != nullptr) {
                    balance(bottom);
                    bottom = bottom->parent;
                }
                return true;
            }

            //Handle replacement with non-immediate child
            if(replace->ssn != temp->left->ssn) {
                //cout << "Replacing with non-immediate child " << replace->ssn << endl;
                //Modify what points to the replacement
                replace->parent->right = replace->left;
                if(replace->left != nullptr) {
                    replace->left->parent = replace->parent;
                }
                temp->left->parent = replace;
                temp->right->parent = replace;
                //Modify what the replacement points to
                replace->left = temp->left;
                replace->right = temp->right;
                replace->parent = temp->parent;
                //Determine if temp is a left or right child non-root only
                if(temp->ssn != root->ssn) {
                    //Modify temp's parent to point to replacement
                    if(temp->parent->left != nullptr && temp->parent->left->ssn == temp->ssn) {
                        temp->parent->left = replace;
                    }
                    if(temp->parent->right != nullptr && temp->parent->right->ssn == temp->ssn) {
                        temp->parent->right = replace;
                    }
                }
                //Handles root situation
                if(temp->ssn == root->ssn) {
                    //cout << "Deleted the root: " << root->ssn << " new root before balance: " << replace->ssn << endl;
                    root = replace;
                }
                delete temp;
                //Proceed with rebalancing
                while(bottom != nullptr) {
                    balance(bottom);
                    bottom = bottom->parent;
                }
                return true;
            }
                
            /*
            //Update height and balance
            AVLNode *temp2 = bottom;
            while(bottom != nullptr) {
                temp2 = bottom;
                updateHeight(bottom);
                while(temp2 != nullptr) {
                    balance(temp2);
                    temp2 = temp2->parent;
                }
                bottom = bottom->parent;
            }
            */
        }
    }
}

AVLNode * AVLTree::minVal(AVLNode* node)
{
        AVLNode* current = node;
        while(current->left != nullptr)
                current = current->left;
        return current;
}

// internal function
// do not call it directly
void AVLTree::print(AVLNode* x, int indent){
    if(x == nullptr) return;
    if (x->right != nullptr) {
        print(x->right, indent+4);
    }
    
    if (indent != 0) {
        cout << std::setw(indent) << ' ';
    }
    
    if(x->right != nullptr){
        cout << " /\n" << std::setw(indent) << ' ';
    }
    
    cout << x->ssn << endl;
    
    if (x->left != nullptr) {
        cout << std::setw(indent) << ' ' <<" \\\n";
        print(x->left, indent+4);
    }
    
}

// print out the structure of the binary tree
// use it for debugging, I love this function
void AVLTree::print(){
    int count = 0;
    print(root, count);
}


// it does not level order traversal
// it prints out the number of node
// use it mainly for debugging
void AVLTree::levelOrder(){
// please implement it
    queue<AVLNode*> q;
    q.push(root);
    int size = 0;
    int nodeCount = q.size();
    while(nodeCount > 0) {
        AVLNode *node = q.front();
        size++;
        q.pop();
        if(node->left != nullptr)
            q.push(node->left);
        if(node->right != nullptr)
            q.push(node->right);
        nodeCount = q.size();
    }
    cout << "Tree size: " << size << endl;
}


