#include <string>
#include <gmpxx.h>
#include <gmp.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
using namespace std;
//predetermine N as some large ass prime of mpz_class
vector<mpz_class> keygen(){
    vector<mpz_class> c;
    //should return a fully secure e and d as a tuple in c
    //multiplicative inverse of each other in  Zn
}
void OT(/*y a bit*/mpz_class m0,mpz_class m1, unsigned long y){
    //gen buffer

    mpz_class N; //temp
    unsigned long seed = (unsigned long)time(NULL);
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate,seed);

    mpz_class x0, x1;
    mpz_urandomm(x0.get_mpz_t(),rstate,N.get_mpz_t());
    mpz_urandomm(x1.get_mpz_t(),rstate,N.get_mpz_t());
    mpz_class e, d;
    //e, x0, x1 to buffer

    mpz_class k;
    mpz_urandomm(k.get_mpz_t(),rstate,N.get_mpz_t());
    unsigned long b = y;
    mpz_class v;
    mpz_class temp;
    mpz_powm(temp.get_mpz_t(),k.get_mpz_t(),e.get_mpz_t(),N.get_mpz_t());
    v = (((b == 0)? x0 : x1) + temp )%N;
    //push v, also buffer xinputs
    mpz_class k0, k1,temp2,temp3;
    mpz_powm(temp2.get_mpz_t(),x0.get_mpz_t(),d.get_mpz_t(),N.get_mpz_t());
    mpz_powm(temp3.get_mpz_t(),x1.get_mpz_t(),d.get_mpz_t(),N.get_mpz_t());
    k0 = (v - temp2)%N;
    k1 = (v - temp3)%N;
    mpz_class n0, n1;
    n0 = k0 + m0;
    n1 = k1 + m1;
    //buffer n0,n1;

    cout << ((b == 0)? n0 : n1 ) - k;
    //n0,n1 from buffer
}

