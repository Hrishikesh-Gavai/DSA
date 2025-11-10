#include <iostream>
#include <stack>
#include <string>
#include <cmath>   // Added for pow() and fmod()
using namespace std;

class Node {
public:
    char data;
    Node *left, *right;

    Node(char val) {
        data = val;
        left = right = NULL;
    }
};

class ExpressionTree {
public:
    Node *root;

    ExpressionTree() {
        root = NULL;
    }

    // Check if a character is an operator
    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^');
    }

    // ✅ CHANGED: Build tree from postfix expression (was prefix earlier)
    Node* constructFromPostfix(string postfix) {
        stack<Node*> st;
        // ✅ Traverse from left to right for postfix
        for (int i = 0; i < postfix.size(); i++) {
            char c = postfix[i];
            Node* newNode = new Node(c);

            if (isOperator(c)) {
                // ✅ CHANGED order: right child popped first, then left (for postfix)
                newNode->right = st.top(); st.pop();
                newNode->left = st.top(); st.pop();
            }
            st.push(newNode);
        }
        return st.top();
    }

    void createExpressionTree() {
        string postfix;
        cout << "\nEnter Postfix Expression: ";
        cin >> postfix;
        root = constructFromPostfix(postfix);
        cout << "\nExpression Tree Created!\n";
    }

    // Recursive Traversals
    void recursiveInorder(Node* root) {
        if (root != NULL) {
            recursiveInorder(root->left);
            cout << root->data << " ";
            recursiveInorder(root->right);
        }
    }

    void recursivePreorder(Node* root) {
        if (root != NULL) {
            cout << root->data << " ";
            recursivePreorder(root->left);
            recursivePreorder(root->right);
        }
    }

    void recursivePostorder(Node* root) {
        if (root != NULL) {
            recursivePostorder(root->left);
            recursivePostorder(root->right);
            cout << root->data << " ";
        }
    }

    // Non-recursive Traversals
    void nonRecursiveInorder() {
        stack<Node*> s;
        Node* curr = root;
        while (curr != NULL || !s.empty()) {
            while (curr != NULL) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top(); s.pop();
            cout << curr->data << " ";
            curr = curr->right;
        }
    }

    void nonRecursivePreorder() {
        if (root == NULL) return;
        stack<Node*> s;
        s.push(root);
        while (!s.empty()) {
            Node* temp = s.top(); s.pop();
            cout << temp->data << " ";
            if (temp->right) s.push(temp->right);
            if (temp->left) s.push(temp->left);
        }
    }

    void nonRecursivePostorder() {
        if (root == NULL) return;
        stack<Node*> s1, s2;
        s1.push(root);
        while (!s1.empty()) {
            Node* temp = s1.top(); s1.pop();
            s2.push(temp);
            if (temp->left) s1.push(temp->left);
            if (temp->right) s1.push(temp->right);
        }
        while (!s2.empty()) {
            cout << s2.top()->data << " ";
            s2.pop();
        }
    }

    // ✅ ADDED: Swap left and right children (Mirror Tree)
    void swapChildren(Node* node) {
        if (node == NULL) return;

        Node* temp = node->left;
        node->left = node->right;
        node->right = temp;

        swapChildren(node->left);
        swapChildren(node->right);
    }

    void swapTree() {
        if (root == NULL) {
            cout << "\nTree is empty!\n";
            return;
        }
        swapChildren(root);
        cout << "\nTree has been swapped!\n";
    }

    // ✅ ADDED: Height of the tree
    int heightUtil(Node *root) {
        if (root == NULL) {
            return 0;
        }
        int leftheight = heightUtil(root->left);
        int rightheight = heightUtil(root->right);
        return max(leftheight, rightheight) + 1;
    }

    void height() {
        int h = heightUtil(root);
        cout << "\nHeight of the Tree is: " << h << endl;
    } 

    // ✅ ADDED: Evaluate the expression tree (numeric postfix)
    double evaluate(Node* node) {
        if (node == NULL)
            return 0;

        if (!isOperator(node->data))
            return node->data - '0'; // convert char to numeric

        double leftVal = evaluate(node->left);
        double rightVal = evaluate(node->right);

        switch (node->data) {
            case '+': return leftVal + rightVal;
            case '-': return leftVal - rightVal;
            case '*': return leftVal * rightVal;
            case '/': return rightVal != 0 ? leftVal / rightVal : 0;
            case '%': return fmod(leftVal, rightVal);
            case '^': return pow(leftVal, rightVal);
        }
        return 0;
    }

    void evaluateExpression() {
        if (root == NULL) {
            cout << "\nTree is empty! Please create it first.\n";
            return;
        }
        double result = evaluate(root);
        cout << "\nEvaluated Result: " << result << endl;
    }
};

int main() {
    ExpressionTree et;
    int choice;

    do {
        cout << "\n\n*** Expression Tree Menu ***";
        cout << "\n1. Create Expression Tree (Postfix Expression)";
        cout << "\n2. Recursive Inorder";
        cout << "\n3. Recursive Preorder";
        cout << "\n4. Recursive Postorder";
        cout << "\n5. Non-Recursive Inorder";
        cout << "\n6. Non-Recursive Preorder";
        cout << "\n7. Non-Recursive Postorder";
        cout << "\n8. Swap Left and Right Children (Mirror Tree)";
        cout << "\n9. Height Of the Tree";
        cout << "\n10. Evaluate Expression";
        cout << "\n11. Exit";
        cout << "\n\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: et.createExpressionTree(); break;
            case 2: cout << "\nInorder (Recursive): "; et.recursiveInorder(et.root); break;
            case 3: cout << "\nPreorder (Recursive): "; et.recursivePreorder(et.root); break;
            case 4: cout << "\nPostorder (Recursive): "; et.recursivePostorder(et.root); break;
            case 5: cout << "\nInorder (Non-Recursive): "; et.nonRecursiveInorder(); break;
            case 6: cout << "\nPreorder (Non-Recursive): "; et.nonRecursivePreorder(); break;
            case 7: cout << "\nPostorder (Non-Recursive): "; et.nonRecursivePostorder(); break;
            case 8: et.swapTree(); break;
            case 9: et.height(); break;
            case 10: et.evaluateExpression(); break;
            case 11: cout << "\nExiting...\n"; break;
            default: cout << "\nInvalid Choice!";
        }
    } while (choice != 11);

    return 0;
}
