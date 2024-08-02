#include<bits/stdc++.h>
#include<iostream>
#include<random>
#include<ctime>
#define _for(i,a,b) for(int i = a; i <= b; i++)
#define _rfor(i,a,b) for(int i=a; i>=b; i--)
using namespace std;
default_random_engine e;
bernoulli_distribution u(0.5); // 随机结果为（0或）1的概率（各）为0.5
void rrand()
{
    cout<<u(e)<<' ';
}
int main()
{
    e.seed(time(0));
	_for(i,1,10) rrand();
    return 0;
}