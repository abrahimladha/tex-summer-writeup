#include <string>
#include <gmpxx.h>
#include <gmp.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "basic.h"
using namespace std;
int main(void){
    int n = 10; //how many parties?
    ifstream in("inputn.txt"); //input file
    ofstream out("output.txt"); //output file
    vector<vector<string>> input(n);
    string line;
    int i = 0;
    while(getline(in,line)){
        if(line == "----"){ //our delimiter for sets
            i++;
        }
        else{
            input[i].push_back(line);
        }
    }
    vector<string> output;
    for(int k = 0; k < input.size() - 1; k++){
        for(int i =  0; i < input[0].size(); i++){
            for(int j = 0; j < input[1].size(); j++){
                vector<unsigned long> temp1 = string_to_vector(input[0][i]);
                vector<unsigned long> temp2 = string_to_vector(input[1][j]);
                if(basic_scheme(temp1,temp2) == 0){
                    output.push_back(input[1][j]);
                }
            }
        }
        if(output.size() != 0){
            input.push_back(output);
        }
        else{
            input.push_back(input[0]);
        }
        input.erase(input.begin(),input.begin()+1);
        output.erase(output.begin(),output.end());
    }
    for(int k = 0; k < input[1].size(); k++){
        out << input[1][k] << endl; //second set
    }
}
