#include<iostream>
#include<stack>
using namespace std;

class node {
public:
    int data; // book ID
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
    void remove();
    void min_book();
    void max_book();
    void search();
    void print_in_asc();
    void recursive_inorder(node *);
    void count_total_books();
    void count_leaf_nodes();
    int total_nodes(node *);
    int leaf_nodes(node *);
};

void bstree::create() {
    cout << "\nCreating Library Catalog (Root Book)\n";
    root = new node;
    root->left = root->right = NULL;
    cout << "Enter Book ID: ";
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
    cout << "Enter new Book ID to insert: ";
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
            cout << "\nBook ID already exists in catalog!";
            delete p;
            break;
        }
    }
}

node* delete_node(node *root, int key) {
    if (root == NULL) return root;

    if (key < root->data)
        root->left = delete_node(root->left, key);
    else if (key > root->data)
        root->right = delete_node(root->right, key);
    else {
        // Node found
        if (root->left == NULL) {
            node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            node *temp = root->left;
            delete root;
            return temp;
        }
        // Node with two children: find inorder successor
        node *succ = root->right;
        while (succ->left != NULL)
            succ = succ->left;
        root->data = succ->data;
        root->right = delete_node(root->right, succ->data);
    }
    return root;
}

void bstree::remove() {
    if (root == NULL) {
        cout << "\nCatalog is empty!\n";
        return;
    }

    int key;
    cout << "\nEnter Book ID to delete: ";
    cin >> key;
    root = delete_node(root, key);
    cout << "\nBook deleted (if it existed).\n";
}

void bstree::min_book() {
    if (root == NULL) {
        cout << "\nCatalog is empty.\n";
        return;
    }

    node *temp = root;
    while (temp->left != NULL) {
        temp = temp->left;
    }
    cout << "\nBook with smallest ID: " << temp->data << endl;
}

void bstree::max_book() {
    if (root == NULL) {
        cout << "\nCatalog is empty.\n";
        return;
    }

    node *temp = root;
    while (temp->right != NULL) {
        temp = temp->right;
    }
    cout << "\nBook with largest ID: " << temp->data << endl;
}

void bstree::recursive_inorder(node *root) {
    if (root != NULL) {
        recursive_inorder(root->left);
        cout << root->data << " ";
        recursive_inorder(root->right);
    }
}

int bstree::total_nodes(node *root) {
    if (root == NULL) return 0;
    return 1 + total_nodes(root->left) + total_nodes(root->right);
}

int bstree::leaf_nodes(node *root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return leaf_nodes(root->left) + leaf_nodes(root->right);
}

void bstree::count_total_books() {
    cout << "\nTotal number of books in catalog: " << total_nodes(root) << endl;
}

void bstree::count_leaf_nodes() {
    cout << "\nTotal number of leaf (end) books: " << leaf_nodes(root) << endl;
}

void bstree::print_in_asc() {
    cout << "\nBooks in ascending order of IDs: ";
    recursive_inorder(root);
    cout << endl;
}

void bstree::search() {
    int key;
    cout << "\nEnter Book ID to search: ";
    cin >> key;
    node *temp = root;
    while (temp != NULL) {
        if (key == temp->data) {
            cout << "\nBook found in catalog!";
            return;
        } else if (key < temp->data) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    cout << "\nBook not found.";
}

int main() {
    bstree library;
    int choice;

    do {
        cout << "\n\n*** Library Book Catalog Menu ***";
        cout << "\n1. Create Library Catalog (Root Book)";
        cout << "\n2. Insert a new Book";
        cout << "\n3. Delete a Book";
        cout << "\n4. Find Book with Smallest ID";
        cout << "\n5. Find Book with Largest ID";
        cout << "\n6. Search for a Book";
        cout << "\n7. Display all Books in Ascending Order";
        cout << "\n8. Count total number of Books";
        cout << "\n9. Count number of Leaf Books";
        cout << "\n10. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: library.create(); break;
            case 2: library.insert(); break;
            case 3: library.remove(); break;
            case 4: library.min_book(); break;
            case 5: library.max_book(); break;
            case 6: library.search(); break;
            case 7: library.print_in_asc(); break;
            case 8: library.count_total_books(); break;
            case 9: library.count_leaf_nodes(); break;
            case 10: cout << "\nExiting Program...\n"; break;
            default: cout << "\nInvalid choice. Try again.\n";
        }
    } while (choice != 10);

    return 0;
}
