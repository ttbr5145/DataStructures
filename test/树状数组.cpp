#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5;
int n,m;

int lowbit(int x){return x&-x;}
int tr[maxn+10];
void init(){memset(tr,0,sizeof tr);return;}
void add(int pos,int x){for(int i=pos;i<=n;i+=lowbit(i))tr[i]+=x; return;}
int presum(int pos){//Çó1~posµÄºÍ
    int res=0;
    for(int i=pos;i>=1;i-=lowbit(i)) res+=tr[i];
    return res;
}
int query(int frm,int to){return presum(to)-presum(frm-1);}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        add(i,x);
    }
    while(m--){
        int k,a,b;cin>>k>>a>>b;
        if(--k)printf("%d\n",query(a,b));
        else add(a,b);
    }
}
