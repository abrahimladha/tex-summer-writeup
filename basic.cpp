#include <string>
#include <gmpxx.h>
#include <gmp.h>
#include <math.h>
#include <iostream>
#include <vector>
using namespace std;
/*
 * returns a vector of all bitstrings up to a
 * certain length
*/
vector<string> bitstring_generator(unsigned long n){
    vector<string> bitstrings(pow(2,n));
    bitstrings.push_back("0");
    bitstrings.push_back("1");
    for(int j = 1; j < n; j++){
        int x = bitstrings.size();
        for(int i = 0; i < x; i++){
            string temp1 = bitstrings[i] + "0";
            string temp2 = bitstrings[i] + "1";
            if((find(bitstrings.begin(), bitstrings.end(),temp1)) ==
            bitstrings.end()){
                bitstrings.push_back(bitstrings[i] + "0");
            }
            if((find(bitstrings.begin(), bitstrings.end(),temp2)) ==
            bitstrings.end()){
                bitstrings.push_back(bitstrings[i] + "1");
            }
        }
    }
    return bitstrings;
}
/*
 * given some bitstring, it returns its
 * vector equivalent
 */
vector<unsigned long> string_to_vector(string s){
     vector<unsigned long> Y(s.length());
    for(int i = 0; i < Y.size(); i++){
        Y[i] = s[i] - '0';
    }
    return Y;
}
/*
 * filters a vector of bitstrings to only use those
 * of a certain length
 */
vector<string> bitstrings_of_length(vector<string> strings, int n){
     vector<string> bitstrings;
    for(int i = 0; i < strings.size(); i++){
        if(strings[i].size() == n)
            bitstrings.push_back(strings[i]);
    }
    return bitstrings;
}
/*
 * computes sum of a vector of ulongs
 */
unsigned long vector_sum(vector<unsigned long> v){
    unsigned long sum;
    for(int i = 0; i < v.size(); i++)
        sum += v[i];
    return sum;
}
/*
 * computes sum of a vector of doubles
 */
double vector_sumd(vector<double> v){
    double sum;
    for(int i = 0; i < v.size(); i++)
        sum += v[i];
    return sum;
}
/*
 * given two vectors, returns their hamming distance
 */
unsigned long basic_scheme(vector<unsigned long> X, vector<unsigned long> Y){
    //tiny error check
    if(X.size() != Y.size()){
        cout << "vector sizes do not match" << endl;
        cout << X.size()  << "\t" << Y.size() << endl;
        return 0;
    }
    unsigned long domain = X.size() + 1;
    vector<unsigned long> r(X.size());
    unsigned long seed = (unsigned long)time(NULL);
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate,seed);
    mpz_class temp, n;
    n = X.size() + 1; //could be bigger
    //make r a vector of uniformly randoms
    for(int i = 0; i < X.size(); i++){
        mpz_urandomm(temp.get_mpz_t(),rstate,n.get_mpz_t());
        r[i] = temp.get_ui();
    }
    //compute their sum
    unsigned long R = vector_sum(r);
    vector<unsigned long> t(X.size());
    vector<unsigned long> tuple(2);
    for(int i = 0; i < X.size(); i++){
        tuple[0] = (r[i] + X[i]) % domain;
        tuple[1] = (r[i] + (1 - X[i])) % domain;
        t[i] = tuple[Y[i]]; //choosing
    }
    //comute their sum
    unsigned long T = vector_sum(t);
    //subtract off the random values
    int total = T - R;
    //some modular issues
    while(total < 0){
        total += (X.size() + 1);
    }
    return total;
}
