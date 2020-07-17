/*
 * Partioning.cpp
 */

#include "Partitioning.h"
#include <bits/stdc++.h>

int s_recursive(int n,int k){
    if(k == 1 || k == n) return 1;
    return s_recursive(n-1,k-1)+k*s_recursive(n-1,k);
}

std::vector< std::vector<int> > s_dyn(20, std::vector<int>(20, -1));
int s_dynamic(int n,int k){
    int &ret = s_dyn[n][k];
    if(ret != -1) return ret;
    if(k == 1 || k == n) return ret = 1;
	return ret = s_dynamic(n-1, k-1)+k*s_dynamic(n-1, k);
}


int b_recursive(int n){
	int ret = 0;
	for(int k = 1; k <= n; ++k) ret += s_recursive(n, k);
    return ret;
}

int b_dynamic(int n){
    int ret = 0;
    for(int k = 1; k <= n; ++k) ret += s_recursive(n, k);
    return ret;
}
