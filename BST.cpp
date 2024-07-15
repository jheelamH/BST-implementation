
#include <iostream>
using namespace std;

struct node {
    int info;
    node *left;
    node *right;
};

class BST {
private:
    node *root;

public:
    BST() {
        root = NULL;
    }
    void find(int, node **, node **);
    void insert(node *, node *);
    void del(int);
    void case_a(node *, node *);
    void case_b(node *, node *);
    void case_c(node *, node *);
    node* getRoot() { return root; }
    node* search(int);
};

void BST::find(int item, node **par, node **loc) {
    node *ptr, *ptrsave;
    if (root == NULL) {
        *loc = NULL;
        *par = NULL;
        return;
    }
    if (item == root->info) {
        *loc = root;
        *par = NULL;
        return;
    }
    if (item < root->info)
        ptr = root->left;
    else
        ptr = root->right;
    ptrsave = root;
    while (ptr != NULL) {
        if (item == ptr->info) {
            *loc = ptr;
            *par = ptrsave;
            return;
        }
        ptrsave = ptr;
        if (item < ptr->info)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    *loc = NULL;
    *par = ptrsave;
}

void BST::insert(node *tree, node *newnode) {
    if (tree == NULL) {
        root = newnode;
        cout << "Root Node is Added" << endl;
        return;
    }
    if (tree->info == newnode->info) {
        cout << "Element already exists in the tree" << endl;
        return;
    }
    if (tree->info > newnode->info) {
        if (tree->left != NULL) {
            insert(tree->left, newnode);
        } else {
            tree->left = newnode;
            cout << "Node Added To The Left" << endl;
        }
    } else {
        if (tree->right != NULL) {
            insert(tree->right, newnode);
        } else {
            tree->right = newnode;
            cout << "Node Added To The Right" << endl;
        }
    }
}

void BST::del(int item) {
    node *parent, *location;
    if (root == NULL) {
        cout << "Tree is empty" << endl;
        return;
    }
    find(item, &parent, &location);
    if (location == NULL) {
        cout << "Item is not present in the tree" << endl;
        return;
    }
    if (location->left == NULL && location->right == NULL)
        case_a(parent, location);
    if (location->left != NULL && location->right == NULL)
        case_b(parent, location);
    if (location->left == NULL && location->right != NULL)
        case_b(parent, location);
    if (location->left != NULL && location->right != NULL)
        case_c(parent, location);
    delete location;
}

void BST::case_a(node *par, node *loc) {
    if (par == NULL) {
        root = NULL;
    } else {
        if (loc == par->left)
            par->left = NULL;
        else
            par->right = NULL;
    }
}

void BST::case_b(node *par, node *loc) {
    node *child;
    if (loc->left != NULL)
        child = loc->left;
    else
        child = loc->right;
    if (par == NULL) {
        root = child;
    } else {
        if (loc == par->left)
            par->left = child;
        else
            par->right = child;
    }
}

void BST::case_c(node *par, node *loc) {
    node *ptr, *ptrsave, *suc, *parsuc;
    ptrsave = loc;
    ptr = loc->right;
    while (ptr->left != NULL) {
        ptrsave = ptr;
        ptr = ptr->left;
    }
    suc = ptr;
    parsuc = ptrsave;
    if (suc->left == NULL && suc->right == NULL)
        case_a(parsuc, suc);
    else
        case_b(parsuc, suc);
    if (par == NULL) {
        root = suc;
    } else {
        if (loc == par->left)
            par->left = suc;
        else
            par->right = suc;
    }
    suc->left = loc->left;
    suc->right = loc->right;
}

node* BST::search(int item) {
    node *parent, *location;
    find(item, &parent, &location);
    return location;
}

int main() {
    int choice, num;
    BST bst;
    node *temp;
    while (1) {
        cout << "Operations on BST" << endl;
        cout << "1.Insert Element " << endl;
        cout << "2.Delete Element " << endl;
        cout << "3.Search Element" << endl;
        cout << "4.Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                temp = new node;
                temp->left = temp->right = NULL;
                cout << "Enter the number to be inserted: ";
                cin >> temp->info;
                if (bst.getRoot() == NULL) {
                    bst.insert(NULL, temp);
                } else {
                    bst.insert(bst.getRoot(), temp);
                }
                break;
            case 2:
                if (bst.getRoot() == NULL) {
                    cout << "Tree is empty" << endl;
                    continue;
                }
                cout << "Enter the number to be deleted: ";
                cin >> num;
                bst.del(num);
                break;
            case 3:
                if (bst.getRoot() == NULL) {
                    cout << "Tree is empty" << endl;
                    continue;
                }
                cout << "Enter the number to be searched: ";
                cin >> num;
                temp = bst.search(num);
                if (temp != NULL) {
                    cout << "Element " << num << " found in the tree." << endl;
                } else {
                    cout << "Element " << num << " not found in the tree." << endl;
                }
                break;
            case 4:
                exit(1);
            default:
                cout << "Wrong choice" << endl;
        }
    }
}
