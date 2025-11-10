#include <iostream>
using namespace std;

int main() {
    int n, capacity;
    cout << "Enter number of package types: ";
    cin >> n;

    float benefit[20], weight[20], ratio[20];
    cout << "Enter capacity of the truck: ";
    cin >> capacity;

    for (int i = 0; i < n; i++) {
        cout << "Enter benefit score and weight of package type " << i + 1 << ": ";
        cin >> benefit[i] >> weight[i];
        ratio[i] = benefit[i] / weight[i];
    }

    cout << "\nCalculating benefit/weight ratio for each package type:\n";
    for (int i = 0; i < n; i++) {
        cout << "Package " << i + 1 << ": benefit = " << benefit[i] << ", weight = " << weight[i]
             << ", ratio = " << ratio[i] << endl;
    }

    // Sort packages by ratio (descending) with step display
    cout << "\nSorting packages by benefit/weight ratio in descending order:\n";
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ratio[i] < ratio[j]) {
                // swap all 3 arrays together
                float temp = ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = temp;

                temp = benefit[i];
                benefit[i] = benefit[j];
                benefit[j] = temp;

                temp = weight[i];
                weight[i] = weight[j];
                weight[j] = temp;

                cout << "Swapped package " << i + 1 << " with package " << j + 1 << endl;
            }
        }
    }

    cout << "\nPackages after sorting:\n";
    for (int i = 0; i < n; i++) {
        cout << "Package " << i + 1 << ": benefit = " << benefit[i] << ", weight = " << weight[i]
             << ", ratio = " << ratio[i] << endl;
    }

    float totalBenefit = 0, currentWeight = 0;

    cout << "\nLoading the truck:\n";
    for (int i = 0; i < n; i++) {
        if (currentWeight + weight[i] <= capacity) {
            // take full package
            currentWeight += weight[i];
            totalBenefit += benefit[i];
            cout << "Loaded full package " << i + 1 << " (weight = " << weight[i]
                 << ", benefit = " << benefit[i] << "). Current weight: " << currentWeight
                 << ", total benefit: " << totalBenefit << endl;
        } else {
            // take fractional part
            float remain = capacity - currentWeight;
            totalBenefit += ratio[i] * remain;
            cout << "Loaded fractional part of package " << i + 1 << " (weight = " << remain
                 << ", benefit = " << ratio[i] * remain << "). Truck is full now." << endl;
            break;
        }
    }

    cout << "\nTotal truck weight used = " << currentWeight << " / " << capacity << endl;
    cout << "Maximum total benefit obtained = " << totalBenefit << endl;

    return 0;
}
