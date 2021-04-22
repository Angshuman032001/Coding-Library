int fact[N], invfact[N];
 
int modinv(int k){
  return power(k, mod-2, mod);
}
 
void precompute(){

  fact[0]=fact[1]=1;
  for(int i=2;i<N;i++){
    fact[i]=fact[i-1]*i;
    fact[i]%=mod;
  }
  invfact[N-1]=modinv(fact[N-1]);
  for(int i=N-2;i>=0;i--){
    invfact[i]=invfact[i+1]*(i+1);
    invfact[i]%=mod;
  }
}
 
int nCr(int x, int y){

  if(y>x)
    return 0;
  int num=fact[x];
  num*=invfact[y];
  num%=mod;
  num*=invfact[x-y];
  num%=mod;
  return num;
}