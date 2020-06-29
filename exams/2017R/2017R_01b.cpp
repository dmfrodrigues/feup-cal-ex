#include <bits/stdc++.h>
using namespace std;

int main(){
    // Input
    size_t N; cin >> N;
    vector<int> S(N); for(size_t i = 0; i < N; ++i) cin >> S[i];
    // Process
    vector< unordered_map<int, size_t> > T(N+1);
    vector< unordered_map<int, int> > prev(N+1);
    T[1][S[0]] = 0; prev[0][0] = -1;
    for(size_t i = 1; i < N; ++i){
        for(const auto &s_: T[i]){
            const int &s = s_.first;
            if(T[i+1].count(s) == 0 || T[i+1][s] > T[i][s]){
                T[i+1][s] = T[i][s]; prev[i+1][s] = s;
            }
            if(s == S[i-1] && 
              (T[i+1].count(S[i]) == 0 || T[i+1][S[i]] > T[i][s] + 1)){
                T[i+1][S[i]] = T[i][s] + 1; prev[i+1][S[i]] = s;
            }
        }
    }
    
    // Get output
    list<size_t> new_sequence;
    int current_s = S[N-1];
    for(ssize_t i = N; i > 1; --i){
        int prev_s = prev[i][current_s];
        if(T[i-1][prev_s] != T[i][current_s]){
            new_sequence.push_front(i-1);
        }
        current_s = prev_s;
    }
    // Print
    cout << new_sequence.size() << endl;
    for(const size_t &i: new_sequence) cout << i << endl;
    return 0;
}
