#include <gmp.h>
#include <gmpxx.h>
#include <math.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include "elgamal.h"
#include "elgamal_v.h"
//somehow include elgamal as a commitment library
using namespace std;
mpz_class vector_sum(vector<mpz_class> v){
    mpz_class sum;
    for(int i = 0; i < v.size(); i++){
        sum += v[i];
    }
    return sum;
}
mpz_class uniformly_random(mpz_class q){
    unsigned long seed = (unsigned long)time(NULL);
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate,seed);
    mpz_class g;
    mpz_urandomm(g.get_mpz_t(),rstate,q.get_mpz_t());
    return g;
}
mpz_class fully_secure(vector<unsigned long> X, vector<unsigned long> Y){
    if(X.size() != Y.size()){
        cout << "vector sizes do not match" << endl;
        cout << X.size() << "\t" << Y.size() << endl;
        return 0;
    }

    map<string,mpz_class> buffer;


    /*
     * I used random.org to pick a random mersenne prime, which is in base 10 format, cited from http://bigprimes.net/pages/archive/mersenne/M21.txt
     */
    ifstream input_q("q.txt");
    string q_str;
    getline(input_q,q_str);
    mpz_class q(q_str,10);
    /*
     *Random mersenne chosen by random.org
     *http://bigprimes.net/pages/archive/mersenne/M21.txt
     */


    unsigned long seed = (unsigned long)time(NULL);
    gmp_randstate_t rstate;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate,seed);
    mpz_class g;
    mpz_urandomm(g.get_mpz_t(),rstate,q.get_mpz_t());

    vector<vector<mpz_class>> com_X(X.size());
    vector<vector<mpz_class>> com_Y(Y.size(),vector<mpz_class>(2,0));

    //get an elgamal tuple
    vector<mpz_class> keys = keygen(g,q);
    mpz_class h,x;
    h = keys[0];
    x = keys[1]; //secret
    cout << "asd" << endl;
    mpz_class temp_random;
    mpz_class temp;
    for(int i = 0; i < X.size(); i++){
        //mpz_class temp;
        //temp = Y[i];
        mpz_set_ui(temp.get_mpz_t(),Y[i]);
        com_Y[i] = encryption(temp,h,q,g);
        //buffer["com_Y0" + to_string(i)] = com_Y[0][i];
        //buffer["com_Y1" + to_string(i)] = com_Y[1][i];
        //uncommenting these really likes to make GNU-MP run out of virtual memory. no idea why.

        //generate a commitment for each xi, yi and add it to com_X and com_Y

        cout << "a";
        //mpz_urandomm(temp_random.get_mpz_t(),rstate,q.get_mpz_t());
        temp_random = uniformly_random(q);
        cout << "b";
        mpz_class ytemp1,ytemp2;
        cout << "c";
        ytemp1 = Y[i];
        cout << "d" << i;
        ytemp2 = 1 - Y[i];
        //cout << elgamal_v(q,h,g,temp_random,ytemp1,ytemp2) << endl;
        //call elgamals verifier function on yi
    }
    vector<mpz_class> r(X.size());
    for(int i = 0; i < X.size(); i++){
        mpz_urandomm(r[i].get_mpz_t(),rstate,q.get_mpz_t());
    }
    cout << "peasche!" << endl;
    mpz_class R = vector_sum(r);

    mpz_class alpha,beta,tau,rho;
    mpz_urandomm(alpha.get_mpz_t(),rstate,q.get_mpz_t());
    mpz_urandomm(beta.get_mpz_t(),rstate,q.get_mpz_t());
    mpz_urandomm(tau.get_mpz_t(),rstate,q.get_mpz_t());
    mpz_urandomm(rho.get_mpz_t(),rstate,q.get_mpz_t());

    cout << "ayylmao" << endl;
    vector<vector<mpz_class>> ab(X.size(),vector<mpz_class>(2,0));
    vector<vector<mpz_class>> A(ab.size(),vector<mpz_class>(2,0));
    vector<vector<mpz_class>> B(ab.size(),vector<mpz_class>(2,0));
    for(int i = 0; i < ab.size(); i++){
        //mpz_urandomm(r[i].get_mpz_t(),rstate,q.get_mpz_t());
        ab[i][0] = (r[i] + X[i]) % q;
        ab[i][1] = (r[i] + (1 - X[i])) % q;
        A[i] = encryption(ab[i][0],alpha,q,g);
        B[i] = encryption(ab[i][1],beta,q,g);
        //buffer["A0" + to_string(i)] = A[0][i];
        //buffer["A1" + to_string(i)] = A[1][i];
        //buffer["B0" + to_string(i)] = B[0][i];
        //buffer["B1" + to_string(i)] = B[1][i];
    }
    for(int i = 0; i < ab.size(); i++){
        mpz_class temp_random;
        mpz_urandomm(temp_random.get_mpz_t(),rstate,q.get_mpz_t());
        cout << "ab" << i << endl;
        cout << elgamal_v(q,h,g,temp_random,ab[0][i],ab[1][i]) << endl;
        //call elgamal verifier method showing |bi = ai| = 1
    }
    cout << "widdle farther" << endl;
    vector<mpz_class> t(ab.size());
    vector<vector<mpz_class>> C(ab.size());
    for(int i = 0; i < ab.size(); i++){
        t[i] = ab[i][Y[i]];
        C[i] = encryption(t[i],tau,q,g);
        //buffer["C0"+ to_string(i)] = C[0][i];
        //buffer["C1"+ to_string(i)] = C[1][i];
    }
    mpz_class T = vector_sum(t);

    //option 1
    vector<mpz_class> Ct(2); //our elgamal tuple
        Ct[0] = 1;
        Ct[1] = 1;
    for(int i = 0; i < ab.size(); i++){
        Ct[0] *= C[0][i];
        Ct[1] *= C[1][i]; //since multiplying integers is the same as and-ing bitstrings
    }
    cout << "woah were far" << endl;
    //buffer T
    buffer["T"] = T;
    //call proof again

    vector<mpz_class> Cl(2);
    Cl[0] = 1;
    Cl[1] = 1;
    for(int i = 0; i < ab.size(); i++){
        Cl[0] *= buffer["C0" + to_string(i)];
        Cl[1] *= buffer["C1" + to_string(i)];
    }
    bool a = Ct[0] == Cl[0];
    bool b = Ct[1] == Cl[1];
    if(a && b) cout << "yes" << endl;
    else cout << "no" << endl;
    //compute Ct again but with C from buffer and verify
    return T - R;
}

