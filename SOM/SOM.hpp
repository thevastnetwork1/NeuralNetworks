#include <iostream>
#include <math.h>
#include <cstdlib>
#include <vector>

class NeuralNetwork {
public:
NeuralNetwork(std::vector<double> inputs){

    set_Input_Vector(inputs);

}

private:
void set_Input_Vector(std::vector<double> Inputs){

    for(int i=0;i<Inputs.size();i++){

        inputs.push_back(Inputs[i]);
    }

}

std::vector<double>inputs;
std::vector<double> One_plane;
double lr= 0.6;

//utility functions
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



double sigma(double arr[3]){
double deviation[3];

    for(int j=0;j<3;j++){
        deviation[j]=arr[j];
    }

double summation;
double mean= Mean(arr);
    for(int k=0;k<3;k++){
        summation+= deviation[k]- mean;
            if(k==2){
                summation= (pow(summation,2))/3;
            }
    }
double output= sqrt(summation);

return output;
}



//guassian bell
double Guassian_Bell(double winner, double neighbhor,double arr[3]){
double difference= winner- neighbhor;

difference= pow(difference,2);

double exponential_value;
double Sigma= 2*sigma(arr);



exponential_value= difference/Sigma;

return exp(-exponential_value);

}



double Norm(double pattern, double Node){
    double sum;
    sum+=pattern;
    sum+=Node;
    return sqrt(sum);
}




public:

void SetUp_Round(){

    for(int j=0;j<inputs.size();j++){
        inputs[j]= Randomize();
    }    

    for(int j=0;j<inputs.size();j++){
        One_plane.push_back(j);
    }
    


}

int size;
bool decrease=true;
double arr[3];
double outputs[3][3];
 std::vector <double> keeper;
std::vector <double> holder;
void Run(std::vector <int> set){

//main loop 
    for(int x=0;x<set.size();x++){
        int curr_Input=set[x];
        std::cout<<curr_Input<<"\n";
for(int n=0;n<10000;n++){

 
        //looping throug all node s and calculating the euclidean distance between the chosen node
        for(int j=0;j<inputs.size();j++){
            keeper.push_back(j);
           
        }

            for(int k=0;k<inputs.size();k++){
                    if(k==curr_Input){

                    }else{
                        keeper[k]=Norm(inputs[curr_Input],inputs[k]);
                    }
            }

            

        for(int j=0;j<inputs.size();j++){
            holder.push_back( keeper[j]);
        }

 

        for(int i=0;i<inputs.size();i++){
                for(int k=i+1;k<inputs.size();k++){
                    if(keeper[i]<keeper[k]){
                        int temp= k;
                        k=i;
                        i=temp;
                    }
                }
        
            }

                double smallest_dist;
                double Neighbhor_1;
                double Neighbhor_2;
                //moving to the calculations
                for(int j=0;j<inputs.size();j++){
             
                    if(holder[j]==keeper[0]){


                        smallest_dist= holder[j];//winner neuron
                            if(j==One_plane[j]){
                                //std::cout<<j<<"  "<<One_plane[j]<<"\n";
                                if(j==0){
                                    Neighbhor_1=j+1;        //winner neuron neighbors
                                    Neighbhor_2=j+2;
                                    
                                }else if(j==inputs.size()-1){
                                    Neighbhor_1= j-1;
                                    Neighbhor_2= j-2;
                                    
                                }else{
                                    
                                Neighbhor_1=j+1;
                                Neighbhor_2=j-1;
                               
                                }
                               
                            }
                    }
                }

                //implememnting the vector formulas
               
                arr[0]= smallest_dist;
                arr[1]=holder[Neighbhor_1];
                arr[2]= holder[Neighbhor_2];



                double Guassian_value[3];
                for(int j=0;j<3;j++){//0
                   Guassian_value[j]= Guassian_Bell(arr[0],arr[j],arr);
                }


                double change;
                for(int j=0;j<3;j++){
                    change= lr* Guassian_value[j] * (inputs[curr_Input]-arr[j]);
                      
                    arr[j]= arr[j]+change;
                   
                }

                //decrementing the learning rate every 100 epochs
                    if(lr==0.01){
                        //decrease=false;
                    }
                if(decrease&&n%100==0){
                    lr=lr-0.1;
                }



}

std::cout<<"\n";
for(int i=0;i<3;i++){
    outputs[x][i]= arr[i];
    std::cout<<outputs[x][i]<<"\n";
}
std::cout<<"\n";

    }





}




};