#include <iostream>
#include "Recursive.hpp"

int main(int argc,char* argv[]){

    double Inputs[3]={0.0,1.0,0.3};
    double Expected_Output[2]={0,1};

    NeuralNetwork Data(Inputs,Expected_Output);
Data.setUP(Data);




Data.Run(Data);




    return 0;
}
