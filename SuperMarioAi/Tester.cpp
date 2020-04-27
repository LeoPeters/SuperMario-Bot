#include "Tester.h"
#include "PngImage.h"
#include "ImageLibrary.h"
#include "Environment.h"
#include "Globals.h"
#include <zlib.h>
#include <chrono>
#include <ctime> 

Tester::Tester(){
    Environment fsm;
    int ergArray[GRIDRADIUS][GRIDRADIUS];
    for (int y = 0; y < GRIDRADIUS; y++) {
        for (int x = 0; x < GRIDRADIUS; x++) {
            ergArray[x][y] = 0;
        }
    }
    int status = 0;
    for(int i = 0; i < 1; i++){
    fsm.environment_interface("pictures/Input/input.png", ergArray, &status);
    }
    //PRINTING ARRAY
    if (status == TOT) {
        printf("MARIO IS DEAD\n");
    }
    else {
        printf("\n");
        for (int y = 0; y < GRIDRADIUS; y++) {
            for (int x = 0; x < GRIDRADIUS; x++) {
                printf("%d ", ergArray[x][y]);
            }
            printf("\n");
        }
        printf("\n");
    }
    if (status == GEWONNEN) {
        printf("MARIO WON!!\n");
    }
}

Tester::~Tester(){

}
 
