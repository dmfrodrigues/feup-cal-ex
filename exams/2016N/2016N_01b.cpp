#include <bits/stdc++.h>
using namespace std;

int main(){
    // Input
    int N; cin >> N;
    vector<int> pos(N), value(N);
    for(int i = 0; i < N; ++i) cin >> pos[i] >> value[i];
    vector<int> e(N); int current_i = 0;
    for(int i = 0; i < N; ++i){
        while(current_i < N && pos[current_i] - pos[i] < 5) ++current_i;
        e[i] = current_i;
    }
    // Processing
    vector< unordered_map<int, int> > S(N+1), prev(N+1);
    S[0][0] = 0;
    for(int i = 0; i <= N; ++i)
        for(const auto &p: S[i]){
            const int &d = p.first;
            int d_ = pos[i]+5-1;
            if(d <= pos[i] && S[i+1][d_] < S[i][d] + value[i]){
                S[i+1][d_] = S[i][d] + value[i]; prev[i+1][d_] = d;
            }
            if(S[i+1][d] < S[i][d]){
                S[i+1][d] = S[i][d]; prev[i+1][d] = d;
            }
        }
    // Get best answer
    int current_d = 0;
    int max_value = -1;
    for(const auto &p: S[N]){
        const int &d = p.first;
        if(S[N][d] > max_value){
            max_value = S[N][d]; current_d = d;
        }
    }
    // Backtrack
    list<int> billboards;
    for(int i = N; i > 0; --i){
        int prev_d = prev[i][current_d];
        if(S[i][current_d] != S[i-1][prev_d]){
            billboards.push_front(i-1);
        }
        current_d = prev_d;
    }
    // Output
    cout << max_value << endl;
    cout << billboards.size() << endl;
    for(const int &i: billboards) cout << i << " ";
    cout << endl;
    return 0;
}
