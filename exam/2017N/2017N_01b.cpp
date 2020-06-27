#include <bits/stdc++.h>
using namespace std;

struct iw: public pair<int,int>{
    iw(int n1 = 0, int n2 = 0):pair<int,int>(n1,n2){}
    int i(){ return first; } int w(){ return second; }
};
struct sol_t { int h, H; iw prev;};
const sol_t null_solution = {-1, -1, iw(-1,-1)};

int main(){
    // Input
    int LP; cin >> LP;
    int n; cin >> n;
    vector<int> L(n), A(n);
    for(int i = 0; i < n; ++i) cin >> L[i] >> A[i];
    // Compute solution
    vector<vector<sol_t> > S(n+1,vector<sol_t>(LP+1, null_solution));
    S[0][0] = {0, 0, iw(-1,-1)};
    for(int i = 0; i < n; ++i){
        for(int w = 0; w < LP; ++w){
            const sol_t &s = S[i][w];
            if(s.h == -1) continue;
            if(w+L[i] < LP){
                sol_t &s1 = S[i+1][w+L[i]];
                if(s1.h == -1 || s.H < s1.H)
                    s1 = {max(s.h, A[i]), s.H, iw(i, w)};
            }
        }
    }
    // Get best solution
    iw best;
    int total_height = 1000000000;
    for(int w = 0; w <= LP; ++w){
        const sol_t &s = S[n][w];
        if(s.h + s.H < total_height){
            total_height = s.h + s.H; best = iw(n, w);
        }
    }
    // Track solutions to see where shelves start
    sol_t cur = S[best.i()][best.w()];
    list<int> shelves;
    for(int i = n; i > 0; --i){
        int H1 = S[cur.prev.i()][cur.prev.w()].H, H2 = cur.H;
        if(H1 != H2) shelves.push_back(i-1);
    }
    // Print solution
    cout << total_height << "\n";
    cout << shelves.size() << "\n";
    for(const int &s: shelves) cout << s << " "; cout << endl;
    return 0;
}