#include <iostream>
#include "Rprop.hpp"

int main(int argc, char* argv[]){

double inputs[2][2]={{0.0,0.0},{0.0,0.1}};
double outputs[2]={1.0,0.0};


RpropNetwork Data(inputs,outputs);

Data.setUp(Data);

Data.Run(Data);

    return 0;
}