#include <string>
#include <gmpxx.h>
#include <gmp.h>
#include <math.h>
#include <iostream>
#include <map>
using namespace std;
/*
 * zero knowledge proof for elgamal
 */
bool elgamal_ff(mpz_class q, mpz_class h, mpz_class g, mpz_class b1,
        mpz_class b2, mpz_class x1, mpz_class x2){
    map <string, mpz_class> buffer;
    mpz_class l, rand;
    mpz_ui_pow_ui(l.get_mpz_t(),2,199);
    unsigned long seed = (unsigned long)time(NULL);
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate,seed);
    mpz_class u1, u2, div1, div2;

    mpz_powm(div1.get_mpz_t(),g.get_mpz_t(),x1.get_mpz_t(),q.get_mpz_t());
    u1 = b2 / div1;
    //u1 = b2/(g^x1)

    mpz_powm(div2.get_mpz_t(),g.get_mpz_t(),x2.get_mpz_t(),q.get_mpz_t());
    u2 = b2 / div2;
    //u1 = b2/(g^x1)

    mpz_class v1, v2, c2, t1, t2;
    mpz_urandomb(v1.get_mpz_t(),rstate,310);
    mpz_urandomb(v2.get_mpz_t(),rstate,310);
    mpz_urandomb(c2.get_mpz_t(),rstate,310);
    v1 %= q;
    v2 %= q;
    c2 %= q;
    //random v1, v2, c2, in Zq

    mpz_powm(t1.get_mpz_t(),h.get_mpz_t(),v1.get_mpz_t(),q.get_mpz_t());
    //t1 = h^v1

    mpz_class temp1, temp2;
    mpz_powm(temp1.get_mpz_t(),u2.get_mpz_t(),c2.get_mpz_t(),q.get_mpz_t());
    mpz_powm(temp2.get_mpz_t(),h.get_mpz_t(),v2.get_mpz_t(),q.get_mpz_t());
    t2 = temp1 * temp2;
    //t2 = u2^c2 * h^v2

    mpz_class c;
    mpz_urandomb(c.get_mpz_t(),rstate,310);
    c %= q;
    mpz_class c1, r1, r2;
    c1 = c - c2;
    r1 = v1 - c1;
    r2 = v2;

    mpz_class temp3,temp4,temp5, temp6;
    mpz_powm(temp5.get_mpz_t(),u2.get_mpz_t(),c2.get_mpz_t(),q.get_mpz_t());
    mpz_powm(temp6.get_mpz_t(),h.get_mpz_t(),v2.get_mpz_t(),q.get_mpz_t());
    mpz_powm(temp3.get_mpz_t(),u1.get_mpz_t(),c1.get_mpz_t(),q.get_mpz_t());
    mpz_powm(temp4.get_mpz_t(),h.get_mpz_t(),r2.get_mpz_t(),q.get_mpz_t());

    return ((c == c1 + c2) && (t2 == temp5 * temp6) && (t1 == temp3 * temp4));
}
