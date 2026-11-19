
#include <iostream>
#include <vector>
using namespace std;

struct WinePlan {
    bool possible;
    vector<vector<int>> schedule;
    vector<int> decoder;
};

WinePlan createPlan(int barrels, int testers) {
    int usedTesters = 0;

    // Find the minimum number of testers needed.
    while ((1 << usedTesters) < barrels + 1) {
        usedTesters++;
    }

    WinePlan plan;

    if (usedTesters > testers) {
        plan.possible = false;
        return plan;
    }

    plan.possible = true;
    plan.schedule.resize(usedTesters);

    // Each barrel gets a unique binary code.
    plan.decoder.assign(1 << usedTesters, -1);

    for (int barrel = 1; barrel <= barrels; barrel++) {
        int mask = barrel;  // Important: use barrel, NOT barrel - 1

        for (int i = 0; i < usedTesters; i++) {
            if (mask & (1 << i)) {
                plan.schedule[i].push_back(barrel);
            }
        }

        plan.decoder[mask] = barrel;
    }

    return plan;
}

int main() {
    int barrels = 1000;
    int testers = 10;

    WinePlan plan = createPlan(barrels, testers);

    if (!plan.possible) {
        cout << "Not enough testers!\n";
        return 0;
    }

    cout << "Number of testers used: "
         << plan.schedule.size() << "\n\n";

    for (int i = 0; i < plan.schedule.size(); i++) {
        cout << "Tester " << i << " tastes barrels: ";

        for (int barrel : plan.schedule[i]) {
            cout << barrel << " ";
        }

        cout << "\n";
    }

    // Example: testers 0 and 2 die.
    // Death pattern = 0000000101 = 5.
    int deathMask = 5;

    cout << "\nPoisoned barrel: "
         << plan.decoder[deathMask] << "\n";

    return 0;
}
