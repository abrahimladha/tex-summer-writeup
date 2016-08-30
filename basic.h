#ifndef BASIC_H
#define BASIC_H
#include <string>
#include <gmpxx.h>
#include <gmp.h>
#include <math.h>
#include <iostream>
#include <vector>
using namespace std;
vector<string> bitstring_generator(unsigned long n);
vector<unsigned long> string_to_vector(string s);
vector<string> bitstrings_of_length(vector<string> strings, int n);
unsigned long vector_sum(vector<unsigned long> v);
double vector_sumd(vector<double> v);
unsigned long basic_scheme(vector<unsigned long> X, vector<unsigned long> Y);
#endif
