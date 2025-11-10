#include<iostream>
#include<stack>
using namespace std;

class node {
public:
    int data;
    node *left, *right;
};

class bstree {
public:
    node *root;

    bstree() {
        root = NULL;
    }

    void create();
    void insert();
    void number_of_nodes_in_longest_path_from_root();
    void min_node();
    void max_node();
    void search();
    void print_in_asc();
    void print_in_desc();
    void recursive_inorder(node *);
    void recursive_preorder(node *);
    void recursive_postorder(node *);
    void recursive_inorder_desc(node *);
    void non_inorder();
    void non_preorder();
    void non_postorder();
};

void bstree::create() {
    cout << "\nCreating Root\n";
    root = new node;
    root->left = root->right = NULL;
    cout << "\nEnter the data: ";
    cin >> root->data;
}

void bstree::insert() {
    node *temp, *p;

    if (root == NULL) {
        create();
        return;
    }

    p = new node;
    p->left = p->right = NULL;
    cout << "\nEnter the data: ";
    cin >> p->data;

    temp = root;
    while (true) {
        if (p->data < temp->data) {
            if (temp->left == NULL) {
                temp->left = p;
                break;
            } else {
                temp = temp->left;
            }
        } else if (p->data > temp->data) {
            if (temp->right == NULL) {
                temp->right = p;
                break;
            } else {
                temp = temp->right;
            }
        } else {
            cout << "\nAlready Inserted Data";
            delete p;
            break;
        }
    }
}

void bstree::min_node() {
    if (root == NULL) {
        cout << "\nTree is empty.\n";
        return;
    }

    node *temp = root;
    while (temp->left != NULL) {
        temp = temp->left;
    }
    cout << "\nMinimum node is: " << temp->data << endl;
}

void bstree::max_node() {
    if (root == NULL) {
        cout << "\nTree is empty.\n";
        return;
    }

    node *temp = root;
    while (temp->right != NULL) {
        temp = temp->right;
    }
    cout << "\nMaximum node is: " << temp->data << endl;
}

void bstree::recursive_inorder(node *root) {
    if (root != NULL) {
        recursive_inorder(root->left);
        cout << root->data << " ";
        recursive_inorder(root->right);
    }
}

void bstree::recursive_preorder(node *root) {
    if (root != NULL) {
        cout << root->data << " ";
        recursive_preorder(root->left);
        recursive_preorder(root->right);
    }
}

void bstree::recursive_postorder(node *root) {
    if (root != NULL) {
        recursive_postorder(root->left);
        recursive_postorder(root->right);
        cout << root->data << " ";
    }
}

void bstree::non_inorder() {
    if (root == NULL) return;
    stack<node*> s;
    node *temp = root;

    while (!s.empty() || temp != NULL) {
        if (temp != NULL) {
            s.push(temp);
            temp = temp->left;
        } else {
            temp = s.top(); s.pop();
            cout << temp->data << " ";
            temp = temp->right;
        }
    }
}

void bstree::non_preorder() {
    if (root == NULL) return;
    stack<node*> s;
    s.push(root);

    while (!s.empty()) {
        node *temp = s.top(); s.pop();
        cout << temp->data << " ";

        if (temp->right) s.push(temp->right);
        if (temp->left) s.push(temp->left);
    }
}

void bstree::non_postorder() {
    if (root == NULL) return;
    stack<node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        node *temp = s1.top(); s1.pop();
        s2.push(temp);
        if (temp->left) s1.push(temp->left);
        if (temp->right) s1.push(temp->right);
    }
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

int height(node *root) {
    if (root == NULL)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return max(leftHeight, rightHeight) + 1;
}

void bstree::number_of_nodes_in_longest_path_from_root() {
    int h = height(root);
    cout << "\nNumber of nodes in longest path from root: " << h << endl;
}

void bstree::search() {
    int key;
    cout << "\nEnter value to search: ";
    cin >> key;
    node *temp = root;
    while (temp != NULL) {
        if (key == temp->data) {
            cout << "\nValue found!";
            return;
        } else if (key < temp->data) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    cout << "\nValue not found.";
}

void bstree::print_in_asc() {
    recursive_inorder(root);
    cout << endl;
}

void bstree::recursive_inorder_desc(node *root) {
    if (root != NULL) {
        recursive_inorder_desc(root->right);
        cout << root->data << " ";
        recursive_inorder_desc(root->left);
    }
}

int main() {
    bstree bst;
    int x;

    do {
        cout << "\n\n*** Select An Option ***";
        cout << "\n1. Create BST";
        cout << "\n2. Insert in BST";
        cout << "\n3. Find number of nodes in longest path from root";
        cout << "\n4. Minimum Node";
        cout << "\n5. Maximum Node";
        cout << "\n6. Search Node";
        cout << "\n7. Print in Ascending";
        cout << "\n8. Print in descending";
        cout << "\n9. Recursive InOrder";
        cout << "\n10. Recursive PreOrder";
        cout << "\n11. Recursive PostOrder";
        cout << "\n12. Non-Recursive InOrder";
        cout << "\n13. Non-Recursive PreOrder";
        cout << "\n14. Non-recursive PostOrder";
        cout << "\n15. Exit";
        cout << "\n\nEnter Choice: ";
        cin >> x;

        switch (x) {
            case 1: bst.create(); break;
            case 2: bst.insert(); break;
            case 3: bst.number_of_nodes_in_longest_path_from_root(); break;
            case 4: bst.min_node(); break;
            case 5: bst.max_node(); break;
            case 6: bst.search(); break;
            case 7: bst.print_in_asc(); break;
            case 8: bst.recursive_inorder_desc(bst.root); break;
            case 9: bst.recursive_inorder(bst.root); break;
            case 10: bst.recursive_preorder(bst.root); break;
            case 11: bst.recursive_postorder(bst.root); break;
            case 12: bst.non_inorder(); break;
            case 13: bst.non_preorder(); break;
            case 14: bst.non_postorder(); break;
            case 15: cout << "\nExiting Program...\n\n"; break;
            default: cout << "\nInvalid Choice!\n\n";
        }
    } while (x != 15);

    return 0;
}





