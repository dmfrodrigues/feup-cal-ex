#include <bits/stdc++.h>
using namespace std;

int main(){
    // Input
    int N; cin >> N;
    vector<int> pos(N), value(N);
    for(int i = 0; i < N; ++i)
        cin >> pos[i] >> value[i];
    // Processing
    list<int> billboards;
    int max_value = 0;
    billboards.push_back(0);
    max_value += value[0];
    for(int i = 1; i < N; ++i){
        if(pos[i] - pos[*billboards.rbegin()] >= 5){
            billboards.push_back(i);
            max_value += value[i];
        }
    }
    // Output
    cout << max_value << endl;
    cout << billboards.size() << endl;
    for(const int &i: billboards) cout << i << " ";
    cout << endl;
    return 0;
}
