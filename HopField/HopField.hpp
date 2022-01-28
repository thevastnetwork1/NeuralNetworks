#include <iostream>
#include <math.h>
#include <cstdlib>
#include <vector>


class HopField_Network{
public:
HopField_Network(int inputs[3][6]){
    set_Training_sets(inputs);
}

private:
void set_Training_sets(int inputs[3][6]){
    for(int k=0;k<3;k++){
    for(int j=0;j<6;j++){
        Training_Patterns[k][j]= inputs[k][j];
    }
    }
}
//
int Training_Patterns[3][6];

//network configuration
double K_layers[3][6];



//the weight matrix
double W_matrix[5][6];

//utility functions

int choose_Neuron(){return round(rand()%6);}

double  Binary_Threshold(int val){

 for(int n=0;n<3;n++){
        for(int k=0;k<6;k++){
               for(int j=0;j<5;j++){
                if(K_layers[n][k]==val){

                }else{
                    val= K_layers[n][k]* W_matrix[j][k];
                }
        }
    }
 }
return val;

}




public:

void setUp(){

    for(int k=0;k<3;k++){
    for(int j=0;j<6;j++){
        K_layers[k][j]= Training_Patterns[k][j];
    
    }
    }


    //initializing the weights
    for(int n=0;n<3;n++){
        for(int k=0;k<6;k++){
                for(int j=0;j<5;j++){
            W_matrix[j][k]= K_layers[n][k]* K_layers[n][k+1];
         
        }
    }
    }

}

double KK_layers[6];
double*  Run(){


int prev;
for(int x=0;x<3;x++){
        for(int n=0;n<6;n++){
        //handling each neuron one at a time

        int index=  choose_Neuron();
        redo:
            if(index==prev){
                index= choose_Neuron();
                goto redo;
            }
     prev= index;

          

               
            

          //stabilize the network

            //multiplying ny the weights and the other neurons
            for(int j=0;j<1;j++){
                for(int k=0;k<6;k++){
                    if(k==index){

                    }else{//+=
                    K_layers[x][index]= W_matrix[j][k]* K_layers[x][k];
                  
                    }
                }
            }
                //activating the given neuron
                if(K_layers[x][index]>0){
                    K_layers[x][index]=1;
                }else{
                    K_layers[x][index]=-1;
                }

                //calculating the weights at each pattern
                for(int j=0;j<5;j++){
                    for(int k=0;k<6;k++){
                            if(K_layers[x][k]==1&&K_layers[x][k+1]==1){
                                W_matrix[j][k]=1;
                            }else if(K_layers[x][k]==-1||K_layers[x][k+1]==-1){
                                W_matrix[j][k]=-1;
                            }else{
                                W_matrix[j][k]=0;
                            }
                       // W_matrix[j][k]+= (K_layers[k]==1&&K_layers[k+1]==1)?1:-1;   

                    }
                }
			


        }

            //getting the finalized values
       /*     std::cout<<"\n";
            std::cout<<"Finalized Weights Matrix\n";
          
           for(int j=0;j<5;j++){
               for(int k=0;k<6;k++){
                   std::cout<<W_matrix[j][k]<<"\n";
               }
           }  

            std::cout<<"\n";
            std::cout<<"finalized neuron states"<<"\n";

            for(int j=0;j<6;j++){
                std::cout<<K_layers[j]<<"  ";
            }*/



       for(int j=0;j<3;j++){
            for(int k=0;k<6;k++){
                KK_layers[k]= K_layers[j][k];
            }
       }
}
     
 return  KK_layers;    
}



};
