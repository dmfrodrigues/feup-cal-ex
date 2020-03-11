/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <bits/stdc++.h>

string calcSum(int* sequence, int size){
    int N = size;
    std::vector< std::vector<int> > s(N, vector<int>(N+1, 0));
    for(int l = 0; l < N; ++l){
        for(int r = l+1; r <= N; ++r){
            s[l][r] = s[l][r-1]+sequence[r-1];
        }
    }
    string ret = "";
    for(int m = 1; m <= N; ++m){
        int best = 0;
        int best_min = s[0][m];
        for(int l = 1, r = 1+m; r <= N; ++l, ++r){
            if(best_min > s[l][r]){
                best_min = s[l][r];
                best = l;
            }
        }
        ret += to_string(best_min) + "," + to_string(best) + ";";
    }
    return ret;
}

