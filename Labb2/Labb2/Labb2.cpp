#include "pch.h"
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <list>
#include <string.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <set>
#include <iterator>
#include "Laba1Func.h"
#include "Laba2Func.h"

#pragma warning(disable : 4996)

using namespace std;

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


bool CheckGGamal(long long p, long long g) {
	set<long long> my;
	for (int i = 0; i < p - 1; ++i) {
		pair<set<long long>::iterator, bool> ins = my.insert(vozvedenie(g, long long(i), p));
		if (!ins.second)
			return false;
	}
	return true;
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
		FILE *output = NULL;
		output = fopen(File.c_str(), "wb");
		fclose(output);
		//генерация P
		while (1) {
			p = rand()%5000 + 1000;
			if (p > 2000 && ferma(p) == true) {
				cout << "P=" << p << endl;
				break;
			}
		}
		//запись в фойл p
		WriteInFile(p, File);
		//генерируем Ca Da Cb Db
		while (1) {
			genNum = rand()%100000;
			if (genNum < p - 1 && evklidSimple(genNum, p - 1) == 1) {
				A[0] = genNum;
				break;
			}
		}
		A[1] = evklid(p - 1, A[0]);
		if (A[1] < 0)
			A[1] = (p - 1) + A[1];
		while (1) {
			genNumB = rand() % 100000;
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
		long long n = 21056;
		// шифруем
		ifstream in("1.jpg", ios::binary);
		int am = 0;
		char M;
		while(!in.eof()){
			am++;
			in.read((char*)&M, sizeof(char));
			m = unsigned char(M);
			x=vozvedenie(m,A[0],p);
			x=vozvedenie(x,B[0],p);
			//x=vozvedenie(x,A[1],p);
			WriteInFile(x, File);
			if (am < 10)
				cout << x << "  ";
			//запись в файл зашифрованного символа
		}
		cout << endl << am << endl;
		in.close();
	}
	else {
		//дешифруем
		string file = "1.jpg";
		FILE *output = NULL;
		output = fopen(file.c_str(), "wb");
		fclose(output);
		long long x = 1, P = 0, A = 0, B = 0, key = 0;
		int byte, temp;
		ifstream in(File.c_str(), ios::binary);
		//прочитали P
		in.read((char*)&byte, sizeof(char));
		for (int i = 0; i <= unsigned char(byte); ++i) {
			in.read((char*)&temp, sizeof(char));
			P += unsigned char(temp) * x;
			x *= 256;
		}
		//прочитали А
		x = 1;
		in.read((char*)&byte, sizeof(char));
		for (int i = 0; i <= unsigned char(byte); ++i) {
			in.read((char*)&temp, sizeof(char));
			A += unsigned char(temp) * x;
			x *= 256;
		}
		//прочитали B
		x = 1;
		in.read((char*)&byte, sizeof(char));
		for (int i = 0; i <= unsigned char(byte); ++i) {
			in.read((char*)&temp, sizeof(char));
			B += unsigned char(temp) * x;
			x *= 256;
		}
		//прочитали key
		ofstream out(file.c_str(), ios::binary);
		int am = 0;
		
		while (!in.eof()) {
			x = 1;
			am++;
			key = 0;
			in.read((char*)&byte, sizeof(char));
			for (int i = 0; i <= unsigned char(byte); ++i) {
				in.read((char*)&temp, sizeof(char));
				key += unsigned char(temp) * x;
				x *= 256;
			}
			if (am < 10)
				cout << key << "  ";
			//дешифруем key
			key = vozvedenie(key, A, P);
			key = vozvedenie(key, B, P);
			out.write((char*)&key, sizeof(char));
			//WriteInFile(key, file);
		}
		cout << endl << am << endl;
		out.close();
		in.close();
		cout << key;
	}
}

void AlGamal(string File, string Temp) {
	ShifrGamal("", Temp);
	DeShifrGamal("", Temp);
	ShifrGamal(File, Temp);
	DeShifrGamal(File, Temp);
}

void ShifrGamal(string File, string Temp) {
	//записываем ключ шифр или дешифр в файл
	if (File.length() == 0) {
		FILE *output = NULL;
		output = fopen(Temp.c_str(), "wb");
		fclose(output);
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
		WriteInFile(p, Temp);
		WriteInFile(g, Temp);
	}
	else {
		ifstream in(Temp.c_str());
		long long p = 0, g = 0, x, y = 0, temp, a, b, k = 0, X = 0;
		char M, byte;

		//read P
		x = 1;
		in.read((char*)&M, sizeof(char));
		for (int i = 0; i <= unsigned char(M); ++i) {
			in.read((char*)&byte, sizeof(char));
			p += unsigned char(byte) * x;
			x *= 256;
		}
		//read g
		x = 1;
		in.read((char*)&M, sizeof(char));
		for (int i = 0; i <= unsigned char(M); ++i) {
			in.read((char*)&byte, sizeof(char));
			g += unsigned char(byte) * x;
			x *= 256;
		}
		//read x
		x = 1;
		in.read((char*)&M, sizeof(char));
		for (int i = 0; i <= unsigned char(M); ++i) {
			in.read((char*)&byte, sizeof(char));
			X += unsigned char(byte) * x;
			x *= 256;
		}
		//read y
		x = 1;
		in.read((char*)&M, sizeof(char));
		for (int i = 0; i <= unsigned char(M); ++i) {
			in.read((char*)&byte, sizeof(char));
			y += unsigned char(byte) * x;
			x *= 256;
		}
		in.close();
		FILE *output = NULL;
		output = fopen(Temp.c_str(), "wb");
		fclose(output);
		k = rand() % (p - 2) + 1;
		in.open(File.c_str());
		//rewrite P and X
		WriteInFile(p, Temp.c_str());
		WriteInFile(X, Temp.c_str());
		while (!in.eof()) {
			in.read((char*)&M, sizeof(char));
			temp = unsigned char(M);
			a = vozvedenie(g, k, p);
			b = temp * vozvedenie(y, k, p) % p;
			WriteInFile(a, Temp.c_str());
			WriteInFile(b, Temp.c_str());
		}
	}
}

void DeShifrGamal(string File, string Temp) {
	if (File.length() == 0) {
		long long p = 0, g = 0, x;
		char M, byte;
		ifstream in(Temp.c_str());
		//read P
		x = 1;
		in.read((char*)&M, sizeof(char));
		for (int i = 0; i <= unsigned char(M); ++i) {
			in.read((char*)&byte, sizeof(char));
			p += unsigned char(byte) * x;
			x *= 256;
		}
		//read g
		x = 1;
		in.read((char*)&M, sizeof(char));
		for (int i = 0; i <= unsigned char(M); ++i) {
			in.read((char*)&byte, sizeof(char));
			g += unsigned char(byte) * x;
			x *= 256;
		}
		in.close();
		x = rand() % (p / 2 - 1) + p / 2;
		//write X
		WriteInFile(x, Temp.c_str());
		x = vozvedenie(g, x, p);
		//write Y
		WriteInFile(x, Temp.c_str());
	}
	else {
		long long a, b, p = 0, x = 0, s, m;
		char byte, t;
		FILE *output = NULL;
		output = fopen(File.c_str(), "wb");
		fclose(output);
		ifstream in(Temp.c_str());
		//read P
		s = 1;
		in.read((char*)&byte, sizeof(char));
		for (int i = 0; i <= unsigned char(byte); ++i) {
			in.read((char*)&t, sizeof(char));
			p += unsigned char(t) * s;
			s *= 256;
		}
		//read X
		s = 1;
		in.read((char*)&byte, sizeof(char));
		for (int i = 0; i <= unsigned char(byte); ++i) {
			in.read((char*)&t, sizeof(char));
			x += unsigned char(t) * s;
			s *= 256;
		}
		//reading and decoding a,b into messege
		while (!in.eof()) {
			a = 0; b = 0;
			s = 1;
			in.read((char*)&byte, sizeof(char));
			for (int i = 0; i <= unsigned char(byte); ++i) {
				in.read((char*)&t, sizeof(char));
				a += unsigned char(t) * s;
				s *= 256;
			}
			s = 1;
			in.read((char*)&byte, sizeof(char));
			for (int i = 0; i <= unsigned char(byte); ++i) {
				in.read((char*)&t, sizeof(char));
				b += unsigned char(t) * s;
				s *= 256;
			}
			m = b * vozvedenie(a, p - 1 - x, p) % p;
			WriteInFile(m, File.c_str());
		}
	}
}

void RSA(string File, string Temp) {
	ShifrRSA(File, Temp);
	DeShifrRSA(File, Temp);
}

void ShifrRSA(string File, string Temp) {
	//записываем ключ шифр или дешифр в файл
	FILE *output = NULL;
	output = fopen(Temp.c_str(), "wb");
	fclose(output);

	//ofstream fout(File.c_str());
	//определяем переменные для ключей 
	char t;
	long long N, Fi, D[2], p, Q, genNum;
	while (1) {
		p = rand() + 2;
		if (p > 1000 && ferma(p) == true) {
			break;
		}
	}
	while (1) {
		Q = rand() + 2;
		if (Q > 1000 && ferma(Q) == true) {
			break;
		}
	}
	N = p * Q;
	Fi = (p - 1)*(Q - 1);
	while (1) {
		genNum = 500 + rand();
		if (genNum < Fi && evklidSimple(genNum, Fi) == 1) {
			D[0] = genNum;
			break;
		}
	}
	D[1] = evklid(Fi, D[0]);
	//	cout<<"Cb="<<B[1]<<endl;
	if (D[1] < 0)
		D[1] = (Fi)+D[1];
	WriteInFile(N, Temp.c_str());
	WriteInFile(D[1], Temp.c_str());
	//fout.close();
	//открываем сообщение для шифрования
	ifstream in(File.c_str());
	//шифрование
	char ch;
	long long m, e;
	while (!in.eof()) {
		in.read((char*)&ch, sizeof(char));
		m = unsigned char(ch);
		e = vozvedenie(m, D[0], N);
		WriteInFile(e, Temp);
	}
	in.close();
}

void DeShifrRSA(string File, string Temp) {
	FILE *output = NULL;
	output = fopen(File.c_str(), "wb");
	fclose(output);
	//открываем файл для чтения
	ifstream in(Temp.c_str());
	//добавляем переменные N
	char M, byte;
	long long N = 0, D = 0, m, x;
	//считываем длину N
	x = 1;
	in.read((char*)&M, sizeof(char));
	for (int i = 0; i <= unsigned char(M); ++i) {
		in.read((char*)&byte, sizeof(char));
		N += unsigned char(byte) * x;
		x *= 256;
	}
	
	//считываем длину D-1
	
	x = 1;
	in.read((char*)&M, sizeof(char));
	for (int i = 0; i <= unsigned char(M); ++i) {
		in.read((char*)&byte, sizeof(char));
		D += unsigned char(byte) * x;
		x *= 256;
	}

	//дешифрование
	long long e;
	while (!in.eof()) {
		x = 1; e = 0;
		in.read((char*)&M, sizeof(char));
		for (int i = 0; i <= unsigned char(M); ++i) {
			in.read((char*)&byte, sizeof(char));
			e += unsigned char(byte) * x;
			x *= 256;
		}
		m = vozvedenie(e, D, N);
		WriteInFile(unsigned char(m), File.c_str());
	}
	in.close();
}

void Vernam(string File, string Temp[2]) {
	ShifrVernam(File, Temp);
	DeShifrVernam(File, Temp);
}

void ShifrVernam(string File, string Temp[2]) {
	FILE *output = NULL;
	output = fopen(Temp[0].c_str(), "wb");
	fclose(output);
	FILE *output1 = NULL;
	output1 = fopen(Temp[1].c_str(), "wb");
	fclose(output1);

	//шифрование
	char byte = 0, m, k;
	long long e = 0;
	ifstream in(File.c_str());
	ofstream out0(Temp[0].c_str());
	ofstream out1(Temp[1].c_str());
	while (!in.eof()) {
		in.read((char*)&byte, sizeof(char));
		m = unsigned char(byte);
		while (1) {
			k = rand() % 256;
			if (k != byte)
				break;
		}
		out1.write(&k, sizeof(k));
		m = m ^ k;
		out0.write(&(m), sizeof(m));
	}
	out0.close();
	out1.close();
	in.close();
}

void DeShifrVernam(string File, string Temp[2]) {
	//открываем файл для чтения
	FILE *output = NULL;
	output = fopen(File.c_str(), "wb");
	fclose(output);

	ifstream in0(Temp[0].c_str());
	ifstream in1(Temp[1].c_str());
	ofstream out(File.c_str());
	char byte = 0, k = 0, m = 0;

	while (!in1.eof() && !in0.eof()) {
		in0.read((char*)&byte, sizeof(char));
		k = unsigned char(byte);
		in1.read((char*)&byte, sizeof(char));
		m = unsigned char(byte);
		m ^= k;
		out.write(&m, sizeof(m));
	}
	out.close();
	in0.clear();
	in1.close();
}




int main() {
	//cout << int(vozvedenie(666, 777, 2014));
	srand(time(0));
	//ShifrShamir("C:\\Users\\Evgeny\\source\\repos\\DI\\Labb2\\Labb2\\123.txt", 1);
	//ShifrShamir("C:\\Users\\Evgeny\\source\\repos\\DI\\Labb2\\Labb2\\123.txt", 0);
	//AlGamal("C:\\Users\\Evgeny\\source\\repos\\DI\\Labb2\\Labb2\\123.txt", "C:\\Users\\Evgeny\\source\\repos\\DI\\Labb2\\Labb2\\temp.txt");
	//RSA("C:\\Users\\Evgeny\\source\\repos\\DI\\Labb2\\Labb2\\123.txt", "C:\\Users\\Evgeny\\source\\repos\\DI\\Labb2\\Labb2\\temp.txt");
	string Temp[2];
	Temp[0] = "C:\\Users\\Evgeny\\source\\repos\\DI\\Labb2\\Labb2\\temp0.txt";
	Temp[1] = "C:\\Users\\Evgeny\\source\\repos\\DI\\Labb2\\Labb2\\temp1.txt";
	Vernam("C:\\Users\\Evgeny\\source\\repos\\DI\\Labb2\\Labb2\\123.txt", Temp);
	//system("PAUSE");
}