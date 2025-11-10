#include <iostream>
using namespace std;

int main() {
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n;

    float value[20], weight[20], ratio[20];
    cout << "Enter capacity of knapsack: ";
    cin >> capacity;

    for (int i = 0; i < n; i++) {
        cout << "Enter value and weight of item " << i + 1 << ": ";
        cin >> value[i] >> weight[i];
        ratio[i] = value[i] / weight[i];
    }

    cout << "\nCalculating value/weight ratio for each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << ": value = " << value[i] << ", weight = " << weight[i] 
             << ", ratio = " << ratio[i] << endl;
    }

    // Sort items by ratio (descending) with step display
    cout << "\nSorting items by value/weight ratio in descending order:\n";
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ratio[i] < ratio[j]) {
                // swap all 3 arrays together
                float temp = ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = temp;

                temp = value[i];
                value[i] = value[j];
                value[j] = temp;

                temp = weight[i];
                weight[i] = weight[j];
                weight[j] = temp;

                cout << "Swapped item " << i + 1 << " with item " << j + 1 << endl;
            }
        }
    }

    cout << "\nItems after sorting:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << ": value = " << value[i] << ", weight = " << weight[i] 
             << ", ratio = " << ratio[i] << endl;
    }

    float totalValue = 0, currentWeight = 0;

    cout << "\nFilling the knapsack:\n";
    for (int i = 0; i < n; i++) {
        if (currentWeight + weight[i] <= capacity) {
            // take full item
            currentWeight += weight[i];
            totalValue += value[i];
            cout << "Taking full item " << i + 1 << " (weight = " << weight[i]
                 << ", value = " << value[i] << "). Current weight: " << currentWeight 
                 << ", total value: " << totalValue << endl;
        } else {
            // take fractional part
            float remain = capacity - currentWeight;
            totalValue += ratio[i] * remain;
            cout << "Taking fractional part of item " << i + 1 << " (weight = " << remain
                 << ", value = " << ratio[i] * remain << "). Knapsack is full now." << endl;
            break;
        }
    }

    cout << "\nMaximum value that can be obtained = " << totalValue << endl;

    return 0;
}
