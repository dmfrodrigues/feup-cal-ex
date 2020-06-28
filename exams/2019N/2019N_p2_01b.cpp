#include <bits/stdc++.h>
using namespace std;

vector< vector<uint8_t> > M, visited;

int dfs(int h, int w){
    if(visited[h][w] || !M[h][w]) return 0;
    const size_t &H = M.size(), &W = M[0].size();
    visited[h][w] = true;
    int ret = 1;
    if(h-1 >= 0) ret += dfs(h-1, w);
    if(h+1 <  H) ret += dfs(h+1, w);
    if(w-1 >= 0) ret += dfs(h, w-1);
    if(w+1 <  W) ret += dfs(h, w+1);
    return ret;
}

int main(){
    int H, W; cin >> H >> W;
    M = vector< vector<uint8_t> >(H, vector<uint8_t>(W));
    visited = vector< vector<uint8_t> >(H, vector<uint8_t>(W, false));
    for(int h = 0; h < H; ++h) for(int w = 0; w < W; ++w) cin >> M[h][w];

    int max_island_area = 0;
    for(int h = 0; h < H; ++h){
        for(int w = 0; w < W; ++w){
            max_island_area = max(max_island_area, dfs(h, w));
        }
    }

    cout << max_island_area << endl;
    return 0;
}
