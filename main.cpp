#include <string>
#include <gmpxx.h>
#include <gmp.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <omp.h>
#include <fstream>
#include "basic.h"
using namespace std;
/*int main(void){

    ifstream in1("input1.txt");
    ifstream in2("input2.txt");
    ofstream out1("output1.txt");

    vector<string> input1;
    vector<string> input2;

    string test;
    while(getline(in1,test)){
        input1.push_back(test);
    }
    string test2;
    while(getline(in2,test2)){
        input2.push_back(test2);
    }
    vector<string> output1;
    for(int i = 0; i < input1.size(); i++){
        for(int j = 0; j < input2.size();j++){
            vector<unsigned long> temp1 = string_to_vector(input1[i]);
            vector<unsigned long> temp2 = string_to_vector(input2[j]);

            if(basic_scheme(string_to_vector(input1[i]),string_to_vector(input2[j])) == 0){
                output1.push_back(input2[j]);
            }

        }
    }
    for(int k = 0; k < output1.size();k++){
        out1 << output1[k] << endl;
    }
}
*/
int main(void){
    int n = 10;
    ifstream in("inputn.txt");
    ofstream out("output.txt");
    vector<vector<string>> input(n);
    string line;
    int i = 0;
    while(getline(in,line)){
        if(line == "----"){
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
        out << input[1][k] << endl;
    }

}
