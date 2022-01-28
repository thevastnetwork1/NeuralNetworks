#include <iostream>
#include <math.h>
#include <cstdlib>


class Neural_Network {

public:
Neural_Network(double points[2]){

    set_inputs(points);
}


public:

void set_inputs(double arr[2]){
    for(int i=0;i<2;i++){
        Inputs[i]=arr[i];
    }
}

double Inputs[2];

//RBF neurons
double H1_Neuron;
double H2_Neuron;

//weights

double Output_W_1[2];
double Output_W_2[2];

//outputs
double Output_1;
double Output_2;

//prototype arrays
double H1_Proto[2]={0.0,13.2};
double H2_Proto[2]={-3.0233,-3.21};
double Beta=0.1;



//utility functions
double dSigmoid(double x){return x*(1-x);}

double loss(double Ideal, double Actual){return Ideal-Actual;}


double Norm(double inputs,double proto[2]){

           double sum;
   for(int j=0;j<2;j++){
   
       sum+= inputs;
       sum+=proto[j];

   }
   return sqrt(sum);

}
double Randomize(){return ((double)rand())/((double)RAND_MAX);}


double Mean(double arr[3]){
   double mean;

      
            for(int k=0;k<3;k++){
          mean+=arr[k];
          if(k==2){
              mean= mean/3;
          }
            }
        
   
    return mean;
}


double Guassian_Bell(double x,double y[2]){
double z[3];
   
            for(int k=1;k<3;k++){
                z[0]+=x;
                z[k]+=y[k];
            }
     

double mean= Mean(z);
double exponential_value;
double Val;

  
                for(int k=0;k<3;k++){
                Val+= z[k]-mean;
                if(k==2){
                   exponential_value= Val= pow(Val,2);
                    
                }
          
            }

//double Output= (1/(std_Deviation(x)*sqrt(2*3.14))*exp(-1/2*exponential_value));
double Output= exp(-Beta*exponential_value);
    return Output;
}


public:

void setUP(Neural_Network object){
//setting up the output layer weights
for(int j=0;j<2;j++){
    Output_W_1[j]= Randomize();
    Output_W_2[j]= Randomize();

}
}



void Run(Neural_Network object){

for(int n=0;n<1000;n++){

    //forward propagate
    double InputsArr1[2];
    double InputsArr2[2];
    for(int j=0;j<2;j++){
        InputsArr1[j]= Inputs[j];
        InputsArr2[j]= Inputs[j];

    }

        double H1_Store[2];
        double H2_Store[2];
double me1= InputsArr1[0];
double me2= InputsArr1[1];
double me3= InputsArr2[0];
double me4= InputsArr2[1];


    H1_Store[0]= Norm(me1,object.H1_Proto);
    H1_Store[1]= Norm(me2,object.H1_Proto);
    H2_Store[0]= Norm(me3,object.H2_Proto);
    H2_Store[1]= Norm(me4,object.H2_Proto);

    double H11;
    double H12;
       H11= H1_Store[0];
       H12= H1_Store[1];
       double H21= H2_Store[0];
       double H22= H2_Store[1];

        object.H1_Neuron+= Guassian_Bell(H11,object.H1_Proto);
        object.H1_Neuron+= Guassian_Bell(H12,object.H1_Proto);
        object.H2_Neuron+= Guassian_Bell(H21,object.H2_Proto);
        object.H2_Neuron+= Guassian_Bell(H22,object.H2_Proto); 



        double H_layers[2]={object.H1_Neuron,object.H2_Neuron};

        //getting to the outputs
        for(int j=0;j<2;j++){
            object.Output_1+= H_layers[j]*object.Output_W_1[j];
        }

        for(int j=0;j<2;j++){
            object.Output_2+= H_layers[j]* object.Output_W_2[j];
        }


        //changing the weights to suite the value
       /* if(object.Output_1<object.Output_2){
        for(int j=0;j<2;j++){
            object.Output_W_1[j]+= object.Output_1* H_layers[j];
        } 
        for(int j=0;j<2;j++){
            object.Output_W_2[j]-= object.Output_2 *H_layers[j];
        }

        }
        else if(object.Output_2<object.Output_1){
            for(int j=0;j<2;j++){
                object.Output_W_2[j]+= object.Output_2* H_layers[j];
            }
            for(int j=0;j<2;j++){
                object.Output_W_1[j]-= object.Output_1* H_layers[j];
            }
        }*/
  


        std::cout<<"POs:"<<object.Output_W_1[0]<<"\n";
        std::cout<<"NEG:"<<object.Output_W_2[0]<<"\n";


            if(object.Output_1>object.Output_2){
                std::cout<<"This is positive\n";
            }else {
                std::cout<<"This is negativve\n";
            }


}

}

};





