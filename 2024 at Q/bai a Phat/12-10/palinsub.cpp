#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n;
    cin >> n;
    vector<string> a(n); // 0-based indexing
    vector<int> start(n), end(n);
    string S = "";
    int idx = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        start[i] = idx;
        idx += a[i].size();
        end[i] = idx - 1;
        S += a[i];
    }
    int L = S.size();
    vector<vector<bool>> palin(L, vector<bool>(L, false));

    // Precompute palindromic substrings in S
    for (int i = 0; i < L; ++i) {
        // Odd length palindromes
        int l = i, r = i;
        while (l >= 0 && r < L && S[l] == S[r]) {
            palin[l][r] = true;
            --l; ++r;
        }
        // Even length palindromes
        l = i, r = i + 1;
        while (l >= 0 && r < L && S[l] == S[r]) {
            palin[l][r] = true;
            --l; ++r;
        }
    }

    // Map each position in S to the corresponding string in a
    vector<int> pos_to_string(L, -1);
    for (int i = 0; i < n; ++i) {
        for (int pos = start[i]; pos <= end[i]; ++pos) {
            pos_to_string[pos] = i;
        }
    }

    long long result = 1; // Start with 1 to account for the empty subsequence

    // Process each palindromic substring
    for (int l = 0; l < L; ++l) {
        for (int r = l; r < L; ++r) {
            if (palin[l][r]) {
                vector<int> indices;
                int pos = l;
                bool valid = true;
                while (pos <= r) {
                    int k = pos_to_string[pos];
                    if (k == -1) {
                        valid = false;
                        break;
                    }
                    int s = start[k];
                    int e = end[k];
                    if (s < l || e > r) {
                        valid = false;
                        break;
                    }
                    // Add the string index if it's not the same as the last one
                    if (indices.empty() || indices.back() != k) {
                        indices.push_back(k);
                    }
                    pos = e + 1;
                }
                if (valid) {
                    // Check if indices are in increasing order
                    bool increasing = true;
                    for (size_t i = 1; i < indices.size(); ++i) {
                        if (indices[i - 1] >= indices[i]) {
                            increasing = false;
                            break;
                        }
                    }
                    if (increasing) {
                        // Verify that concatenating a[indices] gives S[l..r]
                        string concat_str = "";
                        for (int idx : indices) {
                            concat_str += a[idx];
                        }
                        if (concat_str == S.substr(l, r - l + 1)) {
                            result = (result + 1) % MOD;
                        }
                    }
                }
            }
        }
    }

    cout << result << endl;
    return 0;
}
