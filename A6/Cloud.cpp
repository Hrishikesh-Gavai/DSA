#include <iostream>
using namespace std;

int main() {
    int fileCount, storageCapacity;
    cout << "Enter number of files: ";
    cin >> fileCount;
    cout << "Enter total storage capacity (in GB): ";
    cin >> storageCapacity;

    int size[100], importance[100]; // Supports up to 100 files
    for (int i = 0; i < fileCount; i++) {
        cout << "Enter size (in GB) and importance of file " << (i + 1) << ": ";
        cin >> size[i] >> importance[i];
    }

    // dp[i][s] = maximum importance using first i files with storage s
    static int dp[101][10001]; // Handles up to 100 files and capacity up to 10000 GB

    for (int i = 0; i <= fileCount; i++) {
        for (int s = 0; s <= storageCapacity; s++) {

            // Base case: no files or zero storage
            if (i == 0 || s == 0) {
                dp[i][s] = 0;
            }

            // If current file fits in the remaining storage
            else if (size[i - 1] <= s) {
                int excludeFile = dp[i - 1][s]; // skip the file
                int includeFile = dp[i - 1][s - size[i - 1]] + importance[i - 1]; // take the file

                // Choose whichever gives higher total importance
                dp[i][s] = (excludeFile > includeFile) ? excludeFile : includeFile;
            }

            // If file is too large, skip it
            else {
                dp[i][s] = dp[i - 1][s];
            }
        }
    }

    // 🔹 Backtracking to find selected files
    int totalSize = 0;
    int remaining = storageCapacity;

    cout << "\nSelected files: ";
    for (int i = fileCount; i > 0 && remaining > 0; i--) {
        if (dp[i][remaining] != dp[i - 1][remaining]) {
            cout << i << " ";
            totalSize += size[i - 1];
            remaining -= size[i - 1];
        }
    }

    cout << "\nTotal storage used = " << totalSize << " GB";
    cout << "\nMaximum importance achieved = " << dp[fileCount][storageCapacity] << endl;

    return 0;
}
