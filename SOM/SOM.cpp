#include <iostream>
#include <vector>
#include "SOM.hpp"

int  main(){
std::vector <double> inputs;

    for(int j=1;j<15;j++){
        inputs.push_back(j);
    }


    NeuralNetwork Data(inputs);
 
Data.SetUp_Round();

  std::vector <int> set;
  int help[4]={1,6,8};
    for(int i=0;i<3;i++){
        set.push_back(help[i]);
    }

  

Data.Run(set);

       


return 0;

}