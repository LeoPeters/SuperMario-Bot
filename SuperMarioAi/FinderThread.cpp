#include "FinderThread.h"
#include "GridScanner.h"
/*class FinderThread{
    private:
        ImageDistributor distr;
        PngImage &resized;
    public:
        FinderThread(PngImage &resized, int MODUS, int DISTR_IMAGEES);
        ~FinderThread();
        bool search(int gridpositions[MAPPINGDATA]); //xystart xyend
};
*/

void print_rgb_data_png_file(PngImage& inp) {
  printf("\n");
  int height = inp.return_height();
  int width = inp.return_width();
  const int wertsize = 10000;
  int werte[wertsize][3];
  for(int i = 0; i<wertsize;i++){
    for(int y = 0; y<3;y++){
      werte[i][y]=0;
    }
  }
  for(int y = 0; y <height ; y++) {
    png_bytep row = inp.row_pointers[y];
    for(int x = 0; x <width; x++) {
      png_bytep px = &(row[x * 4]);
      //printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
      // Do something awesome for each pixel here...
      for(int i = 0; i<wertsize;i++){
        if(werte[i][0] == px[0] && werte[i][1] == px[1] && werte[i][2] == px[2]){
          i=wertsize;
        }
        else if(werte[i][0] == 0 && werte[i][1] == 0 && werte[i][2] == 0){
          werte[i][0]=px[0];
          werte[i][1]=px[1];
          werte[i][2]=px[2];
          i=wertsize;
          }
     
        }
      }
  }
  //ausgabe:
  for(int i = 0; i<wertsize;i++){
        if(werte[i][0] == 0 && werte[i][1] == 0 && werte[i][2] == 0){
          i=wertsize;//break
        }
        else{
          printf("RGB(%3d, %3d, %3d)\n", werte[i][0], werte[i][1], werte[i][2]);
        }
    }
}


FinderThread::FinderThread(int TYP): resized(distr.grab_resized_img()) , gridsc(){
  this->typ = TYP;
}

FinderThread::~FinderThread(){

}

bool FinderThread::search(int xstart, int xend, int ystart, int yend, Mapper *mapper){
  bool am_i_done = false;
  int erg = 0;
  switch(typ){
    case ENEMY:
      while(true){
        PngImage& img = distr.grab_next_enemy_img(&am_i_done);
        if(am_i_done){break;}
        for(int x = xstart; x<= xend;x++){
          for(int y = ystart; y<=yend;y++){
            if(mapper->check_if_free(x,y)){
              if(gridsc.grid_matching_non_static(x,y,img,ENEMY_UNTERE_FLANKE,ENEMY_OBERE_FLANKE)){
                mapper->write_to_output_array(x, y, ENEMY);
              }
            }
          }
        }
      }
    break;
    case ITEM:
      while(true){
        PngImage& img = distr.grab_next_item_Non_Static_img(&am_i_done);
        if(am_i_done){break;}
        for(int x = xstart; x<= xend;x++){
          for(int y = ystart; y<=yend;y++){
            if(mapper->check_if_free(x-xstart,y-ystart)){
              if(gridsc.grid_matching_non_static(x,y,img,SHROOM_UNTERE_FLANKE,SHROOM_OBERE_FLANKE)){//TODO SHROOMS KALIBRIEREN
                mapper->write_to_output_array(x, y, ITEM);
              }
            }
          }
        }
      }
      am_i_done=false;
      while(true){
        PngImage& img = distr.grab_next_item_Static_img(&am_i_done);
        if(am_i_done){break;}
        for(int x = xstart; x<= xend;x++){
          for(int y = ystart; y<=yend;y++){
            if(mapper->check_if_free(x,y)){
              if(gridsc.grid_matching_static(x,y,img,FLOWER_UNTERE_FLANKE,FLOWER_OBERE_FLANKE)){//TODO FLOWER KALIBRIEREN
                mapper->write_to_output_array(x, y, ITEM);
              }
            }
          }
        }
      }
    break;
    case BLOCK:
      while(true){
        PngImage& img = distr.grab_next_block_img(&am_i_done);
        if(am_i_done)break;
        for(int x = xstart; x<= xend;x++){
          for(int y = ystart; y<= yend;y++){
            if(mapper->check_if_free(x,y)){
              if(gridsc.grid_matching_static(x,y,img,BLOCK_UNTERE_FLANKE,BLOCK_OBERE_FLANKE)){
                mapper->write_to_output_array(x, y, BLOCK);
              }
            }
          }
        }
      }
      am_i_done=false;
      while(true){
        PngImage& img = distr.grab_next_pipe_img(&am_i_done);
        if(am_i_done)break;
        for(int x = xstart; x<= xend;x++){
          for(int y = ystart; y<= yend;y++){
            if(mapper->check_if_free(x,y)){
              if(gridsc.grid_matching_static(x,y,img,PIPES_UNTERE_FLANKE,PIPES_OBERE_FLANKE)){
                mapper->write_to_output_array(x, y, BLOCK);
              }
            }
          }
        }
      }
    break;
    }
  return false;
}



//TODO: entfernen // Working code example from block grabbing for finder threads!
/*//test image distributor
    ImageDistributor imdist;
    bool am_i_done = false;
    int tmpcount=0;
    while(true){
      PngImage& rBlock = imdist.grab_next_block_img(&am_i_done);
      if(am_i_done){break;}
      std::cout << "block number: "<<tmpcount<<std::endl;
      print_different_rgbs_for_testing(rBlock.return_height(),rBlock.return_width(),rBlock.row_pointers);
      tmpcount++;
    }*/

/*
static int  print_different_rgbs_for_testing(int height, int width, png_bytep* row_pointers){
  int wertsize = 10000;
  int werte[wertsize][3];
  for(int i = 0; i<wertsize;i++){
    for(int y = 0; y<3;y++){
      werte[i][y]=0;
    }
  }
  for(int y = height-1; y >= 0; y--) {
    png_bytep row = row_pointers[y];
    for(int x = width-1; x >= 0; x--) {
      png_bytep px = &(row[x * 4]);
      //printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
      // Do something awesome for each pixel here...
      for(int i = 0; i<wertsize;i++){
        if(werte[i][0] == px[0] && werte[i][1] == px[1] && werte[i][2] == px[2]){
          i=wertsize;
        }
        else if(werte[i][0] == 0 && werte[i][1] == 0 && werte[i][2] == 0){
          werte[i][0]=px[0];
          werte[i][1]=px[1];
          werte[i][2]=px[2];
          i=wertsize;
          }
     
        }
      }
  }

  //ausgabe:
  for(int i = 0; i<wertsize;i++){
        if(werte[i][0] == 0 && werte[i][1] == 0 && werte[i][2] == 0){
          i=wertsize;//break
        }
        else{
          printf("RGB(%3d, %3d, %3d)\n", werte[i][0], werte[i][1], werte[i][2]);
        }
    }

}
*/


