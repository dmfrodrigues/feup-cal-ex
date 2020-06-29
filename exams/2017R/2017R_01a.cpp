#include <bits/stdc++.h>
using namespace std;

int main(){
    // Input
    size_t N; cin >> N;
    vector<int> S(N);
    for(size_t i = 0; i < N; ++i)
        cin >> S[i];
    // Get last occurence of each digit
    unordered_map<int, size_t> last_occurence;
    for(ssize_t i = N-1; i >= 0; --i)
        if(!last_occurence.count(S[i]))
            last_occurence[S[i]] = i;
    // Create sequences
    list<size_t> new_sequence;
    size_t l = 0;
    while(l < N){
        l = last_occurence[S[l]]+1;
        new_sequence.push_back(l);
    }
    new_sequence.pop_back();
    // Print
    cout << new_sequence.size() << endl;
    for(const size_t &i: new_sequence)
        cout << i << endl;
    return 0;
}
