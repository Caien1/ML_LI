


#define FRCNN_IMPLEMENTATION
#include "frcnn.h"
#include<stdio.h>
#include<time.h>
int test=4;
float* train;
typedef struct 
{
Mat a0;
Mat layer0;
Mat a1;
Mat layer1;
Mat a2;
} Xor;

float xor[] ={
  1,2,3,
  4,5,6,
  7,8,9,
  2,4,5,
};

Mat xor_gate = {.rows=4,.cols=3,.st=xor};
Xor xor_copy(Xor m){
  Xor temp;
  temp.a0=mat_copy(m.a0);
  temp.layer0=mat_copy(m.layer0);
  temp.a1=mat_copy(m.a1);
  temp.layer1=mat_copy(m.layer1);
  temp.a2 =mat_copy(m.a2);

  return temp;
}
float prop_xor(Xor m)
{
// mat_print(m.a0);
// mat_print(m.a1);
// mat_print(m.a2);
mat_dot(m.a1, m.a0,m.layer0);

mat_sigmoid(m.a0);
mat_dot(m.a2,m.a1,m.layer1);
mat_sigmoid(m.a2);
mat_sigmoid(m.a2);
return (m.a2.st[0]);

}
float cost(Xor m,Mat xor_gate)
{
    float result=0.0f;
    for(size_t i=0;i<test;i++){
    m.a0 = mat_sub_row(xor_gate,i,2);
    float real = xor_gate.st[i+xor_gate.cols-1];
    //mat_print(m.a0); 
    float d = real - prop_xor(m);
    result+= d*d; 
    }
return result/test;

}

float learn(Xor m, float esp, float rate){
  float save=0.0f;
 float c = cost(m,xor_gate);
  Xor temp=xor_copy(m);
  mat_print(m.layer0);

  for(size_t i = 0;i<temp.layer0.rows*temp.layer0.cols;i++)
 { 
  if((i+1)%temp.layer0.cols==0){ //hacks
    continue;
  }
  save=temp.layer0.st[i];
  

} 

printf("\n-------------------------\n");
mat_print(temp.layer1);
  for(size_t i = 0;i<temp.layer1.rows*temp.layer1.cols;i++)
 { 
 
   printf("%f ",temp.layer1.st[i]) ;
} 
}





int main()
{



srand(time(0));

  Xor m;
  m.a0 = mat_alloc(1,3);
  m.a0=mat_init(m.a0,0,1);
  m.layer0 = mat_alloc(3,3);
  m.a1 = mat_alloc(1,3);
  m.layer1 = mat_alloc(3,1);
  m.a2 = mat_alloc(1,1);
  
  m.layer0 = mat_init(m.layer0,0,1);
  m.layer1 = mat_init(m.layer1,0,1);

  mat_sigmoid(m.layer0);
  mat_sigmoid(m.layer1);
  mat_homog(m.a1);
  mat_homog(m.a2);
  //mat_print(m.layer1);
  learn(m);
   // printf("  %f\n ",cost(m,xor_gate));
// for(size_t i=0;i<2;i++){
//   for(size_t j=0;j<2;j++){

//   }f
}
 
  






  






