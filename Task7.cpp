
#include <iostream>
#include <vector>
using namespace std;

// Store the complete testing plan
struct WinePlan {
    bool possible;
    vector<vector<int>> schedule;
    vector<int> decoder;
};

// Recursive Divide and Conquer function
void buildPlan(
    int bit,
    int usedTesters,
    int mask,
    int barrels,
    WinePlan& plan
) {
    // Base Case: All binary bits have been assigned
    if (bit == usedTesters) {

        // Ignore the all-zero pattern
        if (mask == 0) {
            return;
        }

        // Assign the binary code to its barrel
        if (mask <= barrels) {
            int barrel = mask;

            // Save the barrel in the decoder
            plan.decoder[mask] = barrel;

            // Assign the barrel to testers whose bits are 1
            for (int i = 0; i < usedTesters; i++) {
                if (mask & (1 << i)) {
                    plan.schedule[i].push_back(barrel);
                }
            }
        }

        return;
    }

    // DIVIDE: First branch - current bit is 0
    buildPlan(
        bit + 1,
        usedTesters,
        mask,
        barrels,
        plan
    );

    // DIVIDE: Second branch - current bit is 1
    buildPlan(
        bit + 1,
        usedTesters,
        mask | (1 << bit),
        barrels,
        plan
    );
}

// Create the complete wine testing plan
WinePlan createPlan(int barrels, int testers) {

    int usedTesters = 0;

    // Calculate the minimum number of testers needed
    while ((1 << usedTesters) < barrels + 1) {
        usedTesters++;
    }

    WinePlan plan;

    // Check whether enough testers are available
    if (usedTesters > testers) {
        plan.possible = false;
        return plan;
    }

    plan.possible = true;

    // Create one schedule for each required tester
    plan.schedule.resize(usedTesters);

    // Initialize the decoder
    plan.decoder.assign(1 << usedTesters, -1);

    // Start recursive Divide and Conquer
    buildPlan(
        0,
        usedTesters,
        0,
        barrels,
        plan
    );

    return plan;
}

int main() {

    int barrels = 1000;
    int testers = 10;

    // Generate the testing plan
    WinePlan plan = createPlan(barrels, testers);

    // Check if a solution exists
    if (!plan.possible) {
        cout << "Not enough testers!\n";
        return 0;
    }

    // Display the number of testers used
    cout << "Number of testers used: "
         << plan.schedule.size() << "\n\n";

    // Display each tester's tasting schedule
    for (int i = 0; i < plan.schedule.size(); i++) {

        cout << "Tester " << i << " tastes barrels: ";

        for (int barrel : plan.schedule[i]) {
            cout << barrel << " ";
        }

        cout << "\n";
    }

    // Example: Testers 0 and 2 die
    // Death pattern = 0000000101 = 5
    int deathMask = 5;

    // Decode the poisoned barrel
    cout << "\nPoisoned barrel: "
         << plan.decoder[deathMask] << "\n";

    return 0;
}
