#include <iostream>
#include <math.h>
#include <cstdlib>
#include <vector>



class NeuralNetwork {
public:
NeuralNetwork(double inputs[10],double next_input[10],std::vector <double> Binary_code){

        set_Inputs(inputs,next_input);
        set_Expected(Binary_code);

}

public:
void set_Inputs(double inputs[10],double next_input[10]){

    for(int j=0;j<10;j++){
        Input.push_back(inputs[j]);
        next_Input.push_back(next_input[j]);
    }

}

void set_Expected(std::vector <double>vec){

    for(int k=0;k<vec.size();k++){
        Expected_value.push_back(vec[k]);
    }

}


std::vector<double>Input;
std::vector<double> next_Input;
std::vector <double> Expected_value;

double  H1_Neuron[1];
double H2_Neuron[1];
double H3_Neuron[1];

 double O1_Neuron[1];
double O2_Neuron[1];

//creating the matrices required for the weights for each timestep
double _H1_W[2];
double _H2_W[2];
double _H3_W[2];

double _O1_W[3];
double _O2_W[3];

double C_H1_W[3][3];
double C_H2_W[3][3];
double C_H3_W[3][3];

double C_H1_N[1][3];
double C_H2_N[1][3];
double C_H3_N[1][3];
double C_H_N[3];


double H1_Biases[1];
double H2_Biases[1];
double H3_Biases[1];

double O1_Biases[1];

double lr=0.01;

   double Future_H1_Bias, Future_H2_Bias, Future_H3_Bias;


//utility functions

double Sigmoid(double x){return 1/(1+exp(-x));}

double dSigmoid(double x){return x*(1-x);}

double Randomize(){return ((double)rand())/((double)RAND_MAX);}

double loss(double Ideal,double Actual){
   double result;

     result=Ideal-Actual;


    return result;
}





public:


void setUp(){
for(int j=0;j<3;j++){
    _O1_W[j]= Randomize();
    _O2_W[j]= Randomize();

}
for(int k=0;k<1;k++){

H1_Biases[k]=Randomize();
H2_Biases[k]=Randomize();
H3_Biases[k]=Randomize();

O1_Biases[k]= Randomize();

}

for(int k=0;k<2;k++){
_H1_W[k]= Randomize();
_H2_W[k]= Randomize();
_H3_W[k]= Randomize();
}


for(int k=0;k<3;k++){
    for(int j=0;j<3;j++){
        C_H1_W[k][j]=Randomize();
        C_H2_W[k][j]= Randomize();
        C_H3_W[k][j]= Randomize();
    }
}




}
  int size= Expected_value.size();
double Output_Store[10];


void Run(){
 

        double Full_H1;
        double Full_H2;
        double Full_H3;

        int b;

//main loop
int u=0;
double all_Inputs[2][6];
    for(int k=0;k<1;k++){
        for(int j=0;j<6;j++){
            all_Inputs[k][j]= Input[j];
        }
    }
    for(int k=1;k<2;k++){
        for(int j=0;j<6;j++){
            all_Inputs[k][j]= next_Input[j];
        }
    }

int size;
    if(Input.size()>next_Input.size()){
        size=Input.size();
    }else{
        size= next_Input.size();
    }

for(int x=0;x<size;x++){
            for(int n=0;n<10000;n++){


          int   b=Expected_value[u];
                if(u>Expected_value.size()){
                  u=0;
                    b=0;
                }




        double Inputs[2]= {all_Inputs[0][x],all_Inputs[1][x]};

    if(n==0){

        double activation;
        double activation_2;
        double activation_3;
        for(int k=0;k<2;k++ ){
        activation= H1_Biases[0];
        activation_2= H2_Biases[0];
       activation_3= H3_Biases[0];

        activation+= _H1_W[k]* Inputs[k];
        activation_2+= _H2_W[k]* Inputs[k];
        activation_3+= _H3_W[k]* Inputs[k];    

        }

        H1_Neuron[0]= Sigmoid(activation);
        H2_Neuron[0]= Sigmoid(activation_2);
        H3_Neuron[0]= Sigmoid(activation_3);

        Full_H1= H1_Neuron[0];
        Full_H2= H2_Neuron[0];
        Full_H3=  H3_Neuron[0];


    }

    else{

    //forward propagation
    double activation;
    double activation_2;
    double activation_3;
    for(int k=0;k<2;k++ ){
         activation= H1_Biases[0];
        activation_2= H2_Biases[0];
         activation_3= H3_Biases[0];

        activation+= _H1_W[k]* Inputs[k];
        activation_2+= _H2_W[k]* Inputs[k];
        activation_3+= _H3_W[k]* Inputs[k];    
    }
        //making the variables for the transaction between the previous context layer and to the current hidden layer
        
        double transaction;
        double transaction_2;
        double transaction_3;

        for(int k=0;k<1;k++){
            for(int j=0;j<3;j++){
               transaction+= C_H1_W[k][j]* C_H_N[j];
               transaction_2+= C_H2_W[k][j]* C_H_N[j];
               transaction_3+= C_H3_W[k][j]* C_H_N[j];
            }
        }

        double Activated_Neuron_H1;
        double Activated_Neuron_H2;
        double Activated_Neuron_H3;




        H1_Neuron[0]= Sigmoid(activation);
        Activated_Neuron_H1= Sigmoid(transaction);

        H2_Neuron[0]= Sigmoid(activation_2);
        Activated_Neuron_H2= Sigmoid(transaction_2);

        H3_Neuron[0]= Sigmoid(activation_3);
        Activated_Neuron_H3= Sigmoid(transaction_3);


        Full_H1= H1_Neuron[0]+Activated_Neuron_H1;
        Full_H2= H2_Neuron[0]+ Activated_Neuron_H2;
        Full_H3=  H3_Neuron[0]+ Activated_Neuron_H3;

    } 


               //create a new array to only store the previous context neurons 
            C_H_N[0]=Full_H1;
            C_H_N[1]=Full_H2;
            C_H_N[2]=Full_H3;


            


            //continuing the forward propagation to the output layer
            double Full_Arr[3]={Full_H1,Full_H2,Full_H3};
            
            double Output_activation= O1_Biases[0];
            for(int j=0;j<3;j++){
                  Output_activation+= Full_Arr[j];  
            }

            O1_Neuron[0]= Sigmoid(Output_activation);

        std::cout<<O1_Neuron[0]<<"\n";
   
    
            //backward propagation

            double Error= loss(Expected_value[b],O1_Neuron[0]);
    

        double Output_Delta= Error * ((dSigmoid(O1_Neuron[0])));

     //calculating the errors for the hidden neurons and the context layer

    double H1_Error,C_H1_Error;
    double H2_Error,C_H2_Error;
    double H3_Error,C_H3_Error;


    for(int j=0;j<3;j++){
        H1_Error+= Output_Delta* _O1_W[j];
        H2_Error+= Output_Delta* _O1_W[j];
        H3_Error+= Output_Delta* _O1_W[j];

    }



    //add or multiply the future biases to the current deltas if needed

    double H1_Current_Delta,H2_Current_Delta,H3_Current_Delta;

    H1_Current_Delta= H1_Error* ((dSigmoid(H1_Neuron[0])));
    H2_Current_Delta= H2_Error* ((dSigmoid(H2_Neuron[0])));
    H3_Current_Delta= H3_Error* ((dSigmoid(H3_Neuron[0])));

    //use this delta for calucate the biases for the future hidden layer aka the context layers
 

    Future_H1_Bias= H1_Current_Delta* lr;
    Future_H2_Bias= H2_Current_Delta* lr;
    Future_H3_Bias= H3_Current_Delta* lr;

    //creating the new finalized delta
     double _new_Current_H1_Delta;
    double _new_Current_H2_Delta;
    double _new_Current_H3_Delta;

    double new_error_h1;
    double new_error_h2;
    double new_error_h3;

        for(int j=0;j<3;j++){
            new_error_h1+= C_H1_W[2][j]* Future_H1_Bias;
            new_error_h2+= C_H2_W[2][j]* Future_H2_Bias;
            new_error_h3+= C_H3_W[2][j]* Future_H3_Bias;

        }



_new_Current_H1_Delta= new_error_h1+ H1_Current_Delta;
_new_Current_H2_Delta= new_error_h2+ H2_Current_Delta;
_new_Current_H3_Delta= new_error_h3+ H3_Current_Delta;


double F_H_N[3]={H1_Neuron[0],H2_Neuron[0],H3_Neuron[0]};


        //output weights and biases change go here
        O1_Biases[0]+= Output_Delta* lr;
        
        for(int k=0;k<3;k++){
            _O1_W[k]+= Output_Delta* F_H_N[k]* lr;
        }




    //use this delta for changing the internal biases and weights of the current hidden layer
  
    H1_Biases[0]+= _new_Current_H1_Delta* lr;
    H2_Biases[0]+= _new_Current_H2_Delta* lr;
    H3_Biases[0]+= _new_Current_H3_Delta* lr;


        for(int j=0;j<2;j++){
            _H1_W[j]+= _new_Current_H1_Delta* Input[j]* lr;
            _H2_W[j]+= _new_Current_H2_Delta* Input[j]*lr;
            _H3_W[j]+= _new_Current_H3_Delta* Input[j]* lr;
 
        }


    }
   
        
  
   Output_Store[u]= O1_Neuron[0];
u++;
}







}



void display(){
//std::cout<<Expected_value.size()<<"\n";
    for(int k=0;k<6;k++){
        int x= round(Output_Store[k]);
std::cout<<"\n";
std::cout<<"\n";
       std::cout<<x<<"  ";
       std::cout<<Expected_value[k]<<"  ";
       
    }

 


}


};