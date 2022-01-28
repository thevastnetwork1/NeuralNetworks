#include <iostream>
#include "RecAlgorithm.hpp"

int main(){

int arr[3]={1,1,1};
int output=1;
NeuralNetwork Data(arr,output);

Data.setUp();

Data.Run();

Data.display();




    return 0;
}
