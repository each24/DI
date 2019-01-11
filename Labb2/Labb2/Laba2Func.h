#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <list>
#include <string.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
//#include <bits/stdc++.h>

#include <cmath>

void Shamir();
void WriteInFile(long long X, std::string A);
void ShifrShamir(std::string File, bool Do);
void DeShifrShamir();
void WriteMessageDeShifr(long long m);
void ShifrGamal(std::string File, std::string Temp);
void AlGamal(std::string File,std::string Temp);
void DeShifrGamal(std::string File, std::string Temp);
void ShifrRSA(std::string File, std::string Temp);
void RSA(std::string File, std::string Temp);
void DeShifrRSA(std::string File, std::string Temp);
void WriteInFileOnlyVernam(int X);
void Vernam(std::string File, std::string Temp[2]);
void ShifrVernam(std::string File, std::string Temp[2]);
void DeShifrVernam(std::string File, std::string Temp[2]);
//void WriteInFileOnlyVernamInt(int X);
//void WriteInFileOnlyVernamKey(int X);
