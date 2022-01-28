#include <iostream>
#include <math.h>
#include <fstream>
#include <limits>
#include <stdlib.h>


class NeuralNetwork {
public:

NeuralNetwork(double TestValues[2][2]){

    set_Training_sets(TestValues);
}


NeuralNetwork(double PIRValues[2][2],double  ExpectedOutcome[2] ){

    set_Training_sets(PIRValues);
    set_ExpectedOutPuts(ExpectedOutcome);


}

private:
//setter methods
void set_Training_sets(double  Arr[2][2]){
    for(int j=0;j<2;j++){
        for(int k=0;k<2;k++){
            Training_set[j][k]=Arr[j][k];
        }
    }
}

void set_ExpectedOutPuts(double  Arr[2]){
    for(int j=0;j<2;j++){
        ExpectedOutPut[j]=Arr[j];
    }
}


//setting the up the trainig samples
double Training_set[2][2];
double  ExpectedOutPut[2];
int numOfTraining_sets=5;
//no of nodes
int numOfInputs=2;
int numOfH1Nodes=2;
int numOfH2Nodes=2;
int numOfOutputs=1;
int random=5;
//layers
double InputLayers[2];
double H1Layers[2];
double H2Layers[2];
double OutputLayers[1];
//Weights
double H1Weights[2][2];
double H2Weights[2][2];
double OutputWeights[2][1];
//Biases
double H1Biases[2];
double H2Biases[2];
double OutputBiases[1];
//learning rate
double lr= 0.01f;

//Utility functions
double loss(double Ideal,double Actual){return Ideal-Actual;}

double dSigmoid(double x){return x*(1-x);}

double Sigmoid(double x){return 1/(1+exp(-x));}

double Randomize(){return ((double)rand())/((double)RAND_MAX);}


public:

void setUp(NeuralNetwork object){

//Randomizing the H1Layer Weights
for(int j=0;j<2;j++){
    for(int k=0;k<2;k++){
        object.H1Weights[j][k]=Randomize();
    }
}

//Randomizing the H2Layer Weights
for(int j=0;j<2;j++){
    for(int k=0;k<2;k++){
        object.H2Weights[j][k]=Randomize();
    }
}

//Randomizing the Output weights
for(int j=0;j<2;j++){
    for(int k=0;k<1;k++){
        object.OutputWeights[j][k]=Randomize();
    }
}

//Randomizing the H1Biases
for(int j=0;j<2;j++){
    object.H1Biases[j]=Randomize();
}
//Randomizing the H2Biases
for(int k=0;k<2;k++){
    object.H2Biases[k]=Randomize();
}

//Randomizing the Output Biases
for(int j=0;j<1;j++){
    object.OutputBiases[j]=Randomize();
}

}

int count=0;
double OutputStore[2];
void Run(NeuralNetwork object){

//main loop

for(int x=0;x<2;x++){
          int i=x;
        for(int n=0;n<10000;n++){

    //getting the current training samples
  
        
            //working with the current set using the variable i
                                                                    //may have to replace all the named number vars in the loops to actual numbers
        
  

            //forward propagations
            //The inputs and the h1 layer
            for(int j=0;j<2;j++){
                double activation= object.H1Biases[j];
              for(int k=0;k<2;k++){
                    activation+= Training_set[i][k]*object.H1Weights[j][k];
                }
                object.H1Layers[j]= Sigmoid(activation);
            }

            //the h1 layer and the h2 layer
            for(int j=0;j<2;j++){
                double acitvation= object.H2Biases[j];
                for(int k=0;k<2;k++){
                    acitvation+= object.H1Layers[j]* object.H2Weights[j][k];
                }
                object.H2Layers[j]= Sigmoid(acitvation);
            }
            //the h2 layer and the final output layer
            for(int j=0;j<1;j++){
                    double activation= object.OutputBiases[j];
                    for(int k=0;k<2;k++){
                        activation+= object.H2Layers[k]* object.OutputWeights[k][j];
                    }
                    object.OutputLayers[j]= Sigmoid(activation);
            }


//displaying the data in between Samples
std::cout<<"\n";
        std::cout<<"input1:"<<Training_set[i][0]<<"  "<<"input2:"<<Training_set[i][1]<<"\n";
       std::cout<<"Output:"<<object.OutputLayers[0]<<"  "<<"ExpectedOutout:"<<ExpectedOutPut[i]<<"\n";
std::cout<<"\n";

            //backward propagation
            //Calculating the output delta
                double OutputDelta[1];
                double OutputError[1];
                
                for(int j=0;j<1;j++){
                    OutputError[j]= loss(ExpectedOutPut[i],object.OutputLayers[j]);
                    OutputDelta[j]= OutputError[j]* (dSigmoid(object.OutputLayers[j]));
                }
       
                //calculating the h2 layer deltas
                double H2Delta[2];
                double H2Error[2];
                for(int j=0;j<1;j++){
                    for(int k=0;k<2;k++){
                        H2Error[k]+= OutputDelta[j]* object.OutputWeights[k][j];
                        H2Delta[k]= H2Error[k]* dSigmoid(object.H2Layers[k]);
                    }
                }

                //calculating the deltas for the h1 layers
                double H1Delta[2];
                double H1Error[2];
                for(int j=0;j<2;j++){
                    for(int k=0;k<2;k++){
                        H1Error[j]+= H2Delta[k]* object.H2Weights[j][k];
                    }
                    H1Delta[j]=  H1Error[j]*dSigmoid(object.H1Layers[j]);
                }

                //calculating the changed weights
                //changing the output weights
                for(int j=0;j<1;j++){
                    object.OutputBiases[j]+= OutputDelta[j]*lr;
                    for(int k=0;k<2;k++){
                        object.OutputWeights[k][j]+= object.H2Layers[k]* OutputDelta[j]*lr;
                    }
                }

                //calculating the h2 layer weights
                for(int j=0;j<2;j++){
                    object.H2Biases[j]+= H2Delta[j]*lr;
                    for(int k=0;k<2;k++){
                        object.H2Weights[j][k]+= object.H1Layers[k] * H2Delta[j]*lr;
                    }
                }

                //calculating the h1 layer weights
                for(int j=0;j<2;j++){
                    object.H1Biases[j]+= H1Delta[j]*lr;
                    for(int k=0;k<2;k++){
                        object.H1Weights[j][k]+= Training_set[i][k]* H1Delta[j]*lr;
                    }
                }


            OutputStore[i]=object.OutputLayers[0];            

    }


}

        std::ofstream file("Logs",std::ios::app);

file<<"\n";
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                file<<"   "<<object.H1Weights[j][k]<<"\n";
            }
        }

        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                file<<"   "<<object.H2Weights[j][k]<<"\n";
            }
        }

        for(int j=0;j<1;j++){
            for(int k=0;k<2;k++){
                file<<"  "<<object.OutputWeights[k][j]<<"\n";
            }
        }



}



//using offline learning


void Test(NeuralNetwork object){


for(int x=0;x<4;x++){
          int i=x;
            if(i>1&&i==2){
                i=0;
            }
                if(i>2&&i==3){
                    i=1;
                }
        for(int n=0;n<10000;n++){

    //getting the current training samples
  
        
            //working with the current set using the variable i
                                                                    //may have to replace all the named number vars in the loops to actual numbers

            //forward propagations
            //The inputs and the h1 layer
            for(int j=0;j<2;j++){
                double activation= object.H1Biases[j];
              for(int k=0;k<2;k++){
                    activation+= Training_set[i][k]*object.H1Weights[j][k];
                }
                object.H1Layers[j]= Sigmoid(activation);
            }

            //the h1 layer and the h2 layer
            for(int j=0;j<2;j++){
                double acitvation= object.H2Biases[j];
                for(int k=0;k<2;k++){
                    acitvation+= object.H1Layers[j]* object.H2Weights[j][k];
                }
                object.H2Layers[j]= Sigmoid(acitvation);
            }
            //the h2 layer and the final output layer
            for(int j=0;j<1;j++){
                    double activation= object.OutputBiases[j];
                    for(int k=0;k<2;k++){
                        activation+= object.H2Layers[k]* object.OutputWeights[k][j];
                    }
                    object.OutputLayers[j]= Sigmoid(activation);
            }


//displaying the data in between Samples
std::cout<<"\n";
        std::cout<<"input1:"<<Training_set[i][0]<<"  "<<"input2:"<<Training_set[i][1]<<"\n";
       std::cout<<"Output:"<<object.OutputLayers[0]<<"  "<<"ExpectedOutout:"<<ExpectedOutPut[i]<<"\n";
std::cout<<"\n";

            
            //backward propagation
            //Calculating the output delta
                double OutputDelta[1];
                double OutputError[1];
                
                for(int j=0;j<1;j++){
                    OutputError[j]= loss(ExpectedOutPut[i],object.OutputLayers[j]);
                    OutputDelta[j]= OutputError[j]* (dSigmoid(object.OutputLayers[j]));
                }
       
                //calculating the h2 layer deltas
                double H2Delta[2];
                double H2Error[2];
                for(int j=0;j<1;j++){
                    for(int k=0;k<2;k++){
                        H2Error[k]+= OutputDelta[j]* object.OutputWeights[k][j];
                        H2Delta[k]= H2Error[k]* dSigmoid(object.H2Layers[k]);
                    }
                }

                //calculating the deltas for the h1 layers
                double H1Delta[2];
                double H1Error[2];
                for(int j=0;j<2;j++){
                    for(int k=0;k<2;k++){
                        H1Error[j]+= H2Delta[k]* object.H2Weights[j][k];
                    }
                    H1Delta[j]=  H1Error[j]*dSigmoid(object.H1Layers[j]);
                }


                if(x>1){
                //calculating the changed weights
                //changing the output weights
                for(int j=0;j<1;j++){
                    object.OutputBiases[j]+= OutputDelta[j]*lr;
                    for(int k=0;k<2;k++){
                        object.OutputWeights[k][j]+= object.H2Layers[k]* OutputDelta[j]*lr;
                    }
                }

                //calculating the h2 layer weights
                for(int j=0;j<2;j++){
                    object.H2Biases[j]+= H2Delta[j]*lr;
                    for(int k=0;k<2;k++){
                        object.H2Weights[j][k]+= object.H1Layers[k] * H2Delta[j]*lr;
                    }
                }

                //calculating the h1 layer weights
                for(int j=0;j<2;j++){
                    object.H1Biases[j]+= H1Delta[j]*lr;
                    for(int k=0;k<2;k++){
                        object.H1Weights[j][k]+= Training_set[i][k]* H1Delta[j]*lr;
                    }
                }

            OutputStore[i]= object.OutputLayers[0];
             }

        }
    }




} 


~NeuralNetwork(){

    
for(int i=0;i<2;i++){

    std::cout<<"this is a :"<<OutputStore[i]<<" "<<"Aproximatley"<<"\n";
}


}





};