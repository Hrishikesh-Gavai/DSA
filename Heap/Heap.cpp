#include <iostream>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Function to reheapDown for max heap
void reheapDownMax(int a[], int n, int i) {
    int j, temp;
    while (2*i + 1 < n) {
        j = 2*i + 1; // left child
        if (j+1 < n && a[j+1] > a[j])
            j = j + 1; // right child
        if (a[i] >= a[j])
            break;
        else {
            swap(a[i], a[j]);
            i = j;
        }
    }
}

// Function to reheapDown for min heap
void reheapDownMin(int a[], int n, int i) {
    int j;
    while (2*i + 1 < n) {
        j = 2*i + 1; // left child
        if (j+1 < n && a[j+1] < a[j])
            j = j + 1; // right child
        if (a[i] <= a[j])
            break;
        else {
            swap(a[i], a[j]);
            i = j;
        }
    }
}

// Build max heap
void buildMaxHeap(int a[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        reheapDownMax(a, n, i);
}

// Build min heap
void buildMinHeap(int a[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        reheapDownMin(a, n, i);
}

int main() {
    int marks[50], n;
    cout << "Enter number of students: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter marks obtained by student " << i << " :";
        cin >> marks[i];
    }

    int choice;
    do {
        cout << "\nMenu\n1. Find Maximum marks\n2. Find Minimum marks\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Build max heap and maximum is root
                buildMaxHeap(marks, n);
                cout << "Maximum marks obtained: " << marks[0] << endl;
                break;

            case 2:
                // Build min heap and minimum is root
                buildMinHeap(marks, n);
                cout << "Minimum marks obtained: " << marks[0] << endl;
                break;

            case 3:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
                break;
        }
    } while (choice != 3);

    return 0;
}
