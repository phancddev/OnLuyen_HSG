/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>
#include <string>

using namespace std;


string s;
int dp[2005][2005];
int count=0;
void truyvet(int l, int r) 
{
    if (l == r) 
    {
        cout << s[l];
        return;
    }

    if (s[l] == s[r]) 
    {
        cout << s[l];
        truyvet(l+1,r-1);
        cout << s[r];
        return;
    }

    if (dp[l][r] == dp[l+1][r]) truyvet(l+1,r);
        else truyvet(l,r-1);
}

int main() 
{
    cin >> s;
    int n = s.size();
    for(int len = 1; len <= n; len++)
        for(int l = 0; l < n - len + 1; l++) 
        {
            int r = l + len - 1;
            if (len == 1) 
            {   
                dp[l][r] = 1; 
                continue; 
            }
            if (len == 2) 
            {
                dp[l][r] = 1 + (s[l] == s[r]); 
                continue; 
            }
            dp[l][r] = max(dp[l+1][r], dp[l][r-1]);
            if (s[l] == s[r]) dp[l][r] = max(dp[l][r], 2 + dp[l+1][r-1]);
        }
    truyvet(0, n-1);
    return 0;
}
