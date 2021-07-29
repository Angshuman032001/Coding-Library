#include "bits/stdc++.h"
#define sz(x) (int)x.size()

using namespace std;

std::vector<int> pi(const string &s){
    std::vector<int> p(s.length());
    for(int i = 1;i<s.length();i++){
        int g = p[i - 1];
        while(g && s[i] != s[g]) g = p[g - 1];
        p[i] = g + (s[i] == s[g]);
    }
    return p;
}

std::vector<int> match(const string &s, const string &pat){
    std::vector<int> p = pi(pat + "$" + s), ans;
    for(int i = sz(p) - s.length();i<sz(p);i++){
        if(p[i] == pat.length()) ans.push_back(i - 2ll * pat.length());
    }
    return ans;
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    string s = "adsgwadsxdsgwadsgzdsgwadsgz";
    string pat = "dsgwadsgz";

    std::vector<int> res = match(s, pat);

    for(int x : res) cout<<x<<" ";

}