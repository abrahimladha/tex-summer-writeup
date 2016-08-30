#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <math.h>
#include <string>
#include <vector>
#include <map>
using namespace std;
//pick q and g, G is always Zq
vector<mpz_class> keygen(mpz_class g, mpz_class q){

    unsigned long seed = (unsigned long)time(NULL);
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate,seed);
    mpz_class x;
    mpz_urandomm(x.get_mpz_t(),rstate,q.get_mpz_t());
    //randomly pick x from G
    mpz_class h;
    mpz_powm(h.get_mpz_t(),g.get_mpz_t(),x.get_mpz_t(),q.get_mpz_t());
    //h = g^x
    vector<mpz_class> keys(2);
    keys[0] = h;
    keys[1] = x;
    return keys;
    //keys[0] is public, keep keys[1] secret
    //publish h as pubkey
    //x is private key and is kept secret
}
vector<mpz_class> encryption(mpz_class m, mpz_class h, mpz_class q, mpz_class g){
    unsigned long seed = (unsigned long)time(NULL);
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate,seed);
    mpz_class y;
    mpz_urandomm(y.get_mpz_t(),rstate,q.get_mpz_t());
    //randomly pick y from G
    mpz_class c1;
    mpz_powm(c1.get_mpz_t(),g.get_mpz_t(),y.get_mpz_t(),q.get_mpz_t());
    //c1 = g^y

    mpz_class s;
    mpz_powm(s.get_mpz_t(),h.get_mpz_t(),y.get_mpz_t(),q.get_mpz_t());
    //s = h^y
    mpz_class c2;
    c2 = m*s;
    //c2 = m * s

    //(c1,c2) is sent as a tuple
    vector<mpz_class> c(2);
    c[0] = c1;
    c[1] = c2;

    return c;
}
mpz_class decryption(vector<mpz_class> c, mpz_class x, mpz_class q){
    mpz_class c1 = c[0];
    mpz_class c2 = c[1];

    mpz_class s;
    mpz_powm(s.get_mpz_t(),c1.get_mpz_t(),x.get_mpz_t(),q.get_mpz_t());
    //s = c1^x

    mpz_class inv_s;
    inv_s = q - s;
    //get inverse of s from s?
    mpz_class m;
    m = c2 * inv_s;

    return m;
    //m = c2^s^(-1) thats modular multiplicative inverse of s
    //s^-1 = (c1^-1)^x
    //return m
}
