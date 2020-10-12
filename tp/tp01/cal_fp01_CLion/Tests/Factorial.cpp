/*
 * Factorial.cpp
 */

#include "Factorial.h"
#include <bits/stdc++.h>

int factorialRecurs(int n){
    if(n == 0) return 1;
	return n*factorialRecurs(n-1);
}

std::vector<long long> fac(1, 1);
int factorialDinam(int n){
    while(n >= fac.size()){
        long long m = fac.size();
        fac.push_back(fac[m-1]*m);
    }
    return fac[n];
}

/**
 * Para M perguntas de fatoriais até N!:
 * A 1ª abordagem tem complexidade temporal O(MN) e espacial O(N).
 * A 2ª abordagem tem complexidade temporal O(N), e espacial O(N).
 */
