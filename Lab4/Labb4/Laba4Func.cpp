#include <string>
#include "../../Lab3/LibLab/Laba1Func.h"
#include "Laba4Func.h"


using namespace std;

void MentPoker(){
	int N;
	cout<<"Enter the number of players from 2 to 6:"<<endl;
	string Enter;
	
	while(1){
		cin >> Enter;
		if(Enter=="2"){
			N=2;
			break;	
		}else if(Enter=="3"){
			N=3;
			break;
		}else if(Enter=="4"){
			N=4;
			break;
		}else if(Enter=="5"){
			N=5;
			break;
		}else if(Enter=="6"){
			N=6;
			break;
		}else{
			cout<<"Please enter: from 2 to 6"<<endl;
		}
		
	}
//Определяем ключи игроков
	long long **Players;// [i][0]-c, [i][1]-d
	Players = new long long*[N];
	for (int i = 0; i < N; ++i)
		Players[i] = new long long[2];
	long long P;
	int i;
	while(1){
		P=rand()+2;
		if(P>10000 && ferma(P)==true){
//			cout<<"P="<<P<<endl;
			break;
		}
	}
	long long genNum;
	for(i=0; i<N;i++){
		while(1){
			genNum=500+rand();
			if(genNum<(P-1)&&evklidSimple(genNum, (P-1))==1){
				Players[i][0]=genNum;
				break;
			}
		}
		Players[i][1]=evklid((P-1),Players[i][0]);
		if(Players[i][1]<0)
			Players[i][1]=(P-1)+Players[i][1];
//		cout<<"C="<<Players[i][0]<<"; D="<<Players[i][1]<<" Player"<<i<<endl;
	}
//Определяем карты
	long long Cards[52];
	int SIZE = sizeof(Cards)/sizeof(*Cards);
	int k=102;
	long long tempCard;
	long long CardsTrue[52];
	int CardsName[52];
	int pro=0;
	int Sot=2;
	for(i=0; i<52; i++){
		while(1){
			pro=0;
			if(i==0){
				tempCard=rand()%(P-2)+1;
				break;
			}else{
				tempCard=rand()%(P-2)+1;
				for(int j=0; j<i; j++){
					if(Cards[j]==tempCard)
						pro=1;
				}
			}
			if(pro!=1)
				break;
		}
		if(k%100==15){
			k=100*Sot+2;
			Sot++;
		}
		Cards[i]=tempCard;
		CardsTrue[i]=tempCard;
		CardsName[i]=k;
		k++;
	}
//Вывод проверка	
/*	for(i=0; i<52; i++){
		cout<<"xXxName="<<CardsName[i]<<" Value="<<Cards[i]<<endl;
	}*/
//Смешивание и разадача карт
	int j;
	int l;
	long long TempCard;
	string cardsPlay;
	i=0;
	for(j=0; j<52; j++){
		Cards[j]=vozvedenie(Cards[j], Players[i][0], P);
	}
	random_shuffle(Cards, Cards + SIZE);
	i++;
	while(i!=N+1){
		cardsPlay="";
/*		for(j=0; j<52; j++){
		cout<<"xXxName="<<CardsName[j]<<" Value="<<Cards[j]<<endl;
		}*/
		if(i==N){
			while(1){
				j=rand()%51;
				if(Cards[j]!=0){
					if(i==2){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
					}else if(i==3){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
					}else if(i==4){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[2][1],P );
					}else if(i==5){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[2][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[3][1],P );
					}else if(i==6){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[2][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[3][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[4][1],P );
					}
						
					break;
				}
			}
			TempCard=vozvedenie(Cards[j],Players[i-1][1],P );
			Cards[j]=0;
			for(l=0; l<52; l++){
				if(CardsTrue[l]==TempCard){
					cardsPlay=NameCard(CardsName[l])+";";
				}
			}
			while(1){
				j=rand()%51;
				if(Cards[j]!=0){
					if(i==2){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
					}else if(i==3){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
					}else if(i==4){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[2][1],P );
					}else if(i==5){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[2][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[3][1],P );
					}else if(i==6){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[2][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[3][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[4][1],P );
					}
					break;
				}
			}
			TempCard=vozvedenie(Cards[j],Players[i-1][1],P );
			Cards[j]=0;
			for(l=0; l<52; l++){
				if(CardsTrue[l]==TempCard){
					cardsPlay=cardsPlay+NameCard(CardsName[l])+";";
				}
			}
			cout<<"Player"<<i-1<<": "<<cardsPlay<<endl;
		}else{
			while(1){
				j=rand()%51;
				if(Cards[j]!=0){
				//	cout<<"EX"<<endl;
					if(i==2){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
					}else if(i==3){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
					}else if(i==4){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[2][1],P );
					}else if(i==5){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[2][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[3][1],P );
					}else if(i==6){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[2][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[3][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[4][1],P );
					}
					break;	
				}
			//	cout<<"Value="<<Cards[j]<<endl;
			}
	//		cout<<"Value="<<Cards[j]<<endl;
			TempCard=vozvedenie(Cards[j],Players[i-1][1],P );
//			cout<<"xXxName="<<CardsName[j]<<" Value="<<Cards[j]<<endl;
//			cout<<"TempValue="<<TempCard<<endl;
			Cards[j]=0;
			for(l=0; l<52; l++){
				if(CardsTrue[l]==TempCard){
					cardsPlay=NameCard(CardsName[l])+";";
					
				}
			}
			while(1){
				j=rand()%51;
				if(Cards[j]!=0){
					//cout<<"EX"<<endl;
					if(i==2){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
					}else if(i==3){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
					}else if(i==4){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[2][1],P );
					}else if(i==5){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[2][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[3][1],P );
					}else if(i==6){
						Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[2][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[3][1],P );
						Cards[j]=vozvedenie(Cards[j],Players[4][1],P );
					}
					break;	
				}
	//			cout<<"Value="<<Cards[j]<<endl;
			}
//			cout<<"Value="<<Cards[j]<<endl;
			TempCard=vozvedenie(Cards[j],Players[i-1][1],P );
//			cout<<"TempValue="<<TempCard<<endl;
			Cards[j]=0;
			for(l=0; l<52; l++){
				if(CardsTrue[l]==TempCard){
					cardsPlay=cardsPlay+NameCard(CardsName[l])+";";
				}
			}
			cout<<"Player"<<i-1<<": "<<cardsPlay<<endl;
			for(j=0; j<52; j++){
				if(Cards[j]!=0){
					Cards[j]=vozvedenie(Cards[j], Players[i][0], P);
				}
			}
			random_shuffle(Cards, Cards + SIZE);
		}
		i++;
	}
	i=N;
	int NumCard=5;
	cout<<"Table:"<<endl;
	while(NumCard>0){
	
		while(1){
			cardsPlay="";
			j=rand()%51;
			if(Cards[j]!=0){
				if(i==2){
					Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
				}else if(i==3){
					Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
					Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
				}else if(i==4){
					Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
					Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
					Cards[j]=vozvedenie(Cards[j],Players[2][1],P );
				}else if(i==5){
					Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
					Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
					Cards[j]=vozvedenie(Cards[j],Players[2][1],P );
					Cards[j]=vozvedenie(Cards[j],Players[3][1],P );
				}else if(i==6){
					Cards[j]=vozvedenie(Cards[j],Players[0][1],P );
					Cards[j]=vozvedenie(Cards[j],Players[1][1],P );
					Cards[j]=vozvedenie(Cards[j],Players[2][1],P );
					Cards[j]=vozvedenie(Cards[j],Players[3][1],P );
					Cards[j]=vozvedenie(Cards[j],Players[4][1],P );
				}
				break;
			}
		}
		TempCard=vozvedenie(Cards[j],Players[i-1][1],P );
		Cards[j]=0;
		for(l=0; l<52; l++){
			if(CardsTrue[l]==TempCard){
				cardsPlay=cardsPlay+NameCard(CardsName[l])+";";
			}
		}
		cout<<cardsPlay<<" ";
		NumCard--;
	}
		
	cout<<endl;
}

string NameCard(int number){
	string card="";
	if(number%100<=10){
		card=to_string(number%100);
	}else if(number%100==11){
		card="Valet";
	}else if(number%100==12){
		card="Dama";
	}else if(number%100==13){
		card="Korol";
	}else if(number%100==14){
		card="Tuz";
	}
	if(number/100==1){
		card=card+" "+"chervi";
	}else if(number/100==2){
		card=card+" "+"piki";
	}else if(number/100==3){
		card=card+" "+"bubi";
	}else if(number/100==4){
		card=card+" "+"kresti";
	}
	return card;
}

