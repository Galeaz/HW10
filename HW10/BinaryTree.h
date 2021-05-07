// Participants: Christopher
// Date: 5-6-21
// Description: BinaryTree
#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;

class BinaryTree {
    public:
        struct node {
            int entry;
            struct node* left;
            struct node* right;
        }*right;

        void insert(node*, node*);
        void remove(int);
        void find(int, node**, node**);
        void noNull(node*, node*);
        void oneNull(node*, node*);
        void bothNull(node*, node*);
        void Printcount();
        void search(node*, int);
        void preorder(node*);
        void inorder(node*);
        void postorder(node*);
        void deleteNode(node*& _node);
        void print(node*, int);
        int getCount();
        BinaryTree() {
            right = NULL;
            count = 0;
        }
private:
    int count;
};

int BinaryTree::getCount()
{
    return count;
}
void BinaryTree::Printcount()
{
    cout << "\n\tCount of Nodes = " << count << ".\n";
}

void BinaryTree::insert(node *tree, node *newnode) {
    if (right == NULL) {
        right = new node;
        right->entry = newnode->entry;
        right->left = NULL;
        right->right = NULL;
        count++;
        return;
    }
    if (tree->entry > newnode->entry) {
        if (tree->left != NULL) {
            insert(tree->left, newnode);
        }
        else {
            tree->left = newnode;
            (tree->left)->left = NULL;
            (tree->left)->right = NULL;
            count++;
            return;
        }
    }
    else {
        if (tree->right != NULL) {
            insert(tree->right, newnode);
        }
        else {
            tree->right = newnode;
            (tree->right)->left = NULL;
            (tree->right)->right = NULL;
            count++;
            return;
        }
    }
}
void BinaryTree::remove(int i) {
    node*a, *b;
    if (right == NULL) {
        cout << "ERROR: BinaryTree is empty.\n";
        return;
    }
    find(i, &a, &b);
    if (b == NULL) {
        cout << "ERROR: Not in BinaryTree.\n";
        return;
    }
    if (b->left != NULL && b->right != NULL) noNull(a, b);
    if ((b->left != NULL && b->right == NULL) || (b->left == NULL && b->right != NULL)) oneNull(a, b);
    if (b->left == NULL && b->right == NULL) bothNull(a, b);
    free(b);
    count--;
}
void BinaryTree::find(int i, node **a, node **b) {
    node *ptr, *ptrTemp;
    if (right == NULL) {
        *b = NULL;
        *a = NULL;
        return;
    }
    if (i == right->entry) {
        *b = right;
        *a = NULL;
        return;
    }
    if (i < right->entry)
        ptr = right->left;
    else
        ptr = right->right;
    ptrTemp = right;
    while (ptr != NULL) {
        if (i == ptr->entry) {
            *b = ptr;
            *a = ptrTemp;
            return;
        }
        ptrTemp = ptr;
        if (i < ptr->entry)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    *b = NULL;
    *a = ptrTemp;
}
void BinaryTree::noNull(node *a, node *b) {
    node *ptr, *ptrTemp, *suc, *parsuc;
    ptrTemp = b;
    ptr = b->right;
    while (ptr->left != NULL) {
        ptrTemp = ptr;
        ptr = ptr->left;
    }
    suc = ptr;
    parsuc = ptrTemp;
    if (suc->left == NULL && suc->right == NULL)
        bothNull(parsuc, suc);
    else
        oneNull(parsuc, suc);
    if (a == NULL) {
        right = suc;
    }
    else {
        if (b == a->left)
            a->left = suc;
        else
            a->right = suc;
    }
    suc->left = b->left;
    suc->right = b->right;
    cout << "Removal successful\n";
}
void BinaryTree::oneNull(node *a, node *b) {
    node *child;
    if (b->left != NULL)
        child = b->left;
    else
        child = b->right;
    if (a == NULL) {
        right = child;
    }
    else {
        if (b == a->left)
            a->left = child;
        else
            a->right = child;
    }
    cout << "Removal successful\n";
}
void BinaryTree::bothNull(node *a, node *b) {
    if (a == NULL) {
        right = NULL;
    }
    else {
        if (b == a->left)
            a->left = NULL;
        else
            a->right = NULL;
    }
    cout << "Removal successful\n";
}
void BinaryTree::search(node *root, int getThis) {
    int depth = 0;
    node *temp = new node;
    temp = root;
    while (temp != NULL) {
        depth++;
        if (temp->entry == getThis) {
            cout << "Found\n";
            return;
        }
        else if (temp->entry > getThis)
            temp = temp->left;
        else
            temp = temp->right;
    }
    cout << "Not found\n";
    return;
}
void BinaryTree::preorder(node *ptr) {
    if (right == NULL) {
        cout << "Tree is empty\n";
        return;
    }
    if (ptr != NULL) {
        cout << ptr->entry << " ";
        preorder(ptr->left);
        preorder(ptr->right);
    }
}
void BinaryTree::inorder(node *ptr) {
    if (right == NULL) {
        cout << "Tree is empty\n";
        return;
    }
    if (ptr != NULL) {
        inorder(ptr->left);
        cout << ptr->entry << " ";
        inorder(ptr->right);
    }
}
void BinaryTree::postorder(node *ptr) {
    if (right == NULL) {
        cout << "Tree is empty\n";
        return;
    }
    if (ptr != NULL) {
        postorder(ptr->left);
        postorder(ptr->right);
        cout << ptr->entry << " ";
    }
}
void BinaryTree::print(node *ptr, int level) {
    int i;
    if (ptr != NULL) {
        cout <<"\n\t";
        for (i = 0; i < level; i++)
            cout << " ";
        cout << ptr->entry;
        print(ptr->left, level);
        print(ptr->right, level);
    }
}

void BinaryTree::deleteNode(node*& _node) {
    if (_node == nullptr) return;
    deleteNode(_node->left);
    deleteNode(_node->righ);
    delete _node;
    _node = nullptr;
    count--;
}