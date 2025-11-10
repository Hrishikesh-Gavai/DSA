#include <iostream>
using namespace std;

int main() {
    int itemCount, capacity;
    cout << "Enter number of items: ";
    cin >> itemCount;
    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    int weights[100], values[100]; // Supports up to 100 items
    for (int i = 0; i < itemCount; i++) {
        cout << "Enter weight and value of item " << (i + 1) << ": ";
        cin >> weights[i] >> values[i];
    }

    // dp[i][w] = maximum value using first i items with capacity w
    static int dp[101][10001]; // Handles up to 100 items and capacity 10000

    for (int i = 0; i <= itemCount; i++) {
        for (int w = 0; w <= capacity; w++) {

            // Base case: no items or zero capacity
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }

            // If current item fits in the knapsack
            else if (weights[i - 1] <= w) {
                int excludeItem = dp[i - 1][w]; // skip the item
                int includeItem = dp[i - 1][w - weights[i - 1]] + values[i - 1]; // take the item

                // Choose whichever gives higher total value
                dp[i][w] = (excludeItem > includeItem) ? excludeItem : includeItem;
            }

            // If item is too heavy, skip it
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "Maximum value = " << dp[itemCount][capacity] << endl;
    return 0;
}
