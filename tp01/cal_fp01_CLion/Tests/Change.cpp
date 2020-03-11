/*
 * Change.cpp
 *
 * (a)
 * Formalmente, o problema pode ser descrito como:
 * Dado um conjunto $S$ de pares $(i,k)$, encontre o subconjunto $C \subseteq S$
 * tal que $\sum_{p \in C}{p_i} < P$ e $K = \sum_{p \in C}{p_k}$ seja máximo.
 *
 * (b)
 * minCoins(i,k)=min(minCoins(i-1,k), minCoins(i,v[i]-k))
 * minCoins(0,k)=(k%v[0]==0? k/v[0] : -1)
 * minCoins(i,0)=0
 * lastCoin(i,k)=(minCoins(i,k) == minCoins(i-1,k) ? lastCoin(i-1,k) : i)
 * lastCoin(0,k)=(k%v[0]==0? 0 : -1 )
 * lastCoin(i,0)=-1
 *
 * (c)
 * v = [1, 2, 5]
 * minCoins:
 * k \ i | 0 | 1 | 2
 * ------|---|---|---
 * 0     | 0 | 0 |
 * 1     | 1 | 1 |
 * 2     | 2 | 1 |
 * 3     | 3 | 2 |
 * 4     | 4 | 2 | 2
 * 5     | 5 | 3 |
 * 6     | 6 |   |
 * 7     | 7 | 4 |
 * 8     | 8 |   |
 * 9     | 9 | 5 | 3
 *
 * lastCoin:
 * k \ i | 0  | 1  | 2
 * ------|----|----|---
 * 0     | -1 | -1 |
 * 1     | 0  | 0  |
 * 2     | 0  | 1  |
 * 3     | 0  | 1  |
 * 4     | 0  | 1  | 1
 * 5     | 0  | 1  |
 * 6     | 0  |    |
 * 7     | 0  | 1  |
 * 8     | 0  |    |
 * 9     | 0  | 1  | 2
 */

#include "Change.h"
#include <bits/stdc++.h>

vector<int> v;
const int INF = 30000;
std::vector< std::vector<int> > mincoins;
void solve(int i, int k){
    int &coins = mincoins[i][k];
    if(coins != INF) return;
    if(k == 0){
        coins = 0;
    }else if(i == 0) {
        coins = (k%v[0] == 0 ? k/v[0] : INF);
    } else{
        solve(i-1, k);
        coins = mincoins[i-1][k];
        if(k-v[i] >= 0) {
            solve(i, k - v[i]);
            coins = min(coins, 1 + mincoins[i][k - v[i]]);
        }
    }
}

string get_change(int i, int k){
    if(k == 0) return "";
    if(i == 0 && mincoins[i][k] == INF) return "-";
    if(i != 0 && mincoins[i][k] == mincoins[i-1][k]) return get_change(i-1, k);
    string s = get_change(i, k-v[i]);
    if(s == "-") return s;
    else return to_string(v[i])+";"+s;
}

string calcChange(int m, int numCoins, int *coinValues){
    v = vector<int>(coinValues, coinValues+numCoins);
    mincoins = vector< vector<int> >(numCoins, vector<int>(m+1, INF));
    solve(numCoins-1, m);

    /*
    for(int j = 0; j < mincoins[0].size(); ++j) {
        for (int i = 0; i < mincoins.size(); ++i) {
            cout << mincoins[i][j] << "\t";
        }
        cout << endl;
    }
    */
    //cout << mincoins[numCoins-1][m] << endl;
    return get_change(numCoins-1, m);
}


