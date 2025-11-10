#include <iostream>
using namespace std;

int main() {
    int campaignCount, budget;
    cout << "Enter number of campaigns: ";
    cin >> campaignCount;
    cout << "Enter total budget: ";
    cin >> budget;

    int cost[100], reach[100]; // Supports up to 100 campaigns
    for (int i = 0; i < campaignCount; i++) {
        cout << "Enter cost and expected reach of campaign " << (i + 1) << ": ";
        cin >> cost[i] >> reach[i];
    }

    // dp[i][b] = maximum reach using first i campaigns with budget b
    static int dp[101][10001]; // Handles up to 100 campaigns and budget up to 10000

    for (int i = 0; i <= campaignCount; i++) {
        for (int b = 0; b <= budget; b++) {

            // Base case: no campaigns or zero budget
            if (i == 0 || b == 0) {
                dp[i][b] = 0;
            }

            // If current campaign fits in the budget
            else if (cost[i - 1] <= b) {
                int excludeCampaign = dp[i - 1][b]; // skip the campaign
                int includeCampaign = dp[i - 1][b - cost[i - 1]] + reach[i - 1]; // take the campaign

                // Choose whichever gives higher total reach
                dp[i][b] = (excludeCampaign > includeCampaign) ? excludeCampaign : includeCampaign;
            }

            // If campaign is too expensive, skip it
            else {
                dp[i][b] = dp[i - 1][b];
            }
        }
    }

    // 🔹 Simplified backtracking to find selected campaigns
    int totalCost = 0;
    int w = budget;

    cout << "\nSelected campaigns: ";
    for (int i = campaignCount; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << i << " ";
            totalCost += cost[i - 1];
            w -= cost[i - 1];
        }
    }

    cout << "\nTotal cost used = " << totalCost;
    cout << "\nMaximum reach achieved = " << dp[campaignCount][budget] << endl;

    return 0;
}
