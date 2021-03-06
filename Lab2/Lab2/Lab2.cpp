#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <list>
#include <string.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

//путь к файлу

string path = "shamir.txt";
string pathGamal = "gamal.txt";
string pathRSA = "rsa.txt";
string pathVernam = "vernam.txt";
string pathM = "message1.txt";
string pathVernamKey = "vernamKey.txt";
string pathVernamKeyInt = "vernamKeyInt.txt";
string pathV;

long long vozvedenie(long long a, long long b, long long p)
{
	unsigned long result = 1;
	while (b)
	{
		if (b&1 == 0)
		{
			a *= a % p;
		}
		else
		{
			result *= a % p;
		}
		b >>= 1;
	}

	return result % p;
}


//Шифр Шамира
void Shamir() {
	//значение ключа для проверки

	//	int KEY=210697;
	//определение ключа под дешифр вида char

	//	ifstream fin;
	//	fin.open(path);
	/*	FILE *input = NULL;
		input = fopen("shamir.txt", "rb");
		int i=6;
		int byte;
		int key=0;
		if (input != NULL) {
			while(i>0){
				fread(&byte, sizeof(char), 1, input);
				key=key*10+byte;
				i--;
			}
		}
		fclose(input);*/
		//	fin.close();
		//проверка
	int KEY;
	cin >> KEY;
	if (KEY == 1) {
		DeShifrShamir();
	}
	else {
		ShifrShamir();
	}
}

void ShifrShamir(string File, bool Do) {
	long long p;       //простое число p
	long long A[2];		//хранит A[0]-Ca A[1]-Da
	long long B[2];		//хранит B[0]-Cb B[1]-Db
	long long genNum, genNumB;		//для вычисления Dа и Db
	long long m;		//переменная для шифрования
	long long x;		//переменная шифрования

	if (Do) {
		// шифруем
		/*FILE *output = NULL;
		output = fopen(File.c_str(), "wb");*/
		//генерация P
		while (1) {
			p = rand() + 2;
			if (p > 1000 && ferma(p) == true) {
				cout << "P=" << p << endl;
				break;
			}
		}
		//запись в фойл p
		WriteInFile(P, File);
		//генерируем Ca Da Cb Db
		while (1) {
			genNum = 500 + rand();
			if (genNum < p - 1 && evklidSimple(genNum, p - 1) == 1) {
				A[0] = genNum;
				break;

			}
		}
		A[1] = evklid(p - 1, A[0]);
		if (A[1] < 0)
			A[1] = (p - 1) + A[1];
		while (1) {
			genNumB = 600 + rand();
			if (genNumB < p - 1 && evklidSimple(genNumB, p - 1) == 1) {
				B[0] = genNumB;
				break;
			}
		}
		B[1] = evklid(p - 1, B[0]);
		if (B[1] < 0)
			B[1] = (p - 1) + B[1];
		//записываем Da в файл
		WriteInFile(A[1], File);
		//записываем Db в файл
		WriteInFile(B[1], File);
		//шифруем
		long long n = 210697;
		n = vozvedenie(n, A[0], p);
		n = vozvedenie(n, B[0], p);
		WriteInFile(n, File);

		/*
		// шифруем
		FILE *input = NULL;
		input = fopen("img001.jpg", "rb");

		int M;
		while(fread(&M, sizeof(char), 1, input)){
			m=M;
			x=vozvedenie(m,A[0],p);
			x=vozvedenie(x,B[0],p);
			x=vozvedenie(x,A[1],p);
			cout<<"x="<<x<<endl;
			WriteInFile(x, File);		//запись в файл зашифрованного символа
		}
		fclose(input);
		*/
	}
	else {
		//дешифруем
		long long x = 1, P = 0, A = 0, B = 0, key = 0;
		int byte, temp;
		FILE *input = NULL;
		input = fopen(File.c_str(), "rb");
		//прочитали P
		fread(&byte, sizeof(char), 1, input);
		for (int i = 0; i < byte; ++i) {
			fread(&temp, sizeof(char), 1, input);
			P += temp * x;
			x *= 256;
		}
		//прочитали А
		x = 1;
		fread(&byte, sizeof(char), 1, input);
		for (int i = 0; i < byte; ++i) {
			fread(&temp, sizeof(char), 1, input);
			A += temp * x;
			x *= 256;
		}
		//прочитали B
		x = 1;
		fread(&byte, sizeof(char), 1, input);
		for (int i = 0; i < byte; ++i) {
			fread(&temp, sizeof(char), 1, input);
			B += temp * x;
			x *= 256;
		}
		//прочитали key
		x = 1;
		fread(&byte, sizeof(char), 1, input);
		for (int i = 0; i < byte; ++i) {
			fread(&temp, sizeof(char), 1, input);
			key += temp * x;
			x *= 256;
		}
		//дешифруем key
		key = vozvedenie(key, A, p);
		key = vozvedenie(key, B, p);
		cout << key;
	}
	//	ofstream fout(path);
	//	fin.close();
}

void DeShifrShamir() {
	//открываем файл для чтения
	//	ifstream fin(path);
	//добавляем переменные P и Db
	long long p;
	long long Db;
	long long x;
	long long m;
	//выводим ключ шифровки
	FILE *input = NULL;
	input = fopen("shamir.txt", "rb");
	int i = 6;
	int byte;
	int key = 0;
	/*if (input != NULL) {
		while(i>0){
			fread(&byte, sizeof(char), 1, input);
			key=key*10+byte;
			i--;
		}
	}*/
	/*
	char Key[6];
	char ch;
	int i=5;
	int n=0;
	while(i>=0){
		fin.get(ch);
		Key[i]=ch;
		i--;
	}*/
	//переводим ключ шифровки в int

	//	cout<<"Key="<<key<<endl;
	//считываем длину P
	fread(&byte, sizeof(char), 1, input);
	int d;
	d = byte;
	//считываем число P
	int n = 0;
	while (d > 0) {
		fread(&byte, sizeof(char), 1, input);
		n = n * 10 + byte;
		d--;
	}
	p = n;
	cout << "P=" << n << endl;
	//считываем длину Db
	//	fin.get(ch);
	fread(&byte, sizeof(char), 1, input);
	d = byte;
	//считываем число Db
	n = 0;
	while (d > 0) {
		fread(&byte, sizeof(char), 1, input);
		n = n * 10 + byte;
		d--;
	}
	cout << "Db=" << n << endl;
	Db = n;
	//дешифрование
	while (fread(&byte, sizeof(char), 1, input)) {
		d = byte;
		n = 0;
		cout << "d=" << d << '\t';
		while (d > 0) {
			fread(&byte, sizeof(char), 1, input);
			n = n * 10 + byte;
			d--;
		}

		cout << "X=" << n << endl;
		m = vozvedenie(n, Db, p);
		WriteMessageDeShifr(m);
	}
	fclose(input);
	//	fin.close();
}

//Шифр Эль Гамаля
void AlGamal() {

	int KEY = 210697;

	//определение ключа под дешифр вида char
	int i = 5;
	int keyInt = 0;
	char key[6];
	char ch;
	ifstream fin;
	fin.open(pathGamal);
	if (!fin.is_open()) {
		cout << "File not open" << endl;
	}
	else {
		while (i >= 0) {
			fin.get(ch);
			key[i] = ch;
			i--;
		}
		fin.close();
		//определение ключа int	
		for (i = 0; i < 6; i++) {
			keyInt = keyInt * 10 + ((int)key[i] - 97);
		}
	}

	//проверка

	if (KEY == keyInt) {
		DeShifrGamal();
	}
	else {
		ShifrGamal();
	}
}

void ShifrGamal() {
	//записываем ключ шифр или дешифр в файл
	ofstream fout(pathGamal);

	int n = 210697;
	int l;
	while (n > 0) {
		l = n % 10;
		n = n / 10;
		fout << (char)(l + 97);
	}
	fout.close();
	//генерируем значения p и g
	long long p, q, g, a;
	while (1) {
		q = rand() + 2;
		if (ferma(q) == true) {
			p = 2 * q + 1;
			if (ferma(p) == true) {
				break;
			}
		}
	}
	for (g = 2; g < p - 1; g++) {
		a = vozvedenie(g, q, p);
		if (a != 1) {
			break;
		}
	}
	path = pathGamal;
	//записываем в файл значение p и q
	WriteInFile(p);
	//	WriteInFile(g);
	//генерируем открытые и закрытые ключи
	long long A[2], B[2], C[2];
	int i;
	A[0] = 2 + rand() % ((p - 2) - 1);		//Ci
	B[0] = 2 + rand() % ((p - 2) - 1);
	C[0] = 2 + rand() % ((p - 2) - 1);
	A[1] = vozvedenie(g, A[0], p);	//Di
	B[1] = vozvedenie(g, B[0], p);
	C[1] = vozvedenie(g, C[0], p);
	cout << "P=" << p << endl;
	cout << "Cb=" << B[0] << endl;
	//записываем значение секретного ключа получателя в файл
	WriteInFile(B[0]);

	//открываем сообщение для шифрования
	ifstream fin("message.txt");

	if (!fin.is_open()) {
		cout << "NotFile\n";
		exit(0);
	}
	//шифрование
	char ch;
	long long m, k, r, e;
	while (fin.get(ch)) {
		m = (int)ch;
		k = 1 + rand() % ((p - 2) - 1);
		r = vozvedenie(g, k, p);
		cout << "r=" << r << '\t';
		e = m * vozvedenie(B[1], k, p);
		cout << "e=" << e << '\t';
		cout << "m=" << m << endl;
		WriteInFile(r);
		WriteInFile(e);
	}
	fin.close();
}

void DeShifrGamal() {
	//открываем файл для чтения
	ifstream fin(pathGamal);
	//добавляем переменные P и Db
	long long p;
	long long Cb;
	long long m;
	//выводим ключ шифровки
	char Key[6];
	char ch;
	int i = 5;
	int n = 0;
	while (i >= 0) {
		fin.get(ch);
		Key[i] = ch;
		i--;
	}
	//переводим ключ шифровки в int
	for (i = 0; i < 6; i++) {
		n = n * 10 + ((int)Key[i] - 97);
	}
	cout << "Key=" << n << endl;
	//считываем длину P
	fin.get(ch);
	int d;
	d = (int)ch - 97;
	//считываем число P
	n = 0;
	while (d > 0) {
		fin.get(ch);
		n = n * 10 + ((int)ch - 97);
		d--;
	}
	p = n;
	cout << "P=" << n << endl;
	//считываем длину Cb
	fin.get(ch);
	d = (int)ch - 97;
	//считываем число Cb
	n = 0;
	while (d > 0) {
		fin.get(ch);
		n = n * 10 + ((int)ch - 97);
		d--;
	}
	cout << "Cb=" << n << endl;
	Cb = n;
	//дешифрование
	long long r, e;
	long long kof;
	long long uV, uE;
	kof = p - 1 - Cb;
	while (fin.get(ch)) {
		d = (int)ch - 97;
		n = 0;
		//	cout<<"d="<<d<<'\t';
		while (d > 0) {
			fin.get(ch);
			n = n * 10 + ((int)ch - 97);
			d--;
		}
		r = n;
		cout << "r=" << r << '\t';
		fin.get(ch);
		d = (int)ch - 97;
		n = 0;
		//	cout<<"d="<<d<<'\t';
		while (d > 0) {
			fin.get(ch);
			n = n * 10 + ((int)ch - 97);
			d--;
		}
		e = n;
		cout << "e=" << e << '\t';
		//	cout<<"X="<<n<<endl;
		uE = e % p;
		uV = vozvedenie(r, kof, p);
		m = (uE*uV) % p;
		cout << "m=" << m << endl;
		WriteMessageDeShifr(m);
	}
	fin.close();


}
//Шифр RSA
void RSA() {

	int KEY = 210697;

	//определение ключа под дешифр вида char
	int i = 5;
	int keyInt = 0;
	char key[6];
	char ch;
	ifstream fin;
	fin.open(pathRSA);
	if (!fin.is_open()) {
		cout << "File not open" << endl;
	}
	else {
		while (i >= 0) {
			fin.get(ch);
			key[i] = ch;
			i--;
		}
		fin.close();
		//определение ключа int	
		for (i = 0; i < 6; i++) {
			keyInt = keyInt * 10 + ((int)key[i] - 97);
		}
	}
	//проверка
	if (KEY == keyInt) {
		DeShifrRSA();
	}
	else {
		ShifrRSA();
	}
}

void ShifrRSA() {
	//записываем ключ шифр или дешифр в файл
	ofstream fout(pathRSA);

	int n = 210697;
	int l;
	while (n > 0) {
		l = n % 10;
		n = n / 10;
		fout << (char)(l + 97);
	}
	fout.close();
	//определяем переменные для ключей A B C
	long long Na, Nb, Nc, FiA, FiB, FiC;
	long long A[2], B[2], C[2]; //A[0]-Da A[1]-Ca
	long long p, Q;
	long long genNum;
	/*
//генерируем ключи для A
	while(1){
		p=rand()+2;
		if(p>1000 && ferma(p)==true){
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
	Na=p*Q;
	FiA=(p-1)*(Q-1);
	while(1){
		genNum=500+rand();
		if(genNum<FiA&&evklidSimple(genNum, FiA)==1){
			A[0]=genNum;
			break;

		}
	}

	A[1]=evklid(FiA,A[0]);

	if(A[1]<0)
		A[1]=(p-1)+A[1];*/
		//генерируем ключи для B
	while (1) {
		p = rand() + 2;
		if (p > 1000 && ferma(p) == true) {
			//cout<<"P="<<p<<endl;
			break;
		}
	}
	while (1) {
		Q = rand() + 2;
		if (Q > 1000 && ferma(Q) == true) {
			//cout<<"P="<<p<<endl;
			break;
		}
	}
	Nb = p * Q;
	FiB = (p - 1)*(Q - 1);
	while (1) {
		genNum = 500 + rand();
		if (genNum < FiB&&evklidSimple(genNum, FiB) == 1) {
			B[0] = genNum;
			break;

		}
	}

	B[1] = evklid(FiB, B[0]);
	//	cout<<"Cb="<<B[1]<<endl;
	if (B[1] < 0)
		B[1] = (FiB)+B[1];
	cout << "Cb=" << B[1] << endl;
	//генерируем ключи для C
	/*	while(1){
			p=rand()+2;
			if(p>1000 && ferma(p)==true){
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
		Nc=p*Q;
		FiC=(p-1)*(Q-1);
		while(1){
			genNum=500+rand();
			if(genNum<FiC&&evklidSimple(genNum, FiC)==1){
				C[0]=genNum;
				break;

			}
		}

		C[1]=evklid(FiC,C[0]);

		if(C[1]<0)
			C[1]=(p-1)+C[1];*/
			//записываем в файл ключи получателя
	path = pathRSA;
	cout << "Nb=" << Nb << endl;
	WriteInFile(Nb);
	WriteInFile(B[1]);
	//открываем сообщение для шифрования
	ifstream fin("message.txt");

	if (!fin.is_open()) {
		cout << "NotFile\n";
		exit(0);
	}
	//шифрование
	char ch;
	long long m, e;
	while (fin.get(ch)) {
		m = (int)ch;
		e = vozvedenie(m, B[0], Nb);
		//cout<<"r="<<r<<'\t';
		WriteInFile(e);
	}
	fin.close();

}

void DeShifrRSA() {
	//открываем файл для чтения
	ifstream fin(pathRSA);
	//добавляем переменные Nb и Cb
	long long Nb;
	long long Cb;
	long long m;
	//выводим ключ шифровки
	char Key[6];
	char ch;
	int i = 5;
	int n = 0;
	while (i >= 0) {
		fin.get(ch);
		Key[i] = ch;
		i--;
	}
	//переводим ключ шифровки в int
	for (i = 0; i < 6; i++) {
		n = n * 10 + ((int)Key[i] - 97);
	}
	cout << "Key=" << n << endl;
	//считываем длину Nb
	fin.get(ch);
	int d;
	d = (int)ch - 97;
	//считываем число P
	n = 0;
	while (d > 0) {
		fin.get(ch);
		n = n * 10 + ((int)ch - 97);
		d--;
	}
	Nb = n;
	cout << "Nb=" << Nb << endl;
	//считываем длину Cb
	fin.get(ch);
	d = (int)ch - 97;
	//считываем число Cb
	n = 0;
	while (d > 0) {
		fin.get(ch);
		n = n * 10 + ((int)ch - 97);
		d--;
	}
	Cb = n;
	cout << "Cb=" << Cb << endl;
	//дешифрование
	long long e;
	while (fin.get(ch)) {
		d = (int)ch - 97;
		n = 0;
		//	cout<<"d="<<d<<'\t';
		while (d > 0) {
			fin.get(ch);
			n = n * 10 + ((int)ch - 97);
			d--;
		}
		e = n;
		m = vozvedenie(e, Cb, Nb);
		//	cout<<"m="<<m<<endl;
		WriteMessageDeShifr(m);
	}
	fin.close();

}

//Шифр Вернама
void Vernam(string File, string Temp) {
	ShifrVernam(File, Temp);
	DeShifrVernam(File, Temp);
}

void ShifrVernam() {
	FILE *input = NULL;
	input = fopen("img001.jpg", "rb");
	//шифрование
	int byte = 0, e = 0, k = 0;
	while (fread(&byte, sizeof(char), 1, input)) {
		/*	for(i=0;i<8;i++){
				M[i]=0;
				K[i]=0;
				E[i]=0;
			}
			e=0;
			m=(int)ch;*/
		while (1) {
			k = rand() % 240;
			if (k != byte)
				break;
		}
		//cout<<"m="<<m<<'\t'<<"k="<<k<<'\t';
	//	pathV=pathVernamKey;
		WriteInFileOnlyVernamInt(k);
		WriteInFileOnlyVernamKey(k);
		/*	for(i=7;i>=0;i--){
				t=m%2;
				m=m/2;
				M[i]=t;
				t=k%2;
				k=k/2;
				K[i]=t;
				if(K[i]==M[i]){
					E[i]=0;
				}else{
					E[i]=1;
				}
			}
			for(i=0, j=7;i<8;i++,j--){
				x=pow(2,j);
				e+=E[i]*x;
			}*/
		e = byte ^ k;
		cout << "k=" << k << '\t' << "byte=" << byte << '\t' << "e=" << e << endl;
		WriteInFileOnlyVernam(e);
	}
	fclose(input);
}

void DeShifrVernam() {
	//открываем файл для чтения
	//	ifstream fin(pathVernam);
	//	ifstream finKey(pathVernamKey);
	FILE *input = NULL;
	FILE *inputKey = NULL;
	input = fopen("vernam.txt", "rb");
	inputKey = fopen("vernamKey.txt", "rb");
	//выводим ключ шифровки
	 /*	char Key[6];
		char ch, chKey;
		int i=5;
		int n=0;
		while(i>=0){
			fin.get(ch);
			Key[i]=ch;
			i--;
		}
	//переводим ключ шифровки в int
		for(i=0; i<6;i++){
			n=n*10+((int)Key[i]-97);
		}
		cout<<"Key="<<n<<endl;*/
		//дешифрование
			//int byte;

	int byte = 0, k = 0, m = 0;

	while (fread(&byte, sizeof(char), 1, input)) {
		/*for(i=0;i<8;i++){
			M[i]=0;
			K[i]=0;
			E[i]=0;
		}
		e=(int)ch;
		finKey.get(chKey);*/
		fread(&k, sizeof(char), 1, inputKey);
		//		k=(int)chKey;
				/*m=0;
				cout<<"e="<<e<<'\t'<<"k="<<k<<'\t';
				for(i=7;i>=0;i--){
					t=k%2;
					k=k/2;
					K[i]=t;
					t=e%2;
					e=e/2;
					E[i]=t;
					if(K[i]==E[i]){
						M[i]=0;
					}else{
						M[i]=1;
					}
				}
				for(i=0, j=7;i<8;i++,j--){
					x=pow(2,j);
					m+=M[i]*x;
				}*/
		cout << "k=" << k << '\t';
		cout << "Byte=" << byte << '\t';
		m = byte ^ k;
		cout << "m=" << m << endl;
		WriteMessageDeShifr(m);
	}
	fclose(input);
	fclose(inputKey);
}

//запись в файл
void WriteInFileOnlyVernam(int X) {
	/*ofstream fout(pathV,  ios_base::app);
	fout<<(char)X;
	fout.close();*/
	FILE *output = NULL;
	output = fopen("vernam.txt", "ab");
	fwrite(&X, sizeof(char), 1, output);
	fclose(output);
}
void WriteInFileOnlyVernamKey(int X) {
	/*	ofstream fout(pathV,  ios_base::app);
		fout<<(char)X;
		fout.close();*/
	FILE *output = NULL;
	output = fopen("vernamKey.txt", "ab");
	fwrite(&X, sizeof(char), 1, output);
	fclose(output);
}
void WriteInFileOnlyVernamInt(int X, string File) {
	ofstream fout(pathVernamKeyInt, ios_base::app);
	fout << X << ' ';
	fout.close();
}

void WriteInFile(long long X, string File) {
	long long n;
	int l, d, StepenTen;
	//открываем файл
	//ofstream fout(path, ios_base::app);
	FILE *output = NULL;
	output = fopen(File, "ab");
	//определяем длину x
	d = 0; n = X;
	while (n > 255) {
		n /= 255;
		d++;
	}
	//записываем длину x в файл	
	fwrite(&d, sizeof(char), 1, output);
	n = X;
	while (d >= 0) {
		l = n & 255;
		n /= 256;
		d--;
		fwrite(&l, sizeof(char), 1, output);
	}
	//закрываем файл
	fclose(output);
	//	fout.close();
}

void WriteMessageDeShifr(long long m) {
	FILE *output = NULL;
	output = fopen("img101.jpg", "ab");
	fwrite(&m, sizeof(char), 1, output);
	/*	ofstream fout(pathM,  ios_base::app);
		fout<<(char)m;

		fout.close();*/

	fclose(output);
}

main() {
	cout << vozvedenie(255, 1000009, 1000008);
	/*
	ShifrShamir("123.txt", 1);
	ShifrShamir("123.txt", 0);
	*/
	system("PAUSE");
}