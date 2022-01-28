#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>

                    //restart or resize all arrays



class NeuralNetwork{
public:
NeuralNetwork(int inputArr[3],int Output){

   
        set_Training_sets(inputArr);
        set_ExpectedOutcome(Output);


}

private:
void  set_Training_sets(int arr[3]){

    for(int i=0;i<3;i++){
        Training_set[i]=arr[i];
    }
}

void set_ExpectedOutcome(int outcome){
    ExpectedOutPut=outcome;
}



//training inputs
int Training_set[3];
//Expected Output
int ExpectedOutPut;
int max_TrainingSets=3;




double sumOfLetter;
double lr=0.01f;

//setting the numbers
int numOfInputs=3;
int numOfHiddenNodes=4;
int numOfOutputs=1;
//numbers of layers/nodes
double InputLayers[3];
double HiddenLayers1[2];
double HiddenLayers2[2];
double OuputLayers[1];
//weights and biases
double HiddenLayerWeights1[3][2];
double HiddenLayerWeights2[2][2];
double OutputLayerWeights[2][1];
double HiddenLayerBiases1[2];
double HiddenLayerBiases2[2];
double OutputLayerBiases[1];







//utility functions
double Sigmoid(double x){return 1/(1+exp(-x));}

double dSigmoid(double x){return x*(1-x);}

double Randomize(){return ((double) rand())/((double)RAND_MAX);}

double loss(double Ideal,double Actual){return Ideal - Actual;}


public:

void setUp(){

    //looping through the weights of the hidden layers
    for(int j=0;j<3;j++){
        for(int k=0;k<2;k++){
           HiddenLayerWeights1[j][k]=Randomize();
        }
    }
    //looping through the output layer weights and randomizing them 
    for(int j=0;j<2;j++){
        for(int k=0;k<1;k++){
            OutputLayerWeights[j][k]=Randomize();
        }
    }
    //setting the Hidden Layer Biases
    for(int j=0;j<2;j++){
   HiddenLayerBiases1[j]=Randomize();
    }

    for(int j=0;j<2;j++){
        for(int k=0;k<2;k++){
            HiddenLayerWeights2[j][k]=Randomize();
        }
    }


    //setting the Output Layer Biases
    for(int k=0;k<numOfOutputs;k++){
        OutputLayerBiases[k]=Randomize();
    }

   

}


void Run(){
  
//main loop
for(int n=0;n<10000;n++){
        



        //forward Propagate
        //looping over the inputs and multiplying by the weights
        //first h layer
        for(int j=0;j<2;j++){
            double activation= HiddenLayerBiases1[j];
            for(int y=0;y<3;y++){
         
                activation+=Training_set[y]*HiddenLayerWeights1[y][j];
                  
                
  
            }
             HiddenLayers1[j]= Sigmoid(activation);
  
        }

        //second h layer
        //make sure you set the loops right and that they only loop over the required feild for a particular section
      
          
                for(int y=0;y<2;y++){
                 double activation= HiddenLayerBiases2[y];
                for(int k=0;k<2;k++){
                    activation+= HiddenLayers1[y]*HiddenLayerWeights2[k][y];
       
                }
                HiddenLayers2[y]= Sigmoid(activation);
    
                }
           



        //Ouput layers
        for(int j=0;j<1;j++){
            double activation= OutputLayerBiases[j];
             
                for(int k=0;k<2;k++){
                    activation+= HiddenLayers2[k]*OutputLayerWeights[k][j];
                                        
                }

            OuputLayers[j]= Sigmoid(activation);
     
  
        }


//std::cout<<"\n";
 //   std::cout<<"Input1:"<<Training_set[0]<<"   "<<"Input2:"<<Training_set[1]<<"   "<<"Input3:"<<Training_set[2]<<"\n";
 //   std::cout<<"OutPut"<<OuputLayers[0]<<"  "<<"ExprectedOutPut:"<<ExpectedOutPut<<"\n";
//std::cout<<"\n";


 


     double OutputDelta[1];
        //backwards propagating
        double OutputError;
        //setting the output delta
        for(int j=0;j<1;j++){
          OutputError = loss(ExpectedOutPut, OuputLayers[j]);
       
        OutputDelta[j]= OutputError*(dSigmoid(OuputLayers[j]));
        }

        //setting the Second Hidden Layer Deltas
        double H2Delta[2];
        double H2Error[2];
        for(int j=0;j<2;j++){   
            for(int y=0;y<2;y++){
            for(int k=0;k<1;k++){
                H2Error[j]+=OutputDelta[k]* OutputLayerWeights[y][k];
            }
            }
           
   H2Delta[j]= H2Error[j]*(dSigmoid(HiddenLayers2[j]));


        }

        //setting the First Hidden Layer Deltas

        double H1Delta[2];
        double H1Error[2];
        for(int j=0;j<2;j++){
            for(int y=0;y<2;y++){
    
                H1Error[j]+=H2Delta[j]*HiddenLayerWeights2[j][y];
            
            }
    H1Delta[j]= H1Error[j]*(dSigmoid(HiddenLayers1[j]));
          
        }


        //changing the weights

        //first calculating the output weights
        for(int j=0;j<1;j++){
            OutputLayerBiases[j]+= OutputDelta[j]*lr;
            for(int y=0;y<2;y++){
            for(int k=0;k<2;k++){
                OutputLayerWeights[y][j]+= HiddenLayers2[y]*OutputDelta[j]*lr;
          

            }
            }

        }

        //calculating the second Hidden Layer Weights
        for(int j=0;j<2;j++){
            HiddenLayerBiases2[j]+=H2Delta[j]*lr;
            for(int y=0;y<2;y++){
          
                    HiddenLayerWeights2[y][j]+= HiddenLayers1[y]*H2Delta[j]*lr;
                 
        
            }

        }


    //calculating First Layer Hidden Weights
    for(int y=0;y<3;y++){

    for(int j=0;j<2;j++){
           HiddenLayerBiases1[j]+=H1Delta[j]*lr;
            HiddenLayerWeights1[y][j]+= Training_set[y]*H1Delta[j]*lr;
            
    }
    }
    

    
}



}


void display(){
    std::cout<<std::endl;
    std::cout<<OuputLayers[0]<<'\n';
    std::cout<<std::endl;

std::cout<<"\n";
std::cout<<"First Hidden Layer Weights\n";
    for(int j=0;j<3;j++){
        for(int k=0;k<2;k++){
            std::cout<<HiddenLayerWeights1[j][k]<<"   ";
        }
     
    }
std::cout<<"\n";
std::cout<<"Secong Hidden Layer Weights\n";
    for(int j=0;j<2;j++){
        for(int k=0;k<2;k++){
            std::cout<<HiddenLayerWeights2[j][k]<<"   ";
        }
    }


std::cout<<"\n";
std::cout<<"Final Output Layer Weights\n";
    for(int j=0;j<2;j++){
        for(int k=0;k<1;k++){
            std::cout<<OutputLayerWeights[j][k]<<"   ";
        }
    }


}

};
