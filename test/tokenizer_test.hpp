inline int read()
{
    int ret=0,f=1; char ch;
    for (ch=getchar();ch<'0' || ch>'9';ch=getchar())
        if (ch=='-') f=-f;
    for (;'0'<=ch && ch<='9';ch=getchar())
        ret=ret*10+ch-'0';
    return ret*f;
}
const int mod = (int)1e6+3;
long long R[mod+1],vR[mod+1];
long long C(long long n,long long m){
    if (n<m) return 0;
    if (n<mod && m<mod) return (R[n]*vR[m]%mod)*vR[n-m]%mod;
    return C(n%mod,m%mod)*C(n/mod,m/mod)%mod;
}
long long power(long long a,long long b){
    long long ret = 1;
    while (b){
        if (b&1) ret = ret*a%mod;
        a = a*a%mod;
        b>>=1;
    }
    return ret;
}
         
int main()
{
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    int T=read();
    R[0] = 1;
    for (int i = 1;i < mod;i++) R[i]=R[i-1]*i%mod;
    vR[mod-1] = power(R[mod-1],mod-2);
    for (int i = mod-2; i>=0 ;i--) vR[i] = vR[i+1]*(i+1)%mod;
    while (T--){
        int n = read(), l=read(), r=read();
        printf("%long longd\n",(C(r-l+n+1,n)+mod - 1)%mod);
    }
    return 0;
}