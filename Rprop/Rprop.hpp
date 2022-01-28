#include <iostream>
#include <math.h>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <fstream>

class RpropNetwork {
public:
RpropNetwork(double Inputs[2][2],double Outputs[2]){

    set_Training_sets(Inputs);
    set_Outputs(Outputs);

}

~RpropNetwork(){

    for(int j=0;j<2;j++){
std::cout<<"Final Outputs:"<<OutputStore[j]<<"\n";
    }
}

private:
void set_Training_sets(double arr[2][2]){

    for(int j=0;j<2;j++){
        for(int k=0;k<2;k++){
            Training_sets[j][k]=arr[j][k];
        }
    }

}

void set_Outputs(double arr[2]){
    for(int j=0;j<2;j++){
        EOutputs[j]=arr[j];
    }

}

double Training_sets[2][2];
double EOutputs[2];
int numOfTrainingSets=2;

//defining our network structure
//layers
int numOfInputs=2;
int numOfHiddenNodes=4;
int numOutputs=2;

double Inputs[2];
double H1Layer[2];
double H2Layer[2];
double Outputs[1];


//weights and the respective learning rates
double H1Weights[2][2];
double H2Weights[2][2];
double OutputWeights[2][1];

double H1lr[2][2];
double H2lr[2][2];
double Outputlr[2][1];



//biases
double InputBiases[2];
double H1Biases[2];
double H2Biases[2];
double OutputBiases[2];
//dealing  with the offline approach and Rprop too /this is a single variable that will contian  the overall error
double Error;
double Prev_Gradient;
double Prev_Weight_Delta_H1[2][2];
double Prev_Weight_lr_H1[2][2];
double Prev_Weight_Delta_H2[2][2];
double Prev_Weight_lr_H2[2][2];
double Prev_Weight_Delta_output[2][1];
double Prev_Weight_lr_output[2][1];

double Prev_Weight_H1[2][2];
double Prev_Weight_H2[2][2];
double Prev_Weight_output[2][1];

double Prev_Biases_Delta_H1[2];
double Prev_Biases_Delta_H2[2];
double Prev_Biases_Delta_output[1];
//creating the weight and biases individual deltas

double H1Weight_Delta[2][2];
double H2Weight_Delta[2][2];
double OutputWeight_Delta[2][1];
double H1Biases_Delta[2];
double H2Biases_Delta[2];
double OutputBiases_Delta[1];

//initializing the positive and negative given delta values
double W_pos_delta=1.2;
double W_neg_delta=0.5;
double OutputStore[2];


//Utility functions
double dSigmoid(double x){return x*(1-x);}

double Sigmoid(double x){return 1/(1+exp(-x));}

double Randomize(){return ((double)rand())/((double)RAND_MAX);}

double loss(double Ideal,double Actual){return Ideal-Actual;}

double srand(double);
double max=50;
double min=pow(10,-6);
double seed= (max-min)+min;

double lrRandomize(){
   double random=rand()%50;
    return random;
    }



public:
void setUp(RpropNetwork object){

//setting the weights
for(int j=0;j<2;j++){
    for(int k=0;k<2;k++){
        object.H1Weights[j][k]=Randomize();
    }
}
for(int j=0;j<2;j++){
    for(int k=0;k<2;k++){
        object.H2Weights[j][k]=Randomize();
    }
}
for(int j=0;j<1;j++){
    for(int k=0;k<2;k++){
        object.OutputWeights[k][j]=Randomize();
    }
}

//settting the biases
for(int j=0;j<2;j++){
    object.H1Biases[j]=Randomize();
}
for(int j=0;j<2;j++){
    object.H2Biases[j]=Randomize();
}
for(int j=0;j<1;j++){
    object.OutputBiases[j]=Randomize();
}
//setting the learning rates
for(int j=0;j<2;j++){
    for(int k=0;k<2;k++){
        object.H1lr[j][k]=lrRandomize();
    }
}
for(int j=0;j<2;j++){
    for(int k=0;k<2;k++){
        object.H2lr[j][k]=lrRandomize();
    }
}
for(int j=0;j<1;j++){
    for(int k=0;k<2;k++){
        object.Outputlr[k][j]=lrRandomize();    
        }
}

}


void Run(RpropNetwork object){

//main loop 
    for(int x=0;x<2;x++){
for(int n=0;n<10000;n++){

        int i=x;
    //forward prpagation

        for(int j=0;j<2;j++){
            double activation= object.H1Biases[j];
            for(int k=0;k<2;k++){
                activation+= Training_sets[i][k]* object.H1Weights[j][k]; 
            }
            object.H1Layer[j]= Sigmoid(activation);

        }

        //H2layer
        for(int j=0;j<2;j++){
            double activation= object.H2Biases[j];
            for(int k=0;k<2;k++){
                activation+= object.H1Layer[k] * object.H2Weights[j][k]; 
           }
           object.H2Layer[j]= Sigmoid(activation);
        }

        //output layer
        for(int j=0;j<1;j++){
            double acitvation= object.OutputBiases[j];
            for(int k=0;k<2;k++){
                acitvation+= object.H2Layer[k] * object.OutputWeights[k][j];
            }
            object.Outputs[j]= Sigmoid(acitvation);
        }


std::cout<<"\n";
        std::cout<<"Inputs1:"<<Training_sets[i][0]<<"  "<<"Input2:"<<Training_sets[i][1]<<"\n";
        std::cout<<"Output:"<<object.Outputs[0]<<"  "<<"ExpectedOutput:"<<EOutputs[i]<<"\n";
std::cout<<"\n";




        //Resilient Propagation
        //Calculating the error for all cycles
        
            double Range= loss(EOutputs[i],object.Outputs[0]);
        Error+= Range; //pow(Range,2);
       
            
        

        double OutputDelta;
        if(n%2==0&&n!=0){

        OutputDelta= Error * (dSigmoid(object.Outputs[0])); 

            if(Prev_Gradient){

            if(Prev_Gradient* OutputDelta>0){
                  std::cout<<"if\n";
                //goes the logic to apply for both weight deltas and biases delta to increase them a little 
                    //h2
                    double h2Error;
                    for(int j=0;j<1;j++){
                        for(int k=0;k<2;k++){
                            h2Error+= OutputDelta * object.OutputWeights[k][j];
                            object.H2Biases_Delta[k]= h2Error * (dSigmoid(object.H2Layer[k]));
                          
                        }
                        
                    }

                    //h1
                    double h1Error;
                    for(int j=0;j<2;j++){
                        for(int k=0;k<2;k++){
                            h1Error+= object.H2Biases_Delta[k] * object.H2Weights[j][k];
                        }
                        object.H1Biases_Delta[j]= h1Error * (dSigmoid(object.H1Layer[j]));
             
                    }
                    
                    //calculating the weight deltas
                    for(int j=0;j<1;j++){
                        for(int k=0;k<2;k++){
                            object.OutputWeight_Delta[k][j]*= W_pos_delta;
                        }
                    }

                    for(int j=0;j<2;j++){
                        for(int k=0;k<2;k++){
                            object.H2Weight_Delta[j][k]*= W_pos_delta;
                        }
                    }

                    for(int j=0;j<2;j++){
                        for(int k=0;k<2;k++){
                            object.H1Weight_Delta[j][k]*= W_pos_delta;
                        }
                    }

                    //loop through each weight learning rate and set them accordingly
                    for(int j=0;j<1;j++){
                        for(int k=0;k<2;k++){
                            //object.Outputlr[k][j]+= object.OutputWeight_Delta[k][j];
                            object.Outputlr[k][j]= OutputDelta * object.H2Biases_Delta[k];
                        }
                    }

                    for(int j=0;j<2;j++){
                        for(int k=0;k<2;k++){
                           // object.H2lr[j][k]+= object.H2Weight_Delta[j][k];
                           object.H2lr[j][k]= object.H2Biases_Delta[j]* object.H1Biases_Delta[k];
                        }
                    }

                    for(int j=0;j<2;j++){
                        for(int k=0;k<2;k++){
                           // object.H1lr[j][k]+= object.H1Weight_Delta[j][k];
                           object.H1lr[j][k]= object.H1Biases_Delta[j]* Training_sets[i][k];
                        }
                    }

                    //changin the weights based on the respective learning rates/ and biases
                    for(int j=0;j<1;j++){
                        object.OutputBiases[j]+=OutputDelta; 
                        for(int k=0;k<2;k++){
                            object.Outputlr[k][j]*= object.OutputWeight_Delta[k][j];
                            object.OutputWeights[k][j]+= object.Outputlr[k][j];
                        }
                    }

                    for(int j=0;j<2;j++){
                        object.H2Biases[j]+=object.H2Biases_Delta[j];
                        for(int k=0;k<2;k++){
                            object.H2lr[j][k]*= object.H2Weight_Delta[j][k];
                            object.H2Weights[j][k]+= object.H2lr[j][k];
                        }
                    }

                    for(int j=0;j<2;j++){
                        object.H1Biases[j]+= object.H1Biases_Delta[j];
                        for(int k=0;k<2;k++){
                            object.H1lr[j][k]*= object.H1Weight_Delta[j][k];
                            object.H1Weights[j][k]+= object.H1lr[j][k];
                        }
                    }

    

            }
            else if(Prev_Gradient * OutputDelta<0){
         std::cout<<"else if\n";
                //goes the logic to apply for both weight and biases delta to change them based on the different signs
                        
                //decrementing the weights delta by the neg constant
                for(int j=0;j<1;j++){
                    for(int k=0;k<2;k++){
                        object.OutputWeight_Delta[k][j]*= W_neg_delta;
                    }
                }

                for(int j=0;j<2;j++){
                    for(int k=0;k<2;k++){
                        object.H2Weight_Delta[j][k]*= W_neg_delta;
                    }
                }

                for(int j=0;j<2;j++){
                    for(int k=0;k<2;k++){
                        object.H1Weight_Delta[j][k]*= W_neg_delta;
                    }
                }

                //reverting the weight values back to their previous values
                for(int j=0;j<1;j++){
                    for(int k=0;k<2;k++){
                        object.OutputWeights[k][j]= object.Prev_Weight_output[k][j];
                    }
                }

                for(int j=0;j<2;j++){
                    for(int k=0;k<2;k++){
                        object.H2Weights[j][k]= object.Prev_Weight_H2[j][k];
                    }
                }

                for(int j=0;j<2;j++){
                    for(int k=0;k<2;k++){
                        object.H1Weights[j][k]= object.Prev_Weight_H1[j][k];
                    }
                }

            //*error prone
            //setting the respective weight learning rates to 0
            for(int j=0;j<1;j++){
                for(int k=0;k<2;k++){
                    object.Outputlr[k][j]=0;
                }
            }

            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    object.H2lr[j][k]=0;
                }
            }

            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    object.H1lr[j][k]=0;
                }
            }

            
            }
            else{
            std::cout<<"else\n";
                //the the prev gradient and the output delta product == 0
                //setting each weight learning rate to the previous learning rate
                for(int j=0;j<1;j++){
                    for(int k=0;k<2;k++){
                        object.OutputWeight_Delta[k][j]= object.Prev_Weight_lr_output[k][j];
                    }
                }
                
                for(int j=0;j<2;j++){
                    for(int k=0;k<2;k++){
                        object.H2Weight_Delta[j][k]= object.Prev_Weight_lr_H2[j][k];
                    }
                }

                for(int j=0;j<2;j++){
                    for(int k=0;k<2;k++){
                        object.H1Weight_Delta[j][k]= object.Prev_Weight_lr_H1[j][k];
                    }
                }

                //incrementing the Weights by a little
                    for(int j=0;j<1;j++){
                        for(int k=0;k<2;k++){
                            object.Outputlr[k][j]*= object.OutputWeight_Delta[k][j];
                            object.OutputWeights[k][j]+=object.Outputlr[k][j];
                        }
                    }

                    for(int j=0;j<2;j++){
                        for(int k=0;k<2;k++){
                            object.H2lr[j][k]*= object.H2Weight_Delta[j][k];
                            object.H2Weights[j][k]+= object.H2lr[j][k];
                        }
                    }

                    for(int j=0;j<2;j++){
                        for(int k=0;k<2;k++){
                            object.H1lr[j][k]*= object.H1Weight_Delta[j][k];
                            object.H1Weights[j][k]+= object.H1lr[j][k];
                        }
                    }
            
            

            }

            
                //saving the important stuff
                //saving the gradient
                 Prev_Gradient= OutputDelta;
            
                //saving the delta of the weights


                for(int j=0;j<1;j++){
                    for(int k=0;k<2;k++){
                        object.Prev_Weight_lr_output[k][j]= object.Outputlr[k][j];
                        object.OutputWeight_Delta[k][j]= object.Prev_Weight_lr_output[k][j];
                    }
                }

                for(int j=0;j<2;j++){
                    for(int k=0;k<2;k++){
                        object.Prev_Weight_lr_H2[j][k]= object.H2lr[j][k];
                        object.H2Weight_Delta[j][k]= object.Prev_Weight_lr_H2[j][k];
                    }
                }

                for(int j=0;j<2;j++){
                    for(int k=0;k<2;k++){
                        object.Prev_Weight_lr_H1[j][k]= object.H1lr[j][k];
                        object.H1Weight_Delta[j][k]= object.Prev_Weight_lr_H1[j][k];
                    }
                }

                //saving the weights
                for(int j=0;j<1;j++){
                    for(int k=0;k<2;k++){
                        object.Prev_Weight_output[k][j]= object.OutputWeights[k][j];
                    }
                }

                for(int j=0;j<2;j++){
                    for(int k=0;k<2;k++){
                        object.Prev_Weight_H2[j][k]= object.H2Weights[j][k];
                    }
                }

                for(int j=0;j<2;j++){
                    for(int k=0;k<2;k++){
                        object.Prev_Weight_H1[j][k]= object.H1Weights[j][k];
                    }
                }


            }
//file testing
 std::ofstream file("LogTest",std::ios::app);

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


     OutputStore[i]= object.Outputs[0];


}


}
                                        //fix the destructor output problem by creating an array store instead 
   
}



};