#include<bits/stdc++.h>
#define _for(i,a,b) for(int i=a;i<=b;i++)
#define __for(i,a,b) for(int i=a;i>=b;i--)
typedef unsigned long long ull;
using namespace std;
const int maxn=1e5;

int main(){
	int next[maxn+10];
	string s1,s2;
	cin>>s1>>s2;
	s1="0"+s1,s2="0"+s2;//化为从1开始的字符串 
	memset(next,0,sizeof(next));
	next[1]=0;
	int j=0;
	_for(i,2,s2.length()-1){//求最长公共前后缀next
		while(j&&s2[i]!=s2[j+1])j=next[j];
		if(s2[i]==s2[j+1])j++;
		next[i]=j;
	}
	j=0;
	_for(i,1,s1.length()-1){
		while(j&&(j==s2.length()-1||s1[i]!=s2[j+1]))j=next[j];//匹配失败，跳跃
		if(s1[i]==s2[j+1])j++;                                //匹配成功，继续匹配下一位
		if(j==s2.length()-1)printf("%d\n",i-s2.length()+2);   //完全匹配则输出
	}
	_for(i,1,s2.length()-1)printf("%d ",next[i]);
	putchar('\n');
	return 0;
}
