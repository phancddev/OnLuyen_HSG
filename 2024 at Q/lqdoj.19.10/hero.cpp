#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAX_N = 1005;  
const int MAX_HP = 205;  
const int INF = 1e9;

struct State {
    int kills;
    int prev_pos;
    int prev_h;
    int prev_p;
    bool fought;
};

int n, h0, p0;
int a[MAX_N];
int dp[MAX_N][MAX_HP][MAX_HP];
State from[MAX_N][MAX_HP][MAX_HP];

int main() {
    freopen("hero.inp", "r", stdin);
    freopen("hero.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> p0 >> h0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    int MAX_H = h0 + n + 5;
    int MAX_P = p0 + n + 5;

    
    for (int i = 0; i <= n; ++i) {
        for (int h = 0; h < MAX_H; ++h) {
            for (int p = 0; p < MAX_P; ++p) {
                dp[i][h][p] = INF;
            }
        }
    }

    dp[0][h0][p0] = 0;

    for (int pos = 0; pos < n; ++pos) {
        for (int h = 1; h < MAX_H; ++h) {
            for (int p = 1; p < MAX_P; ++p) {
                if (dp[pos][h][p] != INF) {
                    int kills = dp[pos][h][p];
                    int ai = a[pos + 1];

                   
                    if (ai == 0) {
                        if (dp[pos + 1][h][p] > kills) {
                            dp[pos + 1][h][p] = kills;
                            from[pos + 1][h][p] = {kills, pos, h, p, false};
                        }
                    }

                   
                    if (ai == 1) {
                        int p_new = min(p + 1, MAX_P - 1);
                        if (dp[pos + 1][h][p_new] > kills) {
                            dp[pos + 1][h][p_new] = kills;
                            from[pos + 1][h][p_new] = {kills, pos, h, p, false};
                        }
                    }

                    
                    if (ai == 2) {
                        int h_new = min(h + 1, MAX_H - 1);
                        if (dp[pos + 1][h_new][p] > kills) {
                            dp[pos + 1][h_new][p] = kills;
                            from[pos + 1][h_new][p] = {kills, pos, h, p, false};
                        }
                    }

                    
                    if (ai == 3) {
                       
                        if (h > 1) {
                            int h_new = h - 1;
                            if (dp[pos + 1][h_new][p] > kills) {
                                dp[pos + 1][h_new][p] = kills;
                                from[pos + 1][h_new][p] = {kills, pos, h, p, false};
                            }
                        }
                        
                        if (p > 1) {
                            int p_new = p - 1;
                            int kills_new = kills + 1;
                            if (dp[pos + 1][h][p_new] > kills_new) {
                                dp[pos + 1][h][p_new] = kills_new;
                                from[pos + 1][h][p_new] = {kills_new, pos, h, p, true};
                            }
                        }
                    }
                }
            }
        }
    }

    
    int minK = INF;
    int end_h = -1, end_p = -1;
    for (int h = 1; h < MAX_H; ++h) {
        for (int p = 1; p < MAX_P; ++p) {
            if (dp[n][h][p] < minK) {
                minK = dp[n][h][p];
                end_h = h;
                end_p = p;
            }
        }
    }

    if (minK == INF) {
        cout << -1 << endl;
        return 0;
    }


    vector<int> killedPos;
    int pos = n;
    int h = end_h;
    int p = end_p;
    while (pos > 0) {
        State s = from[pos][h][p];
        if (s.fought) {
            killedPos.push_back(pos);
        }
        int prev_h = s.prev_h;
        int prev_p = s.prev_p;
        h = prev_h;
        p = prev_p;
        pos = s.prev_pos;
    }


    cout << minK << endl;
    for (size_t i = 0; i < killedPos.size(); ++i) {
        cout << killedPos[i];
        if (i != killedPos.size() - 1) {
            cout << " ";
        }
    }
    if (!killedPos.empty())
        cout << endl;

    return 0;
}
