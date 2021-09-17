/*The Hunt-Szymanski Algorithm is an algorithm that finds the LCS in O((N + K) log N) time complexity, where N is the maximum length of a string and 
K is the number of matches between the two strings. This is especially useful when the number of 
occurrences of each letter is bounded, like if each letter is guaranteed to appear at most twice or thrice in each string.

For example, if the two strings are "abbcd" and "cdea", the matches would be (0, 3), (3, 0), and (4, 1) 
where the indices are zero-based. Then K would be 3 since there are 3 pairs where the characters of each string are the same. 
Clearly, K = N^2 at worst.
*/


int lcs(char* A, char* B){ /// hash = 935751
    vector <int> adj[256];
    int i, j, l = 0, n = strlen(A), m = strlen(B);
    for (i = 0; i < m; i++) adj[B[i]].push_back(i);

    ar[l++] = -1;
    for (i = 0; i < n; i++){
        for (j = adj[A[i]].size() - 1; j >= 0; j--){
            int x = adj[A[i]][j];
            if (x > ar[l - 1]) ar[l++] = x;
            else ar[lower_bound(ar, ar + l, x) - ar] = x;
        }
    }
    return l - 1;
}
