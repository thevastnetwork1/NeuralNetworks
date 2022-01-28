#include <iostream>
#include "HopField.hpp"


int do_stuff(int a,int b){
    return a-b;
}


int main(){


int inputs2[3][6]={{-1,-1,1,-1,-1,-1},{-1,-1,1,-1,-1,-1},{-1,1,-1,-1,-1,-1}};

    HopField_Network Test(inputs2);
Test.setUp();

   double *Arr= Test.Run();

        std::cout<<"next"<<"\n";
        restart:
        for(int i=0;i<6;i++){
          std::cout<<Arr[i]<<"  "; 
        }
                std::cout<<"****//RUNNING TEST//*****";



            int inputs[3][6]={{1,-1,1,1,1,1},{-1,1,1,1,1,1},{1,1,1,1,-1,1}};         

          HopField_Network Test_2(inputs);

            Test_2.setUp();
         double *Arr_2=Test_2.Run();

            std::cout<<"\n";
            std::cout<<"Predictions??****\n";

            for(int j=0;j<6;j++){
                std::cout<<Arr_2[j]<<"  ";
            }




    return 0;
}
