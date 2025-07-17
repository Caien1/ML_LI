#define FRCNN_IMPLEMENTATION
#include "frcnn.h"
#include<stdio.h>
#include<time.h>
typedef struct 
{
Mat a0;
Mat layer0;
Mat a1;
Mat layer1;
Mat a2;
} Xor;
float cost(Xor m)
{



}
float forward_xor(Xor m,float x, float y){
 // float x =1;
   MAT_AT(m.a0,0,0)=x;
   MAT_AT(m.a0,0,1)=y;
 
  
  mat_dot(m.a1,m.a0,m.layer0);
  mat_sigmoid(m.a0);

  mat_dot(m.a2,m.layer1,m.layer1);
  mat_sigmoid(m.a2);

  //mat_print(m.a2);
  float c = MAT_AT(m.a2,0,0);

 
return c;

}
int main()
{
srand(time(0));

  Xor m;
  m.a0 = mat_alloc(1,3);
  m.layer0 = mat_alloc(3,3);
  m.a1 = mat_alloc(1,3);
  m.layer1 = mat_alloc(3,1);
  m.a2 = mat_alloc(1,1);
  
  m.layer0 = mat_init(m.layer0,5,10);
  m.layer1 = mat_init(m.layer0,5,10);

  mat_sigmoid(m.layer0);
  mat_sigmoid(m.layer1);
  mat_homog(m.a1);
  mat_homog(m.a2);

for(size_t i=0;i<2;i++){
  for(size_t j=0;j<2;j++){
    printf("%zu ^ %zu  %f\n",i,j,forward_xor(m,i,j));
  }
}
 
  






  









    return 0;
}