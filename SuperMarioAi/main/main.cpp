#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include "PngImage.h"
#include "ImageLibrary.h"
#include "Environment.h"
#include "Globals.h"
using namespace std;

#include <zlib.h>
#include <chrono>
#include <ctime>  


    

int main(int argc, char **argv){
  // auto start = std::chrono::system_clock::now();
   Environment fsm;
   int ergArray[GRIDRADIUS][GRIDRADIUS];
   for(int y = 0; y<GRIDRADIUS;y++){
      for(int x= 0; x<GRIDRADIUS;x++){
         ergArray[x][y] = 0;
      }
   }
   int status = 0;
   fsm.environment_interface("pictures/Input/input.png",ergArray,&status);
   //PRINTING ARRAY
   if(status == TOT){
      printf("MARIO IS DEAD\n");
   }
   else{
      printf("\n");
      for(int y = 0; y<GRIDRADIUS;y++){
         for(int x= 0; x<GRIDRADIUS;x++){
            printf("%d ",ergArray[x][y]);
            }
         printf("\n");
         }
      printf("\n");
   }

}

