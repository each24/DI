#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <list>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <bits/stdc++.h>
#include "Laba1Func.h"
#include "Laba2Func.h"
#include "Laba3Func.h"
#include <cmath>
#include "md5.h"

using namespace std;


void EP_RSA(){
	long long N, Fi, P, Q; 
	long long B[2]; //A[0]-D A[1]-C
	long long genNum;
//Генерируем ключи для подписи	
	while(1){
		P=rand()+2;
		if(P>1000 && ferma(P)==true){
			//cout<<"P="<<p<<endl;
			break;
		}
	}
	while(1){
		Q=rand()+2;
		if(Q>1000 && ferma(Q)==true){
			//cout<<"P="<<p<<endl;
			break;
		}
	}
	N=P*Q;
	Fi=(P-1)*(Q-1);
	while(1){
		genNum=500+rand();
		if(genNum<Fi&&evklidSimple(genNum, Fi)==1){
			B[0]=genNum;
			break;
			
		}
	}

	B[1]=evklid(Fi,B[0]);
//	cout<<"Cb="<<B[1]<<endl;
	if(B[1]<0)
		B[1]=(Fi)+B[1];
//	cout<<"Cb="<<B[1]<<endl;
//Вычисление хэш-функции
	FILE *input = NULL;
    int number=0;
    string sumNum="";
    input = fopen("img001.jpg", "rb");
 	while(fread(&number, sizeof(int), 1, input)){
  		sumNum=sumNum+to_string(number);
	}
    fclose(input);
	ofstream fout;
	fout.open("hash.txt");
	fout<<md5(sumNum);
	fout.close();
//Считаем ключи
	input = fopen("hash.txt", "rb");
	int byte=0;
	fout.open("EP_RSA.txt");
	while(fread(&byte, sizeof(char), 1, input)){
		fout<<vozvedenie(byte, B[1], N)<<endl;
	}
	fout.close();
	fclose(input);
//ПРОВЕРКА-----ПРОВЕРКА-----ПРОВЕРКА-----ПРОВЕРКА
	ifstream INPUT("EP_RSA.txt");
	string str;
	ofstream OUTPUT("Proverka_EP_RSA.txt");
	int base=0;
	int k=0;
	while(getline(INPUT, str)){
		istringstream ist(str);
		ist>>base;
		k=vozvedenie(base, B[0], N);
		OUTPUT<<char(k);
	}
	OUTPUT.close();
	INPUT.close();
	cout<<"Please see the file with the result"<<endl;
}

void EP_GAMAL(){
//генерируем открытые ключи	
	long long p, q, g, a;
	while(1) {
		q=rand()+2;
		if(ferma(q)==true){
			p=2*q+1;
			if(ferma(p)==true){
				break;
			}
		}
	}
	for(g=2; g<p-1; g++) {
		a=vozvedenie(g,q,p);
		if(a!=1){
			break;
		}
	}
//генерируем закрытый ключ
	long long x;
	x=rand()%(p-4)+2;
//генерируем открый ключ Y
	long long y;
	y=vozvedenie(g,x,p);
//Вычисление хэш-функции
	FILE *input = NULL;
    int number=0;
    string sumNum="";
    input = fopen("img001.jpg", "rb");
 	while(fread(&number, sizeof(int), 1, input)){
  		sumNum=sumNum+to_string(number);
	}
    fclose(input);
	ofstream fout;
	fout.open("hash.txt");
	fout<<md5(sumNum);
	fout.close();
//Вычисление k
	long long k;
	while(1){
		k=rand()%(p-4)+2;
		if(evklidSimple(k, p-1)==1){
			break;
		}
	}
//Вычисление k-1
	long long K;
	K=evklid(p-1,k);
	if(K<0)
		K=(p-1)+K;
//Вычисление r
	long long r;
	r=vozvedenie(g, k, p);
	fout.open("EP_GAMAL.txt");
	fout<<r<<endl;
//Вычисление u
	input = fopen("hash.txt", "rb");
	int byte=0;
	int hxr=0;
	int dev=0;
	long long u=0;
	long long s=0;
	while(fread(&byte, sizeof(char), 1, input)){
		hxr=byte-x*r;
		dev=(hxr/(p-1))-1;
		u=hxr-((p-1)*dev);
		s=(K*u)%(p-1);
		fout<<s<<endl;
	}
	fclose(input);
	fout.close();
//ПРОВЕРКА----ПРОВЕРКА----ПРОВЕРКА
	input = fopen("hash.txt", "rb");
	ifstream fin("EP_GAMAL.txt");
	string str="";
//Чтение R
	getline(fin, str);
	istringstream ist(str);
	ist>>r;
	byte=0;
//Сравнение
	long long temp1;
	long long temp2;
	int EXP=0;
	while(getline(fin, str)){
		istringstream ist(str);
		ist>>s;
		fread(&byte, sizeof(char), 1, input);
		temp1=(vozvedenie(y, r, p)*vozvedenie(r, s, p))%p;
		temp2=vozvedenie(g, byte, p);
		if(temp1!=temp2){
			cout<<"invalid signature"<<endl;
			EXP=1;
			break;
		}
	}
	fin.close();
	fclose(input);
	if(EXP==0){
		cout<<"The signature is valid!"<<endl;
	}
}

void EP_GOST(){
//генерируем p,q,a
	long long p, q, a;
	while(1) {
		q=rand()+2000;
		if(ferma(q)==true){
			p=2*q+1;
			if(ferma(p)==true){
				break;
			}
		}
	}
	while(1){
		a=rand()+2;
		if(vozvedenie(a,q,p)==1){
			break;
		}
	}
//генерируем x и y
	long long x, y;
	x=rand()%(q-2)+1;
	y=vozvedenie(a,x,p);
//Вычисление хэш-функции
	FILE *input = NULL;
    int number=0;
    string sumNum="";
    input = fopen("img001.jpg", "rb");
 	while(fread(&number, sizeof(int), 1, input)){
  		sumNum=sumNum+to_string(number);
	}
    fclose(input);
	ofstream fout;
	fout.open("hash.txt");
	fout<<md5(sumNum);
	fout.close();
//формируем число K
	input = fopen("hash.txt", "rb");
	long long k, r, s;
	int byte=0;
	fout.open("EP_GOST.txt");
	while(fread(&byte, sizeof(char), 1, input)){
		while(1){
			k=rand()%(q-2)+1;
			r=vozvedenie(a,k,p)%q;
			if(r!=0){
				s=(k*byte+x*r)%q;
				if(s!=0){
					break;
				}
			}
		}
		fout<<r<<endl;
		fout<<s<<endl;
	}
	fout.close();
	fclose(input);
//ПРОВЕРКА----ПРОВЕРКА----ПРОВЕРКА----ПРОВЕРКА
	long long h=0, H=0;
	ifstream fin("EP_GOST.txt");
	input = fopen("hash.txt", "rb");
	string strR="", strS="";
	long long u1=0, u2=0, v=0;
	int EXP=0;
	int rh=0, dev=0;
	while(fread(&byte, sizeof(char), 1, input)){
		h=byte;
		H=evklid(q,h);
		if(H<0)
			H=q+H;
		getline(fin, strR);
		istringstream istR(strR);
		istR>>r;
		getline(fin, strS);
		istringstream istS(strS);
		istS>>s;
		u1=(s*H)%q;
		u2=(-r*H)-(((-r*H)/q)-1)*q;
		v=((vozvedenie(a,u1,p)*vozvedenie(y,u2,p))%p)%q;
		if(v!=r){
			cout<<"invalid signature"<<endl;
			EXP=1;
			break;
		}
	}
	
	fclose(input);
	fin.close();
	if(EXP==0){
		cout<<"The signature is valid!"<<endl;
	}	
}
