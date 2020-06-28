#include <bits/stdc++.h>
using namespace std;

vector< vector<uint8_t> > M, visited;
void dfs(int h, int w){
    if(visited[h][w] || !M[h][w]) return;
    const size_t &H = M.size(), &W = M[0].size();
    visited[h][w] = true;
    if(h-1 >= 0) dfs(h-1, w);
    if(h+1 <  H) dfs(h+1, w);
    if(w-1 >= 0) dfs(h, w-1);
    if(w+1 <  W) dfs(h, w+1);
}

int main(){
    int H, W; cin >> H >> W;
    M = vector< vector<uint8_t> >(H, vector<uint8_t>(W));
    visited = vector< vector<uint8_t> >(H, vector<uint8_t>(W, false));
    for(int h = 0; h < H; ++h) for(int w = 0; w < W; ++w) cin >> M[h][w];
    
    int num_islands = 0;
    for(int h = 0; h < H; ++h){
        for(int w = 0; w < W; ++w){
            if(M[h][w] && !visited[h][w]){
                ++num_islands;
                dfs(h, w);
            }
        }
    }

    cout << num_islands << endl;
    return 0;
}
