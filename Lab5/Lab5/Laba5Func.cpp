#include "Laba5Func.h"


using namespace std;


void ClientBankShop (int client, int bank, int shop ){
	string BAnk="";
	if(bank==1){
		BAnk="enrolled";
	} else if(bank==0){
		BAnk="ERROR!";
	}else if(bank==2){
		BAnk="";
	}
	cout << "Client has : " << client << endl;
	cout << "Shop has : " << shop << endl;

}


long long ToMd5(long long n){
	long long N = 0;
	unsigned char digest[SHA256_DIGEST_LENGTH];
	string str = to_string(n);
	SHA256_CTX ctx;
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, str.c_str(), str.length());
	SHA256_Final(digest, &ctx);
	for (int i = 0; i < SHA256_DIGEST_LENGTH / 4; ++i, N <<= 1)
		N += long long(digest[i] ^ digest[i + SHA256_DIGEST_LENGTH / 4] ^ digest[i + SHA256_DIGEST_LENGTH / 2] ^ digest[i + SHA256_DIGEST_LENGTH / 4 * 3]);
	return N;
}

void ElectrMoney(){
	srand(time(0));
	int client=rand()+1000;
	int shop=rand()+1000;
	ClientBankShop(client, 2, shop);
//Генерируем ключи
	int Nominal[11]={5000, 2000, 1000, 500, 200, 100, 50, 10, 5, 2, 1};
	int KolBanknot[11]={0,0,0,0,0,0,0,0,0,0,0};
	long long MyMoney[2]={0,0};
	long long P, Q, N, c[11], d[11], FiB;
	long long genNum;
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
	FiB=(P-1)*(Q-1);
	int i;
	for(i=0; i<11;i++){ // i=0-5000, i=1-2000, i=2-1000, i=3-500, i=4-200, i=5-100, i=6-50, i=7-10 RUB
		while(1){
			genNum=500+rand();
			if(genNum<FiB&&evklidSimple(genNum, FiB)==1){
				c[i]=genNum;
				break;	
			}
		}

		d[i]=evklid(FiB,c[i]);
		if(d[i]<0)
			d[i]=(FiB)+d[i]; 
	}
	long long sum;
	cout << "C and D of Nominals are " << endl;
	for (i = 0; i < 11; i++) {
		cout << Nominal[i] << " : " << " C = " << c[i] << " D = " << d[i] << endl;
	}
	while(1){
		if(client==0){
			cout<<"HET DEHEG!!!!"<<endl;
			break;
		}
	while(1){	
		cout<<"Enter the amount of money you want to pay: "<<endl;
		cin>>sum;
		if(sum<=client)
			break;
	}
	//cout << "C and D of Nominals are " << endl;
	for(i=0; i<11; i++){
		if(sum>=Nominal[i]){
			//cout << i << " : " << " C = " << c[i] << " D = " << d[i];
			KolBanknot[i]=sum/Nominal[i];
			sum=sum%Nominal[i];
		}
	}
/*	for(i=0;i<8;i++){
		cout<<"Kol "<<i<<": "<<KolBanknot[i]<<endl;
	}*/
	int j;
	long long BankBanknotReturn[100];
	for(j=0; j<100; j++){
		BankBanknotReturn[j]=0;
	}
//Основные операции
	long long n;
	long long n_M5;
	long long r;
	long long n_NotVision;
	long long s_NotVision;
	long long r_inversion;
	long long s;
	int error=0;
	j=1;
	int er=0;
	for(i=0; i<11; i++){
		bool b = 1;
		while(KolBanknot[i]>0){
			n=rand()%(N-4)+2;
			n_M5 = ToMd5(n);
			cout << " number of = " << Nominal[i] << " N = " << n_M5 << endl;
			while(1){
				r=rand()+2;
				if(evklidSimple(r, N)==1){
					break;
				}
			}
			n_NotVision=((n_M5%N)*vozvedenie(r,d[i],N))%N;
			//cout << "nominal of " << Nominal[i] << " n = " << n << endl;
			s_NotVision=vozvedenie(n_NotVision, c[i], N);
			client-=Nominal[i];
			r_inversion=evklid(N,r);
			if(r_inversion<0)
				r_inversion=N+r_inversion;
			s=(s_NotVision*r_inversion)%N;
		//	cout<<"VOZ: "<<vozvedenie(s,d[i],N)<<"   "<<"Fn: "<<ToMd5(n)<<endl;
			er=0;
			if(vozvedenie(s,d[i],N)== ToMd5(n)){
				for(int l=j-1; l<j; l++){
					if(BankBanknotReturn[l]==n)
						er=1;
				}
				if(er==0){
					BankBanknotReturn[j-1]=n;
					shop+=Nominal[i];
				}	
			}
			KolBanknot[i]--;
			j++;
		}
	}
	if(error==0){
		ClientBankShop(client, 1, shop);
	}else{
		ClientBankShop(client, 0, shop);
	}
	string b;
	cout<<"If you want to exit, enter 'YES' if not enter anything"<<endl;
	cin>>b;
	if(b=="YES")
		break;
	}
}

