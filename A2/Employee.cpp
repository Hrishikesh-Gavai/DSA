#include <iostream>
#include <stack>
using namespace std;

class node {
public:
    int empID;
    int salary;
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
    void min_salary();
    void max_salary();
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
    int count_internal_nodes(node *);
    int count_total_nodes(node *);
    void display_leaf_nodes(node *);
};

void bstree::create() {
    cout << "\nCreating Root Employee Record\n";
    root = new node;
    root->left = root->right = NULL;
    cout << "Enter Employee ID: ";
    cin >> root->empID;
    cout << "Enter Employee Salary: ";
    cin >> root->salary;
}

void bstree::insert() {
    node *temp, *p;

    if (root == NULL) {
        create();
        return;
    }

    p = new node;
    p->left = p->right = NULL;
    cout << "\nEnter Employee ID: ";
    cin >> p->empID;
    cout << "Enter Employee Salary: ";
    cin >> p->salary;

    temp = root;
    while (true) {
        if (p->empID < temp->empID) {
            if (temp->left == NULL) {
                temp->left = p;
                break;
            } else {
                temp = temp->left;
            }
        } else if (p->empID > temp->empID) {
            if (temp->right == NULL) {
                temp->right = p;
                break;
            } else {
                temp = temp->right;
            }
        } else {
            cout << "\nEmployee ID already exists!";
            delete p;
            break;
        }
    }
}

void bstree::min_salary() {
    if (root == NULL) {
        cout << "\nNo employee data available.\n";
        return;
    }

    node *minNode = root;
    while (minNode->left != NULL) {
        minNode = minNode->left;
    }
    cout << "\nEmployee with Minimum Salary:\n";
    cout << "ID: " << minNode->empID << ", Salary: " << minNode->salary << endl;
}

void bstree::max_salary() {
    if (root == NULL) {
        cout << "\nNo employee data available.\n";
        return;
    }

    node *maxNode = root;
    while (maxNode->right != NULL) {
        maxNode = maxNode->right;
    }
    cout << "\nEmployee with Maximum Salary:\n";
    cout << "ID: " << maxNode->empID << ", Salary: " << maxNode->salary << endl;
}

void bstree::recursive_inorder(node *root) {
    if (root != NULL) {
        recursive_inorder(root->left);
        cout << "[ID: " << root->empID << ", Salary: " << root->salary << "] ";
        recursive_inorder(root->right);
    }
}

void bstree::recursive_preorder(node *root) {
    if (root != NULL) {
        cout << "[ID: " << root->empID << ", Salary: " << root->salary << "] ";
        recursive_preorder(root->left);
        recursive_preorder(root->right);
    }
}

void bstree::recursive_postorder(node *root) {
    if (root != NULL) {
        recursive_postorder(root->left);
        recursive_postorder(root->right);
        cout << "[ID: " << root->empID << ", Salary: " << root->salary << "] ";
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
            cout << "[ID: " << temp->empID << ", Salary: " << temp->salary << "] ";
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
        cout << "[ID: " << temp->empID << ", Salary: " << temp->salary << "] ";

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
        cout << "[ID: " << s2.top()->empID << ", Salary: " << s2.top()->salary << "] ";
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
    cout << "\nHeight of the BST (Number of nodes in longest path): " << h << endl;
}

void bstree::search() {
    int key;
    cout << "\nEnter Employee ID to search: ";
    cin >> key;
    node *temp = root;
    while (temp != NULL) {
        if (key == temp->empID) {
            cout << "\nEmployee Found!\n";
            cout << "ID: " << temp->empID << ", Salary: " << temp->salary << endl;
            return;
        } else if (key < temp->empID) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    cout << "\nEmployee Not Found.\n";
}

void bstree::print_in_asc() {
    recursive_inorder(root);
    cout << endl;
}

void bstree::recursive_inorder_desc(node *root) {
    if (root != NULL) {
        recursive_inorder_desc(root->right);
        cout << "[ID: " << root->empID << ", Salary: " << root->salary << "] ";
        recursive_inorder_desc(root->left);
    }
}

int bstree::count_internal_nodes(node *root) {
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 0; // leaf node
    return 1 + count_internal_nodes(root->left) + count_internal_nodes(root->right);
}

int bstree::count_total_nodes(node *root) {
    if (root == NULL)
        return 0;
    return 1 + count_total_nodes(root->left) + count_total_nodes(root->right);
}

void bstree::display_leaf_nodes(node *root) {
    if (root == NULL)
        return;
    if (root->left == NULL && root->right == NULL) {
        cout << "[ID: " << root->empID << ", Salary: " << root->salary << "] ";
        return;
    }
    display_leaf_nodes(root->left);
    display_leaf_nodes(root->right);
}

int main() {
    bstree bst;
    int x;

    do {
        cout << "\n\n*** Employee Data Management Using BST ***";
        cout << "\n1. Create BST (Root Employee)";
        cout << "\n2. Insert New Employee Data";
        cout << "\n3. Display Height of BST";
        cout << "\n4. Find Employee with Minimum Salary";
        cout << "\n5. Find Employee with Maximum Salary";
        cout << "\n6. Search Employee by ID";
        cout << "\n7. Display Employees in Ascending Order (by ID)";
        cout << "\n8. Display Employees in Descending Order (by ID)";
        cout << "\n9. Recursive InOrder";
        cout << "\n10. Recursive PreOrder";
        cout << "\n11. Recursive PostOrder";
        cout << "\n12. Non-Recursive InOrder";
        cout << "\n13. Non-Recursive PreOrder";
        cout << "\n14. Non-Recursive PostOrder";
        cout << "\n15. Count Internal Nodes";
        cout << "\n16. Count Total Nodes";
        cout << "\n17. Display Leaf Nodes";
        cout << "\n18. Exit";
        cout << "\n\nEnter Choice: ";
        cin >> x;

        switch (x) {
            case 1: bst.create(); break;
            case 2: bst.insert(); break;
            case 3: bst.number_of_nodes_in_longest_path_from_root(); break;
            case 4: bst.min_salary(); break;
            case 5: bst.max_salary(); break;
            case 6: bst.search(); break;
            case 7: bst.print_in_asc(); break;
            case 8: bst.recursive_inorder_desc(bst.root); break;
            case 9: bst.recursive_inorder(bst.root); break;
            case 10: bst.recursive_preorder(bst.root); break;
            case 11: bst.recursive_postorder(bst.root); break;
            case 12: bst.non_inorder(); break;
            case 13: bst.non_preorder(); break;
            case 14: bst.non_postorder(); break;
            case 15: cout << "\nNumber of Internal Nodes: " << bst.count_internal_nodes(bst.root) << endl; break;
            case 16: cout << "\nTotal Number of Nodes: " << bst.count_total_nodes(bst.root) << endl; break;
            case 17: cout << "\nLeaf Nodes:\n"; bst.display_leaf_nodes(bst.root); cout << endl; break;
            case 18: cout << "\nExiting Program...\n"; break;
            default: cout << "\nInvalid Choice!\n";
        }
    } while (x != 18);

    return 0;
}
