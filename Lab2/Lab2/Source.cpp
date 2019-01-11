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


using namespace std;

long long vozvedenie(long long a, long long b, long long p)
{
	unsigned long result = 1;
	while (b)
	{
		if (b & 1 == 0)
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


int main() {
	cout << int(vozvedenie(255, 1000009, 1000008));
	/*
	ShifrShamir("123.txt", 1);
	ShifrShamir("123.txt", 0);
	*/
	//system("PAUSE");
}