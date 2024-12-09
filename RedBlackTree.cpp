#include <iostream>
using namespace std;

class Node{
public:
    int key;
    Node* right, *left, *parent;
    // true ---> Red , false ---> Black
    bool color ;

    Node(int key){
        this->key = key;
        color = true;
        left = right = parent = nullptr;
    }

};

class RedBlackTree{
private:
    Node* root;

    void rightRotate(Node *&root , Node *&A){
        Node *B = A->left;
        A->left = B->right;

        if (B->right != nullptr){
            B->right->parent = A;
        }
        B->parent = A->parent;

        if (A->parent == nullptr){
            root = B;
        }else if (A == A->parent->left){
            A->parent->left = B;
        }else{
            A->parent->right = B;
        }
        B->right = A;
        A->parent = B;
    }

    void lefttRotate(Node *&root , Node *&A){
        Node *B = A->right;
        A->right = B->left;

        if (B->left != nullptr){
            B->left->parent = A;
        }
        B->parent = A->parent;

        if (A->parent == nullptr){
            root = B;
        }else if (A == A->parent->left){
            A->parent->left = B;
        }else{
            A->parent->right = B;
        }
        B->left = A;
        A->parent = B;
    }

    void handelInsertion(Node *&root , Node *&node){
        Node *parent , *grandParent , *uncle = nullptr;
        // parent = red then grandParent = black
        while (node != root && node->color == true && node->parent->color == true){
            parent = node->parent;
            grandParent = node->parent->parent;

            if (parent == grandParent->left){
                uncle = grandParent->right;
                // uncle red and in right location
                if (uncle != nullptr && uncle->color == true){
                    // recolor
                    grandParent->color = true;
                    parent->color = false;
                    uncle->color = false;

                    node = grandParent;
                } else{
                    if (node == parent->right){
                        lefttRotate(root , parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rightRotate(root , grandParent);
                    swap(parent->color , grandParent->color);
                    node = parent;
                }
            } else{
                uncle = grandParent->left;
                // uncle red and in right location
                if (uncle != nullptr && uncle->color == true){
                    // recolor
                    grandParent->color = true;
                    parent->color = false;
                    uncle->color = false;

                    node = grandParent;
                } else{
                    if (node == parent->left){
                        rightRotate(root , parent);
                        node = parent;
                        parent = node->parent;
                    }
                    lefttRotate(root , grandParent);
                    swap(parent->color , grandParent->color);
                    node = parent;
                }
            }
        }
        root->color = false;
    }

    void printTree(Node *node){
        if (node == nullptr){
            return;
        }
        printTree(node->left);
        if (node->color == true){
            cout<<node->key <<", Red\n";
        } else{
            cout<<node->key <<", Black\n";
        }
        printTree(node->right);
    }

public:
    RedBlackTree (){
        root = nullptr;
    }

    void insert(int key){
        Node *node = new Node(key);

        if (root == nullptr){
            node->color = false;
            root = node;
        }
        else{
            Node *node2 = root;
            Node *parent = nullptr;

            while (node2 != nullptr){
                parent = node2;
                if (node->key < node2->key){
                    node2 = node2->left;
                } else{
                    node2 = node2->right;
                }
            }
            node->parent = parent;
            if (node->key < parent->key){
                parent->left = node;
            }
            else{
                parent->right = node;
            }
            handelInsertion(root,node);

        }
    }

    void Print(){
        printTree(root);
        cout<<"\n";
    }

};



int main(){
    RedBlackTree RBT;
    RBT.insert(10);
    RBT.insert(20);
    RBT.insert(30);
    RBT.insert(15);
    RBT.insert(25);
    RBT.Print();


    return 0;
}
