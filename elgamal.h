#ifndef ELGAMAL_H
#define ELGAMAL_H
#include <string>
#include <gmpxx.h>
#include <gmp.h>
#include <math.h>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
using namespace std;
vector<mpz_class> keygen(mpz_class g, mpz_class q);
vector<mpz_class> encryption(mpz_class m, mpz_class h, mpz_class q, mpz_class g);
mpz_class decryption(vector<mpz_class> c, mpz_class x, mpz_class q);
#endif
