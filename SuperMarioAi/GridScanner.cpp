#include "GridScanner.h"
/*
class GridScanner{
private:
    ImageDistributor distr;
    PngImage& resized;
public:
    GridScanner();
    ~GridScanner();
    int grid_matching_static(int grid_x, int grid_y, PngImage &matchingImg);
    int grid_matching_non_static(int grid_x, int grid_y, PngImage &matchingImg);
};*/

GridScanner::GridScanner(): resized(distr.grab_resized_img()), matcher(distr.grab_resized_img()){
    
}

GridScanner::~GridScanner()=default;

bool GridScanner::grid_matching_static(int grid_x, int grid_y, PngImage &matchingImg, int untere_flanke, int obere_flanke){
    int erg = matcher.match_tilesize_on_pixel(grid_x*TILESIZE,grid_y*TILESIZE,matchingImg);
    //printf("%2d,",erg);
    return (untere_flanke<=erg && erg <=obere_flanke);
}

bool GridScanner::grid_matching_non_static(int grid_x, int grid_y, PngImage &matchingImg, int untere_flanke, int obere_flanke){
    int highest = 0;
    int height = distr.grab_resized_img().return_height();
    int width = distr.grab_resized_img().return_width();
    int xstart = grid_x * TILESIZE - (TILESIZE/2);
    int xend = grid_x * TILESIZE + (TILESIZE/2) +1;
    int ystart = grid_y * TILESIZE - (TILESIZE/2) -1;
    int yend = grid_y*TILESIZE + (TILESIZE/2);
    //printf("xy %d %d xyend %d %d : bei max %d %d\n",xstart,ystart,xend,yend,width,height);
    //boundary checking
    if(xstart<0)xstart=0;
    if(ystart<0)ystart=0;
    if(xend>width-TILESIZE)xend=width-1-TILESIZE;
    if(yend>height-TILESIZE)yend=height-1-TILESIZE;
    int tmp = 0;
    for(int x = xstart; x <=xend;x++){
        for(int y = ystart;y<=yend;y++){
           // printf("x:%d,y=%d, " ,x,y);
            tmp = matcher.match_tilesize_on_pixel(x,y,matchingImg);
            if(tmp>highest){
                highest = tmp;
                //printf("%2d,",highest);
                if(untere_flanke<=highest && highest <=obere_flanke) {
                    //printf("HIT ON GRID: %d %d \n",grid_x,grid_y);
                    return true;}
            }
        }
    }
    return false;

} 