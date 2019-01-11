// Lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "../../Lab3/LibLab/Laba1Func.h"
#include "../Labb4/Laba4Func.h"

using namespace std;

long long Cards[2][52];

int main()
{
	//MentPoker();
	int N, n;
	// defining cards
	for (int i = 0; i < 52; ++i)
		Cards[0][i] = i;
	cout << "\ninsert number of players\n";
	cin >> N;
	//creating keys for players
	long long **Players;// [i][0]-c, [i][1]-d
	Players = new long long*[N];
	for (int i = 0; i < N; ++i)
		Players[i] = new long long[2];
	long long P, tempCard, pro;
	int i, j;
	while (1) {
		P = rand() + 2;
		if (P > 10000 && ferma(P) == true) {
			//			cout<<"P="<<P<<endl;
			break;
		}
	}
	long long genNum;
	for (i = 0; i < N; i++) {
		while (1) {
			genNum = 500 + rand();
			if (genNum < (P - 1) && evklidSimple(genNum, (P - 1)) == 1) {
				Players[i][0] = genNum;
				break;
			}
		}
		Players[i][1] = evklid((P - 1), Players[i][0]);
		if (Players[i][1] < 0)
			Players[i][1] = (P - 1) + Players[i][1];

		//		cout<<"C="<<Players[i][0]<<"; D="<<Players[i][1]<<" Player"<<i<<endl;
	}
	//defyning cards long long numbers

	for (i = 0; i < 52; i++) {
		while (1) {
			pro = 0;
			tempCard = rand() % (P - 2) + 1;
			for (int j = 0; j < i; j++) {
				if (Cards[1][j] == tempCard)
					pro = 1;
			}
			if (pro != 1)
				break;
		}
		Cards[1][i] = tempCard;
	}
	long long PlayCards[52];
	for (int i = 0; i < 52; ++i)
		PlayCards[i] = Cards[1][i];

	i = 0;
	for (j = 0; j < 52; j++) {
		PlayCards[j] = vozvedenie(PlayCards[j], Players[i][0], P);
	}
	
	random_shuffle(PlayCards, PlayCards + sizeof(PlayCards)/sizeof(*PlayCards));
	
	i++;
	string cardsPlay;
	while (i != N + 1) {
		cardsPlay = "";
		/*		for(j=0; j<52; j++){
				cout<<"xXxName="<<CardsName[j]<<" Value="<<Cards[j]<<endl;
				}*/
		if (i == N) {
			string play = "";
			while (1) {
				j = rand() % 51;
				if (PlayCards[j] != 0) {
					for (int g = 0; g < i - 1; ++g)
						PlayCards[j] = vozvedenie(PlayCards[j], Players[g][1], P);
					break;
				}
			}
			tempCard = vozvedenie(PlayCards[j], Players[i - 1][1], P);
			PlayCards[j] = 0;
			for (int l = 0; l < 52; l++) {
				if (Cards[1][l] == tempCard) {
					play += to_string(Cards[0][l]) + " ";
					//cout << Cards[0][l] << endl;
					//cardsPlay = NameCard(CardsName[l]) + ";";
				}
			}
			while (1) {
				j = rand() % 51;
				if (PlayCards[j] != 0) {
					for (int g = 0; g < i - 1; ++g)
						PlayCards[j] = vozvedenie(PlayCards[j], Players[g][1], P);
					break;
				}
			}
			tempCard = vozvedenie(PlayCards[j], Players[i - 1][1], P);
			PlayCards[j] = 0;
			for (int l = 0; l < 52; l++) {
				if (Cards[1][l] == tempCard) {
					play += to_string(Cards[0][l]) + " ";
					//cout << Cards[0][l] << endl;
					//cardsPlay = cardsPlay + NameCard(CardsName[l]) + ";";
				}
			}
			cout << "Player" << i - 1 << ": " << play << endl;
			//cout << "Player" << i - 1 << ": " << tempCard << endl;
		}
		else {
			while (1) {
				j = rand() % 51;
				if (PlayCards[j] != 0) {
					//cout<<"EX"<<endl;
					for (int g = 0; g < i - 1; ++g)
						PlayCards[j] = vozvedenie(PlayCards[j], Players[g][1], P);
					break;
				}
					//cout<<"Value="<< PlayCards[j]<<endl;
			}
			//cout<<"Value="<< PlayCards[j]<<endl;
			tempCard = vozvedenie(PlayCards[j], Players[i - 1][1], P);
			//			cout<<"xXxName="<<CardsName[j]<<" Value="<<Cards[j]<<endl;
			//			cout<<"TempValue="<<TempCard<<endl;
			PlayCards[j] = 0;
			string play = "";
			for (int l = 0; l < 52; l++) {
				if (Cards[1][l] == tempCard) {
					//cardsPlay = NameCard(CardsName[l]) + ";";
					//cout << Cards[0][l] << endl;
					play += to_string(Cards[0][l]) + " ";
				}
			}
			while (1) {
				j = rand() % 51;
				if (PlayCards[j] != 0) {
					//cout<<"EX"<<endl;
					for (int g = 0; g < i - 1; ++g)
						PlayCards[j] = vozvedenie(PlayCards[j], Players[g][1], P);
					break;
				}
				//			cout<<"Value="<<Cards[j]<<endl;
			}
			//cout<<"Value="<< PlayCards[j]<<endl;
			tempCard = vozvedenie(PlayCards[j], Players[i - 1][1], P);
			//			cout<<"TempValue="<<TempCard<<endl;
			PlayCards[j] = 0;
			for (int l = 0; l < 52; l++) {
				if (Cards[1][l] == tempCard) {
					//cout << Cards[0][l] << endl;
					//cardsPlay = cardsPlay + NameCard(CardsName[l]) + ";";
					play += to_string(Cards[0][l]) + " ";
				}
			}
			cout << "Player" << i - 1 << ": " << play << endl;
			for (j = 0; j < 52; j++) {
				if (PlayCards[j] != 0) {
					PlayCards[j] = vozvedenie(PlayCards[j], Players[i][0], P);
				}
			}
			random_shuffle(PlayCards, PlayCards + sizeof(PlayCards) / sizeof(*PlayCards));
		}
		i++;
	}
    //std::cout << "Hello World!\n"; 
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
