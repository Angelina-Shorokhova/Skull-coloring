#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <strings.h>
#include "lodepng.h"
int i,j;

void preparation(unsigned char *od, int height_image, int width_image){
 for(i=0;i<height_image;i++){
  for(j=0;j<width_image;j++){
    
    if(od[width_image*i+j]<100)
      od[width_image*i+j]=0;
    if(od[width_image*i+j]>180)
      od[width_image*i+j]=255;
  }}
 return;
}

 char* loadPng(const char* filename, int* width, int* height) {
  
  unsigned char* image = NULL;

  int error = lodepng_decode32_file(&image, width, height, filename);
  if(error) 
  {
    printf("error %u: %s\n", error, lodepng_error_text(error));
  }
  
  return (image);
}



void writePng(const char* filename, const unsigned char* image, unsigned width, unsigned height) { 
  unsigned error; 
  unsigned char* png; 
  size_t pngsize; 
  LodePNGState state; 
 
  lodepng_state_init(&state); 
  /*optionally customize the state*/ 
 
  error = lodepng_encode(&png, &pngsize, image, width, height, &state); 
  if(!error) lodepng_save_file(png, pngsize, filename); 
 
  /*if there's an error, display it*/ 
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error)); 
 
  lodepng_state_cleanup(&state); 
  free(png); 
} 


void fGauss(unsigned char *od, unsigned char *cp, int height_image, int width_image){
for (i=2;i<height_image-1;i++){
  for(j=2;j<width_image-1;j++){
    cp[4*i*width_image+4*j]=0.03*od[4*(i-1)*width_image+4*(j-1)]+0.08*od[4*(i-1)*width_image+4*j]+0.03*od[4*(i-1)*width_image+4*(j+1)]+0.13*od[4*i*width_image+4*(j-1)]+0.16*od[4*i*width_image+4*j]+0.13*od[4*i*width_image+4*(j+1)]+0.05*od[4*(i+1)*width_image+4*(j-1)]+0.13*od[4*(i+1)*width_image+4*j]+0.16*od[4*(i+1)*width_image+4*(j+1)];
      cp[4*i*width_image+4*j+1]=0.03*od[4*(i-1)*width_image+4*(j-1)+1]+0.08*od[4*(i-1)*width_image+4*j+1]+0.03*od[4*(i-1)*width_image+4*(j+1)+1]+0.13*od[4*i*width_image+4*(j-1)+1]+0.16*od[4*i*width_image+4*j+1]+0.13*od[4*i*width_image+4*(j+1)+1]+0.05*od[4*(i+1)*width_image+4*(j-1)+1]+0.13*od[4*(i+1)*width_image+4*j+1]+0.16*od[4*(i+1)*width_image+4*(j+1)+1];
      cp[4*i*width_image+4*j+2]=0.03*od[4*(i-1)*width_image+4*(j-1)+2]+0.08*od[4*(i-1)*width_image+4*j+2]+0.03*od[4*(i-1)*width_image+4*(j+1)+2]+0.13*od[4*i*width_image+4*(j-1)+2]+0.16*od[4*i*width_image+4*j+2]+0.13*od[4*i*width_image+4*(j+1)+2]+0.05*od[4*(i+1)*width_image+4*(j-1)+2]+0.13*od[4*(i+1)*width_image+4*j+2]+0.16*od[4*(i+1)*width_image+4*(j+1)+2];
      cp[4*i*width_image+4*j+3]=0.03*od[4*(i-1)*width_image+4*(j-1)+3]+0.08*od[4*(i-1)*width_image+4*j+3]+0.03*od[4*(i-1)*width_image+4*(j+1)+3]+0.13*od[4*i*width_image+4*(j-1)+3]+0.16*od[4*i*width_image+4*j+3]+0.13*od[4*i*width_image+4*(j+1)+3]+0.05*od[4*(i+1)*width_image+4*(j-1)+3]+0.13*od[4*(i+1)*width_image+4*j+3]+0.16*od[4*(i+1)*width_image+4*(j+1)+3];
  }
  }
  return;
}


void colouring(unsigned char *cp, unsigned char *sec_ver, int height_image, int width_image, int n){
  for(i=1;i<width_image*height_image;i++) {
   
   if(cp[i]<=100){
    sec_ver[i*n]=250-0.1*cp[i];
    sec_ver[i*n+1]=100-cp[i];
    sec_ver[i*n+2]=35+0.5*cp[i];
    sec_ver[i*n+3]=150;
    }
     else  if((i<width_image*height_image*0.13)) {
    sec_ver[i*n]=0.1*cp[i-1];
    sec_ver[i*n+1]=0.3*cp[i];
    sec_ver[i*n+2]=0.4*cp[i];
      sec_ver[i*n+3]=150;
 }
  
  else if((cp[i]>100)&&(cp[i]<=180)&&(i<0.6*width_image*height_image)){
    sec_ver[i*n]=20-0.1*cp[i-1]+0.2*cp[i];
    sec_ver[i*n+1]=150-0.9*cp[i];
    sec_ver[i*n+2]=255-0.5*cp[i-1]+0.4*cp[i];
      sec_ver[i*n+3]=150;
  }//cиний

  else if((cp[i]>180)&&(cp[i]<=220)){
    sec_ver[i*n]=255-0.1*cp[i-1];
    sec_ver[i*n+1]=0.9*cp[i];
    sec_ver[i*n+2]=55+0.5*cp[i-1];
      sec_ver[i*n+3]=150;
  }
  else {
    if((i<0.6*width_image*height_image)){
    sec_ver[i*n]=55-0.1*cp[i-1];
    sec_ver[i*n+1]=180-0.1*cp[i];
    sec_ver[i*n+2]=255-cp[i-1];
     sec_ver[i*n+3]=150;}
      else if(i<0.8*width_image*height_image){ sec_ver[i*n]=190-0.9*cp[i];
    sec_ver[i*n+1]=150-0.9*cp[i];
    sec_ver[i*n+2]=105-0.4*cp[i];
      sec_ver[i*n+3]=150;}
      else if((i<0.91*width_image*height_image)&&(cp[i]>120)&&(cp[i]<=160)){ sec_ver[i*n]=190-0.9*cp[i-1];
    sec_ver[i*n+1]=150-0.9*cp[i-1];
    sec_ver[i*n+2]=105-0.4*cp[i-1];
      sec_ver[i*n+3]=150;}
   else if((i<0.92*width_image*height_image)&&(cp[i]>160)&&(cp[i]<=255)){ sec_ver[i*n]=19-0.09*cp[i-1];
    sec_ver[i*n+1]=50-0.1*cp[i-1];
    sec_ver[i*n+2]=15-0.04*cp[i-1];
      sec_ver[i*n+3]=150;}
   else if((i<0.94*width_image*height_image)&&(cp[i]>0)&&(cp[i]<=120)){ sec_ver[i*n]=0.3*cp[i-1];
    sec_ver[i*n+1]=0.2*cp[i-1];
    sec_ver[i*n+2]=0.1*cp[i-1];
      sec_ver[i*n+3]=150;}
    else { sec_ver[i*n]=20-0.2*cp[i];
    sec_ver[i*n+1]=50-0.9*cp[i];
    sec_ver[i*n+2]=255-0.4*cp[i];
      sec_ver[i*n+3]=150;}
  }
  

 }

  
 return;
}

int main()
{
 const char* inputPath ="image0.png";
  int width_image,height_image;
  int k=0, n=4;

  char *zversion=loadPng(inputPath, &width_image, &height_image);
  if(zversion==NULL){
     printf("ERROR: can't read file %s\n", inputPath);
     return 1;
}

unsigned char *firstversion=(unsigned
char*)malloc(height_image*width_image*sizeof(unsigned char));
unsigned char *copy_of_fv=(unsigned char*)malloc(height_image*width_image*sizeof(unsigned char));
unsigned char *second_version=(unsigned char*)malloc(height_image*width_image*n*sizeof(unsigned char));

  
for(i=0;i<height_image*width_image;i=i+1){
    firstversion[k]=0.299*zversion[4*i]+0.587*zversion[4*i+1]+0.114*zversion[4*i+2];
    k++;
}

  
preparation(firstversion,height_image,width_image);


fGauss(firstversion, copy_of_fv,height_image,width_image);

colouring(copy_of_fv, second_version, height_image, width_image, n); 

char *outputPath="image1.png";

writePng(outputPath,second_version, width_image, height_image);
printf("The end _(^-^)/ ");
return 0;
}