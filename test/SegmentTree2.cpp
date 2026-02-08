#include<bits/stdc++.h>
using namespace std;
int n,q,a[1000005],m;
struct node{
	long long sum,l,r,mul,add;
}tree[1000005];
long long read(){
	long long x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
void build(long long p,long long l,long long r){
	tree[p].l=l,tree[p].r=r;tree[p].mul=1;
	if(l==r){tree[p].sum=a[l]%m;return ;}
	long long mid=(l+r)>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	tree[p].sum=(tree[p*2].sum+tree[p*2+1].sum)%m;
}
void spread(long long p){
    tree[p*2].sum=(long long)(tree[p].mul*tree[p*2].sum+((tree[p*2].r-tree[p*2].l+1)*tree[p].add)%m)%m;
    tree[p*2+1].sum=(long long)(tree[p].mul*tree[p*2+1].sum+(tree[p].add*(tree[p*2+1].r-tree[p*2+1].l+1))%m)%m;//add已经乘过mul啦
	
    tree[p*2].mul=(long long)(tree[p*2].mul*tree[p].mul)%m;
    tree[p*2+1].mul=(long long)(tree[p*2+1].mul*tree[p].mul)%m;

	tree[p*2].add=(long long)(tree[p*2].add*tree[p].mul+tree[p].add)%m;
    tree[p*2+1].add=(long long)(tree[p*2+1].add*tree[p].mul+tree[p].add)%m;
    
    tree[p].mul=1,tree[p].add=0;
}
void add(long long p,long long l,long long r,long long k){
	if(tree[p].l>=l&&tree[p].r<=r){
		tree[p].add=(tree[p].add+k)%m;
		tree[p].sum=(long long)(tree[p].sum+k*(tree[p].r-tree[p].l+1))%m;//只要加上增加的就好
		return ;
	}
	spread(p);
	tree[p].sum=(tree[p*2].sum+tree[p*2+1].sum)%m;
	long long mid=(tree[p].l+tree[p].r)>>1;
	if(l<=mid)add(p*2,l,r,k);
	if(mid<r)add(p*2+1,l,r,k);
	tree[p].sum=(tree[p*2].sum+tree[p*2+1].sum)%m;
	
}
void mul(long long p,long long l,long long r,long long k){
	if(tree[p].l>=l&&tree[p].r<=r){
		tree[p].add=(tree[p].add*k)%m;//比较重要的一步,add要在这里乘上k,因为后面可能要加其他的数而那些数其实是不用乘k的
		tree[p].mul=(tree[p].mul*k)%m;
		tree[p].sum=(tree[p].sum*k)%m;
		return ;
	}
	spread(p);
    tree[p].sum=tree[p*2].sum+tree[p*2+1].sum;
	long long mid=(tree[p].l+tree[p].r)>>1;
	if(l<=mid)mul(p*2,l,r,k);
	if(mid<r)mul(p*2+1,l,r,k);
	tree[p].sum=(tree[p*2].sum+tree[p*2+1].sum)%m;
}
long long ask(long long p,long long l,long long r){
	if(tree[p].l>=l&&tree[p].r<=r){
		return tree[p].sum;
	}
	spread(p);
	long long val=0;
	long long mid=(tree[p].l+tree[p].r)>>1;
	if(l<=mid)val=(val+ask(p*2,l,r))%m;
	if(mid<r)val=(val+ask(p*2+1,l,r))%m;
	return val;
}
int main(){
	cin>>n>>q>>m;
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	build(1,1,n);
	for(int i=1;i<=q;i++){
		int ty=read();
		if(ty==1){
			long long cn=read(),cm=read(),cw=read();
			mul(1,cn,cm,cw);
		}else if(ty==2){
			long long cn=read(),cm=read(),cw=read();
			add(1,cn,cm,cw);
		}else {
			long long cn=read(),cm=read();
			cout<<ask(1,cn,cm)<<endl;
		}
    }
}