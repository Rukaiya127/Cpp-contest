#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--){
        long long a,b;
        cin >> a >> b;

        int ans = 0;
        for(int start = 0; start < 2; start++){
            long long w = a, d = b;
            long long sz = 1;
            int layers = 0;

            while(true){
                if((layers % 2) == start){
                    if(w < sz) break;
                    w -= sz;
                } else {
                    if(d < sz) break;
                    d -= sz;
                }
                layers++;
                sz <<= 1;
            }
            ans = max(ans, layers);
        }
        cout << ans << '\n';
    }
    return 0;
}
