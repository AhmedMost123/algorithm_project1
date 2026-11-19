
#include <iostream>
#include <vector>
using namespace std;

struct WinePlan {
    bool possible;
    vector<vector<int>> schedule;

    vector<int> decoder;
};

WinePlan designWineTests(int testers) {

    WinePlan plan;
    plan.possible = false;

    if (testers < 10) {
        return plan;
    }

    plan.possible = true;

    int usedTesters = 10;

    plan.schedule.resize(usedTesters);

    plan.decoder.assign(1 << usedTesters, -1);

    for (int barrel = 1; barrel <= 1000; barrel++) {

        int mask = barrel - 1;

        for (int i = 0; i < usedTesters; i++) {

            if (mask & (1 << i)) {
                plan.schedule[i].push_back(barrel);
            }
        }

        // Save the decoding information
        plan.decoder[mask] = barrel;
    }

    return plan;
}
