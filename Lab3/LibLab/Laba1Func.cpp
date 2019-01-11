#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <list>
//#include <bits/stdc++.h>
#include "Laba1Func.h"


using namespace std;

const int N=100;

struct PR{
	long long data;
	long long value;
};

list<PR> lst[N];

long HKey(long k) {
	return k%N;
}


long long vozvedenie(long long a, long long b, long long p)
{
	long long result = 1;
	while (b)
	{
		if (b & 1)
			result = (result * a) % p;
		a = (a*a) % p;
		b >>= 1;
	}
	return result % p;
}



//Возведение в степень
/*
unsigned functionV(unsigned a, unsigned m, unsigned step){
		if(step > 0){ 
			unsigned c = functionV(a,m,step-1);
			return (c*c)%m;
		}else
			return a%m;
}

unsigned stepen(unsigned a, unsigned b, unsigned m, unsigned step) {
	unsigned pro_ost=1;
	while(b>0){
		if(b&1){
			pro_ost*=functionV(a,m,step);
		}
		b=b>>1;
		step++;
		//cout << step << "  " << a << "  " << num << endl;
	}
	return pro_ost;
}

unsigned vozvedenie(unsigned a, unsigned b, unsigned m) {
	unsigned pro_ost;
	unsigned step=0;
	pro_ost=stepen(a,b,m,step);
	return pro_ost%m;	
}
*/
/*
long vozvedenie(long x, long y, long N)
{
  if (y == 0) return 1;
  long z = vozvedenie(x, y / 2, N);
  if (y % 2 == 0)
    return (z*z) % N;
  else
    return (x*z*z) % N;
}


long long vozvedenie(long long base, long long exponent, long long mod){
    base %= mod;
    long long pow;
    if(exponent == 0){
        pow = 1;
    }
    else if(exponent % 2 == 0){
        pow = vozvedenie(base * base, exponent / 2, mod) % mod;
    }
    else{
        pow = (base * vozvedenie(base, exponent - 1, mod)) % mod;
    }
    return pow;
}
*/
//Алгоритм Евклида простой
long long evklidSimple(long long a, long long b){
	if(b==0)
		return a;
	return evklidSimple(b, a%b);
}

//Тест ферма
bool ferma(long long x){
	if(x == 2)
		return true;
	for(int i=0;i<100;i++){
		long long a = (rand() % (x - 2)) + 2;
		if (evklidSimple(a, x) != 1)
			return false;			
		if( vozvedenie(a, x-1, x) != 1)		
			return false;			
	}
	return true;
}


//Алгоритм Евклида расширенный

long long evklid(long long a, long long b) {
		long long U[3], V[3], T[3];
		long long q;
		long long x, y, NOD;
		if(a>=b){
			U[0]=a;	V[0]=b;
			U[1]=1;	V[1]=0;
			U[2]=0; V[2]=1;

			while(V[0]!=0){
				q=U[0]/V[0];
				T[0]=U[0]%V[0];
				T[1]=U[1]-q*V[1];
				T[2]=U[2]-q*V[2];
				for(int i=0; i<3; i++){
					U[i]=V[i];
					V[i]=T[i];
				}
			}
		} else {
			printf("Error: a<b");
		}
		x=U[1];

		y=U[2];
		NOD=U[0];
		return y;
	}

//Деффи-хелман

void deffi(){
	long long Y[2];
	long long X[2];
	long long Z[2];
	long long q, p, g, k;
	int n=1;
	while(n==1) {
		q=rand()+2;
		if(ferma(q)==true){
			p=2*q+1;
			if(ferma(p)==true){
				n=0;
			}
		}
	}
	for(g=2; g<p-1; g++) {
		k=vozvedenie(g,q,p);
		if(k!=1){
			break;
		}
	}
	for(int i=0;i<2;i++){
		X[i]=1+rand()%30;
	}
	for(int i=0; i<2; i++){
		Y[i]=vozvedenie(g,X[i],p);
		cout<<Y[i]<<endl;
	}
	Z[0]=vozvedenie(Y[1],X[0],p);
	Z[1]=vozvedenie(Y[0],X[1],p);
	
	if(Z[0]==Z[1]){
		printf("Rabotaet!");
	}	
}

//Шаг "младенца" шаг "великана"

void shag() {
	long long m, k, proverka=1, c1, c2, x, u1, I=0, J=0, c, key;
	long long a, p, y;
	int j, n=1;
	while(n==1) {
		p=rand()+2;
		if(ferma(p)==true){
			a=rand()+2;
			if(a<p){
				n=0;
				y=rand()+2;
			}
		}
	}
	printf("p=%lld\n", p);
	while(proverka==1){
		printf("Vvedite m and k: ");
		cin>>m>>k;
		if(m*k<=p){
		} else{
			proverka=0;
		}
	}
	
	for(int i=0; i<m; i++){
		c2=(y%p*vozvedenie(a,i,p))%p;
		if(c2<0)
			c2=-c2;
		key = HKey(c2);
		PR tmp;
		tmp.data = i;
		tmp.value = c2;
	//	printf("value=%lld\n", tmp.value);
		lst[key].push_back(tmp);
	}
	
	for(int i=1;i<=k;i++){
		u1=i*m;
		c1=vozvedenie(a,u1,p);
		if(c1<0)
			c1=-c1;
		key=HKey(c1);
		
		for(auto it=lst[key].begin(); it!=lst[key].end(); it++){
			if(it->value==c1){
		/*		printf("c1=%lld\t", c1);
				printf("value=%lld\n", it->value);*/
				I=i;
				J=it->data;
				c=0;
				x=I*m-J;
				break;
			}
		}
		if(c==0){
			break;
		}
	}
	printf("x = %lld\n", x);
}

