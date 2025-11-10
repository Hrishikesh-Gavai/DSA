#include <iostream>
using namespace std;

// Function to swap two elements
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Function to reheapDown for max heap
void reheapDownMax(int a[], int n, int i) {
    int j;
    while (2 * i + 1 < n) {
        j = 2 * i + 1; // left child
        if (j + 1 < n && a[j + 1] > a[j])
            j = j + 1; // choose right child if greater
        if (a[i] >= a[j])
            break;
        swap(a[i], a[j]);
        i = j;
    }
}

// Function to reheapDown for min heap
void reheapDownMin(int a[], int n, int i) {
    int j;
    while (2 * i + 1 < n) {
        j = 2 * i + 1; // left child
        if (j + 1 < n && a[j + 1] < a[j])
            j = j + 1; // choose right child if smaller
        if (a[i] <= a[j])
            break;
        swap(a[i], a[j]);
        i = j;
    }
}

// Build Max Heap
void buildMaxHeap(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        reheapDownMax(a, n, i);
}

// Build Min Heap
void buildMinHeap(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        reheapDownMin(a, n, i);
}

// Delete the topmost (maximum) element from a max heap
int deleteMax(int a[], int &n) {
    if (n <= 0) {
        cout << "Heap is empty!\n";
        return -1;
    }
    int maxValue = a[0];
    a[0] = a[n - 1];
    n--;
    reheapDownMax(a, n, 0);
    return maxValue;
}

// Heap Sort for Ascending order (using Max Heap)
void heapSortAscending(int a[], int n) {
    buildMaxHeap(a, n);
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        reheapDownMax(a, i, 0);
    }
}

// Heap Sort for Descending order (using Min Heap)
void heapSortDescending(int a[], int n) {
    buildMinHeap(a, n);
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        reheapDownMin(a, i, 0);
    }
}

int main() {
    int prices[100], n;
    cout << "Enter number of days: ";
    cin >> n;

    cout << "Enter daily stock prices:\n";
    for (int i = 0; i < n; i++) {
        cout << "Day " << i + 1 << ": ";
        cin >> prices[i];
    }

    int choice;
    do {
        cout << "\n==== Stock Price Menu ====\n";
        cout << "1. Display Maximum Price\n";
        cout << "2. Display Minimum Price\n";
        cout << "3. Delete Topmost Maximum Price\n";
        cout << "4. Display Prices in Ascending Order\n";
        cout << "5. Display Prices in Descending Order\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                buildMaxHeap(prices, n);
                cout << "Highest Stock Price: " << prices[0] << endl;
                break;

            case 2:
                buildMinHeap(prices, n);
                cout << "Lowest Stock Price: " << prices[0] << endl;
                break;

            case 3: {
                buildMaxHeap(prices, n);
                int deleted = deleteMax(prices, n);
                if (deleted != -1)
                    cout << "Deleted Maximum Price: " << deleted << endl;
                cout << "Remaining Prices: ";
                for (int i = 0; i < n; i++)
                    cout << prices[i] << " ";
                cout << endl;
                break;
            }

            case 4:
                heapSortAscending(prices, n);
                cout << "Stock Prices in Ascending Order: ";
                for (int i = 0; i < n; i++)
                    cout << prices[i] << " ";
                cout << endl;
                break;

            case 5:
                heapSortDescending(prices, n);
                cout << "Stock Prices in Descending Order: ";
                for (int i = 0; i < n; i++)
                    cout << prices[i] << " ";
                cout << endl;
                break;

            case 6:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}

/*
------------------------------------------
Algorithmic Analysis
------------------------------------------
1️⃣ Insertion (Building Heap):
   - Each reheapDown or reheapUp takes O(log n)
   - Building a heap of n elements takes O(n)

2️⃣ Finding Max or Min:
   - Directly accessed at root (index 0)
   - Time complexity: O(1)

3️⃣ Deletion (deleteMax):
   - Remove root, replace with last element, reheapDown
   - Time complexity: O(log n)

4️⃣ Heap Sort (Ascending/Descending):
   - Build heap O(n), then n deletions O(n log n)
   - Total: O(n log n)

5️⃣ Space Complexity:
   - Uses in-place array → O(1) auxiliary space
------------------------------------------
*/
