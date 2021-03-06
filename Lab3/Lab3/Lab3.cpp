// Lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <string>

#pragma warning(disable : 4996)

using namespace std;

void signRSA(string File, string Temp) {
	unsigned char digest[SHA256_DIGEST_LENGTH];
	string str;
	SHA256_CTX ctx;
	SHA256_Init(&ctx);
	FILE *output = NULL;
	output = fopen(Temp.c_str(), "wb");
	fclose(output);
	ifstream in(File.c_str());
	unsigned char m;
	char t;
	long long N, Fi, D[2], p, Q, genNum, e, count = 0;
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
	ofstream out(Temp.c_str(), ios::binary | ios::app);
	out << N << " " << D[1] << " ";
	while (!in.eof()) {
		in.read((char*)&t, sizeof(char));
		str += (unsigned char)t;
	}
	//out.close();
	in.close();
	SHA256_Update(&ctx, str.c_str(), str.length());
	SHA256_Final(digest, &ctx);
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		e = vozvedenie((long long)digest[i], D[0], N);
		out << e << " ";
	}
	out.close();
}

void unsignRSA(string File, string Temp) {
	//открываем файл для чтения
	FILE *output = NULL;
	output = fopen(Temp.c_str(), "wb");
	fclose(output);
	ifstream in(File.c_str());
	//добавляем переменные N
	char M, byte;
	long long N = 0, D = 0, m, x;
	//считываем  N
	in >> N;
	//считываем  D-1
	in >> D;
	long long e;
	ofstream out(Temp.c_str(), ios::binary | ios::app);
	while (!in.eof()) {
		x = 1; e = 0;
		//in.read((char*)&e, sizeof(long long));
		in >> e;
		m = vozvedenie(e, D, N);
		out << m << " ";
	}
	out.close();
	in.close();
}


void WriteInFile(long long X, string File) {
	long long n;
	int d;
	char l;
	//открываем файл
	ofstream out(File.c_str(), ios::binary | ios::app);
	//определяем длину x
	d = 1; n = X;
	while (n > 255) {
		n /= 256;
		d++;
	}
	//записываем длину x в файл
	out.write((char*)&d, sizeof(char));
	//fwrite(&d, sizeof(char), 1, output);
	n = X;
	while (d > 0) {
		l = char(n & 255);
		n /= 256;
		d--;
		out.write((char*)&l, sizeof(l));
		//fwrite(&l, sizeof(char), 1, output);
	}
	//закрываем файл
	out.close();
}

bool checking(string File, string Temp) {
	long long m;
	char t, byte, M;
	long long x;
	unsigned char digest[SHA256_DIGEST_LENGTH];
	string str;
	SHA256_CTX ctx;
	SHA256_Init(&ctx);
	ifstream in(File.c_str());
	ifstream out(Temp.c_str());
	while (!in.eof()) {
		in.read((char*)&t, sizeof(char));
		str += (unsigned char)t;
	}
	SHA256_Update(&ctx, str.c_str(), str.length());
	SHA256_Final(digest, &ctx);
	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
		//x = 1;
		out >> m;
		//out.read((char*)&t, sizeof(char));
		/*out.read((char*)&M, sizeof(char));
		for (int i = 0; i < unsigned char(M); ++i) {
			out.read((char*)&byte, sizeof(char));
			t += unsigned char(byte) * x;
			x *= 256;
		}*/
		//cout << m << " " << (long long) digest[i] << endl;
		if (m != (long long)digest[i]) {
			//cout << endl << "ERROR!" << endl;
			in.close();
			out.close();
			return false;
		}
	}
	in.close();
	out.close();
	return true;
}

void signGamal(string File, string Temp) {
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
		ofstream out(Temp.c_str(), ios::binary | ios::app);
		out << p << " ";
		out << g << " ";
		out.close();
	}
	else {
		ifstream in(Temp.c_str());
		long long p = 0, g = 0, x, y = 0, temp, a, b, k = 0, X = 0;
		char M, byte;
		//read P, G, X, Y
		in >> p;
		in >> g;
		in >> X;
		in >> y;

		in.close();
		FILE *output = NULL;
		output = fopen(Temp.c_str(), "wb");
		fclose(output);
		ofstream out(Temp.c_str(), ios::binary | ios::app);
		k = rand() % (p - 2) + 1;
		in.open(File.c_str());
		//rewrite P and X
		out << p << " " << X << " ";
		//reading and signing doc
		unsigned char digest[SHA256_DIGEST_LENGTH];
		string str;
		SHA256_CTX ctx;
		SHA256_Init(&ctx);
		while (!in.eof()) {
			in.read((char*)&M, sizeof(char));
			str += M;
		}
		// making hash out of our file
		SHA256_Update(&ctx, str.c_str(), str.length());
		SHA256_Final(digest, &ctx);
		long long amount = SHA256_DIGEST_LENGTH;
		//cout << "p = " << p << " x = " << X << endl << str << endl << "amount = " << amount << endl;
		//out << amount << " ";
		//out.write((char*)&amount, sizeof(long long));
		for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
			a = vozvedenie(g, k, p);
			b = (long long)digest[i] * vozvedenie(y, k, p) % p;
			out << a << " " << b << " ";
			//printf("%lld %lld %lld\n", (long long)digest[i], a, b);
		}
		cout << endl;
		out.close();
	}
}

void unsignGamal(string File, string Temp) {
	if (File.length() == 0) {
		long long p = 0, g = 0, x;
		char M, byte;
		ifstream in(Temp.c_str());
		//read P, G
		x = 1;
		in >> p;
		in >> g;
		in.close();
		x = rand() % (p / 2 - 1) + p / 2;
		//write X
		ofstream out(Temp.c_str(), ios::binary | ios::app);
		out << x << " ";
		x = vozvedenie(g, x, p);
		//write Y
		out << x << " ";
		out.close();
	}
	else {
		long long a, b, p = 0, x = 0, s, m;
		char byte, t;
		FILE *output = NULL;
		output = fopen(File.c_str(), "wb");
		fclose(output);
		ifstream in(Temp.c_str());
		//read P, X
		in >> p;
		in >> x;
		//reading and decoding a,b into messege
		ofstream out(File.c_str(), ios::binary | ios::app);
		cout << endl;
		long long amount;
		in >> amount;
		//printf("\n p = %lld x = %lld amount = %lld\n", p, x, amount);
		while (amount-- > 0 && !in.eof()) {
			in >> b >> a;
			//cout << a << " " << b << endl;
			m = b * vozvedenie(a, p - 1 - x, p) % p;
			//cout << m << "  ";
			//printf("%lld %lld %lld\n", m, a, b);
			out << m << " ";
		}
		out.close();
	}
}

void gost(string File, string Temp) {
	long long p, q = 4, a;
	char t;
	unsigned char digest[SHA256_DIGEST_LENGTH];
	string str;
	SHA256_CTX ctx;
	SHA256_Init(&ctx);
	FILE *output = NULL;
	output = fopen(Temp.c_str(), "wb");
	fclose(output);
	//generating q, p, a
	while (1) {
		q = rand() % ((1 << 15) - 1) + (1 << 15);
		if (ferma(q))
			break;
	}
	while(1)
		if (ferma(q)) {
			p = (rand() % (1 << 14) + (1 << 15)) * q + 1;
			if (ferma(p) == true) {
				break;
			}
		}
	
	while (1) {
		a = rand() + 2;
		if (vozvedenie(a, q, p) == 1) {
			break;
		}
	}
	//generating x и y
	long long x, y, k, r, s;
	x = rand() % (q - 2) + 1;
	y = vozvedenie(a, x, p);
	//reading file and creating hash
	ifstream in(File.c_str());
	while (!in.eof()) {
		in.read((char*)&t, sizeof(char));
		str += (unsigned char)t;
	}
	//out.close();
	in.close();
	SHA256_Update(&ctx, str.c_str(), str.length());
	SHA256_Final(digest, &ctx);
	bool b = 0;
	while (!b) {
		k = rand() % (q - 2) + 1;
		b = 1;
		for (int i = 0; i < SHA256_DIGEST_LENGTH && b; i++) {
			r = vozvedenie(a, k, p) % q;
			if (r != 0) {
				s = (k*digest[i] + x * r) % q;
				if (s == 0) {
					b = 0;
				}
			}
			else
				b = 0;
		}
	}
	ofstream out(Temp.c_str(), ios::binary | ios::trunc);
	out << p << " " << q << " " << a << " " << y << " ";
	for (int i = 0; i < SHA256_DIGEST_LENGTH && b; i++) {
		r = vozvedenie(a, k, p) % q;
		s = (k*(long long)digest[i] + x * r) % q;
		out << r << " " << s << " ";
		//cout << r << "  " << s << endl;
	}
}

void gostCheck(string File, string Temp) {
	long long p, a, q, r, s, u1, u2, v, H, y;
	unsigned char digest[SHA256_DIGEST_LENGTH];
	char t;
	string str;
	SHA256_CTX ctx;
	SHA256_Init(&ctx);
	ifstream in(Temp.c_str());
	in >> p;
	in >> q;
	in >> a;
	in >> y;
	//in.close();
	ifstream out(File.c_str());
	while (!out.eof()) {
		out.read((char*)&t, sizeof(char));
		str += (unsigned char)t;
	}
	//out.close();
	//in.close();
	//in.open(Temp.c_str());
	SHA256_Update(&ctx, str.c_str(), str.length());
	SHA256_Final(digest, &ctx);
	bool F = 0;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
		in >> r;
		in >> s;
		//cout << r << "  " << s << endl;
		H = evklid(q, (long long)digest[i]);
		if (H < 0)
			H = q + H;
		u1 = (s*H) % q;
		u2 = (q-r)*H%q;
		v = ((vozvedenie(a, u1, p)*vozvedenie(y, u2, p)) % p) % q;
		if (r != v) {
			F = 1;
			cout << "something gone wrong in Gost" << endl;
		}
		//cout << r << "   " << v;
	}
	if (!F)
		cout << "Gost is working!!" << endl;
}

int main()
{
	string path = "C:\\Users\\Evgeny\\source\\repos\\DI\\Lab3\\Lab3\\";
	signRSA(path + "123.txt", path + "temp.txt");
	unsignRSA(path + "temp.txt", path + "321.txt");
	if (checking(path + "123.txt", path + "321.txt"))
		cout << endl << "RSA is working";
	else
		cout << endl << "Something gone wrong in RSA";
	
	signGamal("", path + "temp.txt");
	unsignGamal("", path + "temp.txt");
	signGamal(path + "123.txt", path + "temp.txt");
	unsignGamal(path + "321.txt", path + "temp.txt");
	if (checking(path + "123.txt", path + "321.txt"))
		cout << endl << "Gamal is working" << endl;
	else
		cout << endl << "Something gone wrong in Gamal" << endl;

	gost(path + "123.txt", path + "temp.txt");
	gostCheck(path + "123.txt", path + "temp.txt");
	//printf("SHA256 digest: %s\n", mdString);
	
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
