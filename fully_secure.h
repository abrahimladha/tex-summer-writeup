#ifndef FULLY_SECURE_H
#define FULLY_SECURE_H
#include <string>
#include <gmpxx.h>
#include <gmp.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
mpz_class vector_sum(vector<mpz_class> v);
mpz_class fully_secure(vector<unsigned long> X, vector<unsigned long> Y);
#endif
