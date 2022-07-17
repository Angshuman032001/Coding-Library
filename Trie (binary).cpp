const int mx_bit = 31;

class Trie{
private:
    int cnt;
    Trie* child[2];
public:
    Trie(){
        this->cnt = 0;
        this->child[0] = this->child[1] = NULL;
    }
    
    void insert(int value, Trie* root){
        Trie* curr = root;
        for(int i = mx_bit; i>=0; i--){
            int bitValue = (value >> i) & 1;
            if(root->child[bitValue] == NULL) root->child[bitValue] = new Trie();
            root = root->child[bitValue];
            root->cnt++;
        }
    }

    int remove(int value, Trie* root, int i = mx_bit){
        if(i < 0) return 1;
        if(root == NULL) return 0;
        int d = (value >> i) & 1;
        if(root->child[d]){
            int g = remove(value, root->child[d], i - 1);
            root->child[d]->cnt -= g;
            if(root->child[d]->cnt == 0){
                delete root->child[d];
                root->child[d] = nullptr;
                return 1;
            }
            return g;
        }
        return 0;
    }

    int maxXor(int value, Trie* root){
        int max_xor = 0;
        Trie *curr = root;
        for(int i = mx_bit; i>=0; i--){
            int bitValue = (value >> i) & 1;
            if(curr->child[!bitValue] != NULL){
                max_xor |= (1 << i);
                curr = curr->child[!bitValue];
            }
            else curr = curr->child[bitValue];
        }
        return max_xor;
    }

    int minXor(int value, Trie* root){
        int min_xor = 0;
        Trie *curr = root;
        for(int i = mx_bit; i>=0; i--){
            int bitValue = (value >> i) & 1;
            if(curr->child[bitValue] != NULL){
                curr = curr->child[bitValue];
            }
            else{ 
                min_xor |= (1 << i);
                curr = curr->child[!bitValue];
            }
        }
        return min_xor;
    }

    //count of entries in the array such that a[i] xor x >= k
    int greaterThan(Trie* root, int x, int k){
        int ans = 0;
        for (int i = mx_bit; i >=0 ; --i){
            int bit = ((x & (1 << i)) != 0);
            // ith bit is set on both x and k
            if((x & (1 << i)) and (k & (1 << i))){
                if(root->child[0] == nullptr) return ans;
                root = root->child[0];
            }
            else if((x & (1 << i)) and !(k & (1 << i))){
                if(root->child[0] != nullptr) 
                    ans += root->child[0]->cnt;
                if(root->child[1] == nullptr)
                    return ans;
                root = root->child[1];
            }
            else if(!(x & (1 << i)) and (k & (1 << i))){
                if(root->child[1] == nullptr)
                    return ans;
                root = root->child[1];
            }
            else if(!(x & (1 << i)) and !(k & (1 << i))){
                if(root->child[1] != nullptr) 
                    ans += root->child[1]->cnt;
                if(root->child[0] == nullptr)
                    return ans;
                root = root->child[0];
            }
        }
        ans += root->cnt;
        return ans;
    }
};

//https://codeforces.com/contest/706/problem/D
//https://codeforces.com/contest/706/submission/164587404


