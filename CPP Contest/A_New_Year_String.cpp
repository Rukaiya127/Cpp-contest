#include <bits/stdc++.h>
using namespace std;

static const string P = "2025";
static const vector<char> ALPH = {'0','2','5','6'};
const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;

        // ---------- Option 1: force "2026" ----------
        int best2026 = INF;
        for (int i = 0; i + 3 < n; i++) {
            int cost = 0;
            cost += (s[i]   != '2');
            cost += (s[i+1] != '0');
            cost += (s[i+2] != '2');
            cost += (s[i+3] != '6');
            best2026 = min(best2026, cost);
        }

        // ---------- Option 2: avoid "2025" ----------
        // Build automaton (KMP)
        vector<vector<int>> nxt(4, vector<int>(4));
        for (int st = 0; st < 4; st++) {
            for (int c = 0; c < 4; c++) {
                string cur = P.substr(0, st) + ALPH[c];
                int k = min(4, (int)cur.size());
                while (k > 0 && P.substr(0, k) != cur.substr(cur.size() - k))
                    k--;
                nxt[st][c] = k;
            }
        }

        vector<vector<int>> dp(n+1, vector<int>(4, INF));
        dp[0][0] = 0;

        for (int i = 0; i < n; i++) {
            for (int st = 0; st < 4; st++) {
                if (dp[i][st] == INF) continue;
                for (int c = 0; c < 4; c++) {
                    int nst = nxt[st][c];
                    if (nst == 4) continue; // forbidden
                    int add = (s[i] != ALPH[c]);
                    dp[i+1][nst] = min(dp[i+1][nst],
                                        dp[i][st] + add);
                }
            }
        }

        int bestNo2025 = INF;
        for (int st = 0; st < 4; st++)
            bestNo2025 = min(bestNo2025, dp[n][st]);

        cout << min(best2026, bestNo2025) << '\n';
    }
    return 0;
}
