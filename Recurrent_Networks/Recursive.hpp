#include <iostream>
#include <math.h>
#include <vector>
#include <cstdlib>


class NeuralNetwork {
public:
NeuralNetwork(double time_Series[2],double Expected_Result[2]){

    set_Series(time_Series,Expected_Result);

}


void set_Series(double time_series[2],double expected_results[2]){
    for(int j=0;j<2;j++){
        Time_Series_Inputs[j]=time_series[j];
        Expected_Results[j]=expected_results[j];
    }

}




double Time_Series_Inputs[2];
double Expected_Results[2];


double Context_I_Neurons[2];

double Context_H1_Biases[2];
double Context_H2_Biases[2];
double Context_H3_Biases[2];

double Context_H1_Weights[2];
double Context_H2_Weights[2];
double Context_H3_Weights[2];

double Context_H1_Neurons[2];
double Context_H2_Neurons[2];
double Context_H3_Neurons[2];

double Context_O1_biases[2];
double Context_O2_biases[2];

double Context_O1_Weights[3];
double Context_O2_Weights[3];

double Context_O1_Neurons[2];
double Context_O2_Neurons[2];



double I1_Neuron[1];
double I2_Neurons[1];
double H1_Neuron[1];
double H2_Neuron[1];
double H3_Neurons[1];
double O1_Neuron[1];
double O2_Neuron[1];

//weihgts for the current timestep network
double H1_Weights[2];
double H2_Weights[2];
double H3_Weights[2];

double O1_Weights[3];
double O2_Weights[3];

//Biases
double H1_Biases[1];
double H2_Biases[1];
double H3_Biases[1];
 double O1_Biases[1];
double O2_Biases[1];

double lr=0.01;

//utility functions

double Sigmoid(double x){return 1/(1+exp(-x));}

double dSigmoid(double x){return x*(1-x);}

double Randomize(){return ((double)rand())/((double)RAND_MAX);}

double loss_P1(double Ideal,double Actual){return Ideal-Actual;}

double loss_P2(double result1,double result2){return result1+result2;}

void setUP(NeuralNetwork object){


for(int j=0;j<2;j++){
    H1_Weights[j]=Randomize();
    H2_Neuron[j]=Randomize();
    H3_Neurons[j]=Randomize();
}

for(int j=0;j<3;j++){
     O1_Weights[j]=Randomize();
    O2_Weights[j]=Randomize();
}



for(int k=0;k<1;k++){
    H1_Biases[k]=Randomize();
    H2_Biases[k]=Randomize();
    H3_Biases[k]=Randomize();
    O1_Biases[k]=Randomize();
    O2_Biases[k]=Randomize();

    
}
//initial the context input neurons as well

    for(int j=0;j<2;j++){
    Context_I_Neurons[j]=Time_Series_Inputs[j];
    }


for(int j=0;j<2;j++){
double me=Randomize();
double me2=Randomize();
double me3=Randomize();


   Context_H1_Weights[j]= me;
    Context_H2_Weights[j]= me2;
    Context_H3_Weights[j]= me3;

}

for(int j=0;j<3;j++){
       

    Context_O1_Weights[j]= Randomize();
    Context_O2_Weights[j]= Randomize();

   
}


       
      for(int j=0;j<2;j++){
    Context_H1_Biases[j]= Randomize();
    Context_H2_Biases[j]= Randomize();
    Context_H3_Biases[j]= Randomize();
    Context_O1_biases[j]=Randomize();
    Context_O2_biases[j]= Randomize();

      }

  
  


}


void Run(NeuralNetwork object){
//main loop 

for(int n=0;n<10000;n++){

    // normal foraward propagation
      double activation_1;
     double activation_2;
     double activation_3;
    for(int j=0;j<2;j++){
        double activation_1= H1_Biases[0];
        double activation_2= H2_Biases[0];
        double activation_3= H3_Biases[0];

        activation_1+= H1_Weights[j]* Time_Series_Inputs[j];
        activation_2+= H2_Weights[j]* Time_Series_Inputs[j];
        activation_3+= H3_Weights[j]* Time_Series_Inputs[j];
    }
        H1_Neuron[0]= Sigmoid(activation_1);
        H2_Neuron[0] = Sigmoid(activation_2);
        H3_Neurons[0]= Sigmoid(activation_3);



    //we also need to pass the initial input values into the context input layers
        double activation_CH1[2];
        double activation_CH2[2];
        double activation_CH3[2];
    for(int k=0;k<2;k++){
        activation_CH1[k]= Context_H1_Biases[0];
        activation_CH2[k]= Context_H2_Biases[0];
        activation_CH3[k]= Context_H3_Biases[0];

       activation_CH1[k]+= Context_H1_Weights[k]* Context_I_Neurons[k];
      activation_CH2[k]+= Context_H2_Weights[k]* Context_I_Neurons[k];
        activation_CH3[k]+= Context_H3_Weights[k]* Context_I_Neurons[k];
    
    Context_H1_Neurons[k]= Sigmoid(activation_CH1[k]);
    Context_H2_Neurons[k]= Sigmoid(activation_CH2[k]);
    Context_H3_Neurons[k]= Sigmoid(activation_CH3[k]);

    }
//concating these values into array
double Context_H_layers[3][2];
Context_H_layers[0][0]= Context_H1_Neurons[0];
Context_H_layers[0][1]= Context_H1_Neurons[1];
Context_H_layers[1][0]= Context_H2_Neurons[0];
Context_H_layers[1][1]= Context_H2_Neurons[1];
Context_H_layers[2][0]= Context_H3_Neurons[0];
Context_H_layers[2][1]= Context_H3_Neurons[1];








double H_layers[3];
       H_layers[0]= H1_Neuron[0];
       H_layers[1]= H2_Neuron[0];
       H_layers[2]= H3_Neurons[0];




        //continuing the propagation
        double activation_1b;
        double activation_2b;
        for(int j=0;j<3;j++){
             activation_1b= O1_Biases[0];
             activation_2b= O2_Biases[0];

            activation_1b+= O1_Weights[j]* H_layers[j];
            activation_2b+= O2_Weights[j]* H_layers[j];

        }

        O1_Neuron[0]= Sigmoid(activation_1b);
        O2_Neuron[0]= Sigmoid(activation_2b);

  



        //context layer work
      double Context_O1_activation[2];
      double Context_O2_activation[2];
       for(int k=0;k<2;k++){
            Context_O1_activation[k]= Context_O1_biases[k];
            Context_O2_activation[k]= Context_O2_biases[k];
  
             for(int j=0;j<3;j++){
            Context_O1_activation[k]+= Context_O1_Weights[j]* Context_H_layers[j][k];
            Context_O2_activation[k]+= Context_O2_Weights[j]* Context_H_layers[j][k];

            Context_O1_Neurons[k]= Sigmoid(Context_O1_activation[k]);
            Context_O2_Neurons[k]= Sigmoid(Context_O2_activation[k]);

                

            }
        }
     

       






        //backpropagation along with context neuron remberebce
        double Error1= loss_P1(Expected_Results[0],O1_Neuron[0]);
        double Error2= loss_P1(Expected_Results[1],O2_Neuron[0]);


        double Final_Error= loss_P2(Error1,Error2);

        double Output_Derivative= O1_Neuron[0]+ O2_Neuron[0];

        double Output_overall_Delta= Final_Error* (dSigmoid(Output_Derivative));


        //calculating the hidden layer deltas
        double h1_error;
        double h2_error;
        double h3_error;

                //overall error for h1 
                h1_error+= O1_Weights[0]* Output_overall_Delta;
                h1_error+= O2_Weights[0]*Output_overall_Delta;
           
                
                //overall error for h2
                h2_error+= O1_Weights[1]* Output_overall_Delta;
                h2_error+= O2_Weights[1]* Output_overall_Delta;
                //overall error for h3
                h3_error+= O1_Weights[2]* Output_overall_Delta;
                h3_error+= O2_Weights[2]* Output_overall_Delta;


                double h1_Delta;
                double h2_Delta;
                double h3_Delta;

                h1_Delta= h1_error* ((dSigmoid(H1_Neuron[0])));
                h2_Delta= h2_error* ((dSigmoid(H2_Neuron[0])));
                h3_Delta= h3_error* ((dSigmoid(H3_Neurons[0])));



                //context layers backPropagation
                //calculate the error for the context output neurons
                double CO_Error1[2];
                double CO_Error2[2];
                double C_Final_Error[2];
                for(int j=0;j<2;j++){
                    CO_Error1[j]= loss_P1(O1_Neuron[0],Context_O1_Neurons[j]);
                    CO_Error2[j]= loss_P1(O2_Neuron[j],Context_O2_Neurons[j]);
             
              
    
                    C_Final_Error[j]= loss_P2(CO_Error1[j],CO_Error2[j]);
                
                   
                }
                  
                double C_Output_Derivative[2];
                    for(int j=0;j<2;j++){
                        C_Output_Derivative[j]= Context_O1_Neurons[j]+Context_O2_Neurons[j];
                    }                


                //overall delta for a certain network in time
                double C_Output_overall_Delta[2];

                for(int j=0;j<2;j++){
                    C_Output_overall_Delta[j]= C_Final_Error[j]* (dSigmoid(C_Output_Derivative[j]));
                   
                }


                //calculating the context h layers values
                double C_h1_error[2];
                double C_h2_error[2];
                double C_h3_error[2];

double Context_layers_OWeights[2][3];

    for(int j=0;j<1;j++){
        for(int k=0;k<3;k++){
            Context_layers_OWeights[j][k]= Context_O1_Weights[k];

        }
    }
    for(int j=1;j<2;j++){
        for(int k=0;k<3;k++){
            Context_layers_OWeights[j][k]= Context_O2_Weights[k];
         
        }
    }




                    for(int j=0;j<2;j++){
                        for(int k=0;k<1;k++){
                            C_h1_error[j]+= Context_layers_OWeights[j][k]* C_Output_overall_Delta[j];
                          
                        }
                    }
                    for(int j=0;j<2;j++){
                        for(int k=1;k<2;k++){
                            C_h2_error[j]+= Context_layers_OWeights[j][k]* C_Output_overall_Delta[j];
                        }
                    }
                    for(int j=0;j<2;j++){
                        for(int k=2;k<3;k++){
                            C_h3_error[j]+= Context_layers_OWeights[j][k]* C_Output_overall_Delta[j];
                        }
                    }

                double C_h1_Deltas[2];
                double C_h2_Deltas[2];
                double C_h3_Deltas[2];

                for(int j=0;j<2;j++){
                    C_h1_Deltas[j]= C_h1_error[j]* (dSigmoid(Context_H1_Neurons[j]));

                    C_h2_Deltas[j]= C_h2_error[j]* ((dSigmoid(Context_H2_Neurons[j])));

                    C_h3_Deltas[j]= C_h3_error[j]* ((dSigmoid(Context_H3_Neurons[j])));
                }

                //changing the weights
                //first the context networks
                for(int j=0;j<2;j++){
                Context_H1_Biases[j]+= C_h1_Deltas[j]* lr;
                Context_H2_Biases[j]+= C_h2_Deltas[j]* lr;
                Context_H3_Biases[j]+= C_h3_Deltas[j]* lr;
                }
                for(int j=0;j<2;j++){
                    Context_O1_biases[j]+= C_Output_overall_Delta[j]* lr;
                    Context_O2_biases[j]+= C_Output_overall_Delta[j]* lr;
                }
   

                
                for(int j=0;j<1;j++){
                    for(int k=0;k<3;k++){
                        Context_layers_OWeights[j][k]+= C_Output_overall_Delta[j]* Context_H_layers[k][j]*lr; 
                    }
                }
                for(int j=1;j<2;j++){
                    for(int k=0;k<3;k++){
                        Context_layers_OWeights[j][k]+= C_Output_overall_Delta[j]* Context_H_layers[k][j]*lr;
                    }
                }
        
                //now for the hidden context weights
                for(int j=0;j<2;j++){
                    Context_H1_Weights[j]+= C_h1_Deltas[j]* Context_I_Neurons[j]* lr;
                    Context_H2_Weights[j]+= C_h2_Deltas[j]* Context_I_Neurons[j]* lr;
                    Context_H3_Weights[j]+= C_h3_Deltas[j]* Context_I_Neurons[j]* lr;
                }
                


                //now using the Context layered weights and biases to help determine the current weights and biases
                double O1_sum;
                double O2_sum;
                for(int j=0;j<2;j++){
                O1_sum+= Context_O1_biases[j];
                O2_sum+= Context_O2_biases[j];
                }
                O1_Biases[0]+= (O1_sum/2)* Output_overall_Delta * lr;
                O2_Biases[0]+= (O2_sum/2)* Output_overall_Delta * lr;

                for(int j=0;j<2;j++){
                    
                    H1_Biases[0]+= Context_H1_Biases[j];
                    H2_Biases[0]+= Context_H2_Biases[j];
                    H3_Biases[0]+= Context_H3_Biases[j];
                }
                H1_Biases[0]= (H1_Biases[0]/2)* h1_Delta* lr;
                H2_Biases[0]= (H2_Biases[0]/2)* h2_Delta* lr;
                H3_Biases[0]= (H3_Biases[0]/2)* h3_Delta* lr;


                //weights
                double O1_W_sum;
                double O2_W_sum;
                for(int j=0;j<3;j++){
                    O1_W_sum+= Context_O1_Weights[j];
                    O2_W_sum+= Context_O2_Weights[j];
                }

                    for(int k=0;k<3;k++){
                    O1_Weights[k]+= /*(O1_W_sum-O1_Weights[k])*lr*/((O1_W_sum/2)-O1_Weights[k])* Output_overall_Delta* lr;
                    O2_Weights[k]+= /*(O2_W_sum-O2_Weights[k])*lr;*/((O2_W_sum/2)-O2_Weights[k])* Output_overall_Delta* lr;
                    }
  
                    double h1_sum;
                    double h2_sum;
                    double h3_sum;
                    for(int j=0;j<2;j++){
                        h1_sum+=Context_H1_Weights[j];
                        h2_sum+= Context_H2_Weights[j];
                        h3_sum+= Context_H3_Weights[j];
                    }

                    for(int j=0;j<2;j++){
                        H1_Weights[j]+= /*(h1_sum-H1_Weights[j])*lr*/((h1_sum/2)-H1_Weights[j])* h1_Delta* lr;
                        H2_Weights[j]+= /*(h2_sum-H2_Weights[j])*lr;*/((h2_sum/2)-H2_Weights[j])* h2_Delta* lr;
                        H3_Weights[j]+= /*(h3_sum-H3_Weights[j])*lr;*/((h3_sum/2)-H3_Weights[j])* h3_Delta* lr;
                    }



std::cout<<O1_Neuron[0]<<"  ";

std::cout<<"\n";

std::cout<<O2_Neuron[0]<<"   ";



       
      
           



}




}


};