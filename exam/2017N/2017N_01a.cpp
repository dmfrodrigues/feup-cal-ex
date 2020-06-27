#include <bits/stdc++.h>
using namespace std;

int main(){
    // Input
    int LP; cin >> LP;
    int n; cin >> n;
    vector<int> L(n), A(n);
    for(int i = 0; i < n; ++i) cin >> L[i] >> A[i];
    // Process with greedy
    list<int> shelves;
    int total_height = 0;
    int cur_shelf = 0;
    int cur_shelf_w = 0;
    int cur_shelf_h = 0;
    for(int i = 0; i < n; ++n){
        if(cur_shelf_w+L[i] > LP){
            total_height += cur_shelf_h; shelves.push_back(i);
            cur_shelf++;
            cur_shelf_w = 0; cur_shelf_h = 0;
        }
        cur_shelf_w += L[i];
        cur_shelf_h = max(cur_shelf_h, A[i]);
    }
    total_height += cur_shelf_h;
    // Print solution
    cout << total_height << endl;
    cout << shelves.size() << endl;
    for(const int &s: shelves) cout << s << " "; cout << endl;
    return 0;
}
