#include <iostream>
#include "T_spiral.hpp"

int main(int argc,char* argv[]){

std::cout<<"Please enter a positive value for R and then a negative value for the machine to learn properly.\n";
std::cout<<"Enter two numbers\n";


double  Points[2][2]={{34.0,23},{-23,-12}};
double  outputs[2]={1.0,0.0};




NeuralNetwork Data(Points,outputs);


Data.setUp(Data);

Data.Run(Data);
Data.Test(Data);







    return 0;
}