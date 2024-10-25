#include <bits/stdc++.h>
using namespace std;

struct FuelStation {
    int64_t x;
    int64_t A;
    int64_t B;
};

struct Journey {
    int64_t N;
    int64_t D;
    vector<FuelStation> stations;

    int64_t cMIF() { // compute Min Initial Fuel
        vector<int64_t> positions;
        vector<int64_t> A_vals;
        vector<int64_t> B_vals;

        positions.push_back(0);
        A_vals.push_back(0);
        B_vals.push_back(LLONG_MAX);

        for (const auto& station : stations) {
            positions.push_back(station.x);
            A_vals.push_back(station.A);
            B_vals.push_back(station.B);
        }

        positions.push_back(D);
        A_vals.push_back(0);
        B_vals.push_back(LLONG_MAX);

        int M = positions.size();
        vector<tuple<int64_t, int64_t, int64_t>> allStations(M);
        for (int i = 0; i < M; ++i) {
            allStations[i] = make_tuple(positions[i], A_vals[i], B_vals[i]);
        }

        sort(allStations.begin(), allStations.end());

        for (int i = 0; i < M; ++i) {
            positions[i] = get<0>(allStations[i]);
            A_vals[i] = get<1>(allStations[i]);
            B_vals[i] = get<2>(allStations[i]);
        }

        vector<int64_t> required_fuel(M);
        required_fuel[M - 1] = 0;

        for (int i = M - 2; i >= 0; --i) {
            int64_t dist = positions[i + 1] - positions[i];
            int64_t required_fuel_before = required_fuel[i + 1] + dist;

            if (required_fuel_before <= B_vals[i]) {
                required_fuel[i] = max(int64_t(0), required_fuel_before - A_vals[i]);
            } else {
                required_fuel[i] = required_fuel_before;
            }

            required_fuel[i] = max(required_fuel[i], int64_t(0));
        }

        return required_fuel[0];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int64_t N, D;
    cin >> N >> D;

    Journey journey;
    journey.N = N;
    journey.D = D;
    journey.stations.resize(N);

    for (int64_t i = 0; i < N; ++i) {
        cin >> journey.stations[i].x >> journey.stations[i].A >> journey.stations[i].B;
    }

    int64_t minInitialFuel = journey.cMIF();
    cout << minInitialFuel << endl;

    return 0;
}
