#include <iostream>
#include <vector>
#include "new_Recursion.hpp"




 
void set_Binary()
{  
 double a[10]; 
 double b[10];
int n, i,x;    
std::cout<<"Enter the number to convert: \n";  
  std::cin>>n;
std::cout<<"Now enter a second number:   \n";  
std::cin>>x;
int expected_value= n+x;

for(i=0; n>0; i++)    
{    
a[i]=n%2;    
n= n/2;  

} 
for(int i=0;x>0;i++){
b[i]=x%2;
x=x/2;

}



std::vector<double> arr;
//expected_value= expected_value+1;
int size= expected_value+1;
for(int i=0;expected_value>0;i++){
double me= expected_value%2;

arr.push_back( me);

expected_value=expected_value/2;

}

  


NeuralNetwork Data(a,b,arr);

   Data.setUp();
   Data.Run();   
  Data.display();

 

}



int main(){


 set_Binary();

  
    return 0;
}