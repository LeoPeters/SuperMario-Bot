#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include "../ImageTools/header/PngImage.h"
#include "../ImageTools/header/ImageLibrary.h"
using namespace std;

#include <zlib.h>


int main () {
   ImageLibrary test;
   printf("%d",test.return_item_img_count());
}

