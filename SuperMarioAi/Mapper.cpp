#include "Mapper.h"
#include "MarioFinder.h"
#include "FinderThread.h"
#include "Globals.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <cmath>
/*    int ErgebnisArray[GRIDRADIUS][GRIDRADIUS];
    int MappingArray[MAPPINGDATA];
    int last_mario_pos_x;
    int last_mario_pos_y;
public:
    Mapper();
    bool Map_Mario();
    int Create_Array_Around_Mario();
    int Map_Blocks_Threaded();
    int Map_Items_Threaded();
    int Map_Enemys_Threaded();
    bool check_if_free(int grid_x, int grid_y);
    bool write_to_output_array(int grid_x, int grid_y, int DISTR_IMAGES);
    ~Mapper();*/

std::mutex mutex;

bool Mapper::write_to_output_array(int grid_x, int grid_y, int DISTR_IMAGES){
    mutex.lock();
    ErgebnisArray[grid_x-MappingArray[X_Start]][grid_y-MappingArray[Y_Start]] = DISTR_IMAGES;
    mutex.unlock();
    return false;
}

bool Mapper::check_if_free(int grid_x,int grid_y){
    return (ErgebnisArray[grid_x-MappingArray[X_Start]][grid_y-MappingArray[Y_Start]] == 0);
}

Mapper::Mapper(): last_mario_pos_x(0), last_mario_pos_y(0){
    //ErgebnisArray.resize(GRIDRADIUS, std::vector<int>(GRIDRADIUS, 0));
}

Mapper::~Mapper()=default;

int Mapper::print_erg_radius(){
    for(int y = 0; y<GRIDRADIUS;y++){
        printf("\n");
        for(int x = 0; x<GRIDRADIUS;x++){
            std::cout<<ErgebnisArray[x][y]<< " ";

        }
    }
    printf("\n\n");
    return 0;
}

int Mapper::return_erg_array(int arr[GRIDRADIUS][GRIDRADIUS]){
    for(int x = 0; x<GRIDRADIUS;x++){
        for(int y = 0; y<GRIDRADIUS;y++){
            arr[x][y] = ErgebnisArray[x][y];
        }
    }
    return 0;
}

bool Mapper::Map_Mario(){
    int start_x;
    int start_y;
    int end_x;
    int end_y;

    int height = distr.grab_resized_img().return_height();
    int width = distr.grab_resized_img().return_width();

    //Last Mario. if he was found already, search near his last position
    if(last_mario_pos_x == 0 && last_mario_pos_y == 0){
        start_x = 0;
        start_y = 0;
        end_x = width;
        end_y = height;
    }
    else{
        start_x = (last_mario_pos_x - TILESIZE*GRIDRADIUS/2);
        start_y = (last_mario_pos_y - TILESIZE*GRIDRADIUS/2);
        end_x = (last_mario_pos_x + TILESIZE*GRIDRADIUS/2);
        end_y = (last_mario_pos_y + TILESIZE*GRIDRADIUS/2);
    }


    //Randüberprüfungen
    if(start_x<0)start_x=0;
    if(start_y<0)start_y=0;
    if(end_x>width-TILESIZE)end_x = width - TILESIZE;
    if(end_y>height - TILESIZE)end_y = height - TILESIZE;
    //printf("%4d,%4d",height,width);
    bool bools[MARIOFINDERTHREADS];
    std::thread threads[MARIOFINDERTHREADS];
    MarioFinder finders[MARIOFINDERTHREADS];
    for(int i = 0; i < MARIOFINDERTHREADS;i++){
        if (start_y < 0)start_y = 0;
        bools[i]=false;
        threads[i] = std::thread(&MarioFinder::search_for_Mario_threaded,
                    &finders[i],start_x,end_x,start_y,(end_y/MARIOFINDERTHREADS)*(i+1),&bools[i]);

                    //printf(" %d-%d,",start_y,(end_y/MARIOFINDERTHREADS)*(i+1));

        start_y = end_y/MARIOFINDERTHREADS*(i+1)-tilesize_mario_big_y;
    }
    for(int i = 0; i<MARIOFINDERTHREADS;i++){
        threads[i].join();
    }
    for(int i = 0; i<MARIOFINDERTHREADS;i++){
        if(bools[i]){
            //std::cout << "MARIO FOUND ON X:"<<finders[i].return_x_pos()<<" AND Y:"
            //            <<finders[i].return_y_pos()<<"\n";
            last_mario_pos_x = finders[i].return_x_pos();
            last_mario_pos_y = finders[i].return_y_pos();
            Create_Array_Around_Mario(finders[i].return_is_big());
            return true;
        }
    }
    //-------------------------------------------------------------------------------------
    //such im ganzen foto nochmal, vielleicht ist er gestorben und seine near position ist weg
    start_x = 0;
    start_y = 0;
    end_x = width - TILESIZE;
    end_y = height - TILESIZE;
    for(int i = 0; i < MARIOFINDERTHREADS;i++){
        bools[i]=false;
        if (start_y < 0)start_y = 0;
        threads[i] = std::thread(&MarioFinder::search_for_Mario_threaded,
                    &finders[i],start_x,end_x,start_y,(end_y/MARIOFINDERTHREADS)*(i+1),&bools[i]);

                    //printf(" %d-%d,",start_y,(end_y/MARIOFINDERTHREADS)*(i+1));

        start_y = end_y/MARIOFINDERTHREADS*(i+1)-tilesize_mario_big_y;
    }
    for(int i = 0; i<MARIOFINDERTHREADS;i++){
        threads[i].join();
    }
    for(int i = 0; i<MARIOFINDERTHREADS;i++){
        if(bools[i]){
            //std::cout << "MARIO FOUND ON X:"<<finders[i].return_x_pos()<<" AND Y:"
            //            <<finders[i].return_y_pos()<<"\n";
            last_mario_pos_x = finders[i].return_x_pos();
            last_mario_pos_y = finders[i].return_y_pos();
            Create_Array_Around_Mario(finders[i].return_is_big());
            return true;
        }
    }

    return false;
}




int Mapper::Create_Array_Around_Mario(bool bigflag){
    for(int x = 0; x < GRIDRADIUS; x++){
        for(int y = 0; y < GRIDRADIUS; y++){
            ErgebnisArray[x][y]=0;
        }
    }
    //Marios new Grid Position:
    /* //MAKE A GRIDRADIUS * GRIDRADIUS ARRAY
        Checkt die ecken, damit das grid nicht im nichts beginnt.
        Rundet auf um zu bestimmen, im welchen grid mario sich befindet
    [ ][ ][ ][ ][ ]
    [ ][ ][ ][ ][ ]    
    [ ][ ][M][ ][ ]
    [ ][ ][ ][ ][ ]
    [ ][ ][ ][ ][ ]
    */ 
    int height = distr.grab_resized_img().return_height();
    int width = distr.grab_resized_img().return_width();
    int mariogrid_x = last_mario_pos_x/TILESIZE;
    int mariogrid_y = last_mario_pos_y/TILESIZE;
    double runden_x = round((float)last_mario_pos_x/TILESIZE - ((int)last_mario_pos_x/TILESIZE));
    double runden_y = round((float)last_mario_pos_y/TILESIZE - ((int)last_mario_pos_y/TILESIZE));

    mariogrid_x+=runden_x;
    mariogrid_y+=runden_y;
    //mariogrid_y = 11;
    /*
    int array_x = GRIDRADIUS/2;
    int array_y = GRIDRADIUS/2;
    if(mariogrid_x<array_x){
       array_x=mariogrid_x;
    }
    if(mariogrid_y<array_y){
       array_y=mariogrid_y;
    }
    if(mariogrid_y > (height/TILESIZE)-(GRIDRADIUS/2)-1){
        array_y=(height/TILESIZE) -(GRIDRADIUS/2) - mariogrid_y + GRIDRADIUS/2 + array_y-1;
    }
    //printf("%d,,,,",array_y);
    if(mariogrid_x>(width/TILESIZE)-(GRIDRADIUS/2)-1){
        array_x=(width/TILESIZE)-(GRIDRADIUS/2) - mariogrid_x + GRIDRADIUS/2 + array_x-1;
    }
    */
    //neue idee: mario nach unten links packen und nach oben um grid/2 dann nach rechts um grid/2
    int array_x = 0;

    int array_y = 0;

    if(mariogrid_x-(GRIDRADIUS/2) < 0){
        array_x = (GRIDRADIUS/2) + (mariogrid_x-(GRIDRADIUS/2));
    }
    else if(mariogrid_x+(GRIDRADIUS/2)+1 > width/TILESIZE){
        array_x = (GRIDRADIUS/2)+1 + (mariogrid_x+(GRIDRADIUS/2)-(width/TILESIZE));
    }
    else{
        array_x = GRIDRADIUS/2;
    }
    if(mariogrid_y-(GRIDRADIUS/2) < 0){
        array_y = (GRIDRADIUS/2) + (mariogrid_y-(GRIDRADIUS/2));
    }
    else if(mariogrid_y+(GRIDRADIUS/2)+1 > height/TILESIZE){
        array_y = (GRIDRADIUS/2) + (mariogrid_y+(GRIDRADIUS/2)+1-(height/TILESIZE));
    }
    else{
        array_y = GRIDRADIUS/2;
    }

    //printf("%d %d\n%d %d\n ",mariogrid_x,mariogrid_y,array_x,array_y);
    ErgebnisArray[array_x][array_y]=MARIO;

    if(bigflag){
        if(array_y<GRIDRADIUS-1){
            ErgebnisArray[array_x][array_y+1]=MARIO;
        }
    }
    //now fill in the x pos and y pos of the first grid [0][0]:
    //0 0 :
    MappingArray[X_Start] = mariogrid_x - array_x; 
    MappingArray[Y_Start] = mariogrid_y - array_y; 
    MappingArray[X_End] = MappingArray[X_Start] + GRIDRADIUS-1;
    MappingArray[Y_End] = MappingArray[Y_Start] + GRIDRADIUS-1;
    //std::cout<<"MARIO POS IN REAL MAP IN GRIDS: (X)(Y):"<<mariogrid_x<<" " 
    //    << mariogrid_y<<" \n";
    //std::cout<<"MARIO POS IN ARRAY: (X)(Y):"<<array_x<<" " << array_y<<" \n";
    //std::cout<<"ERG ARRAY ON REAL MAP: (X)(Y) bis (XEND)(YEND):"<<
    //    MappingArray[X_Start]<<" " << MappingArray[Y_Start]<<" " 
    //    <<MappingArray[X_End]<<" " <<MappingArray[Y_End]<<" \n";

    //print_erg_radius();
    return 0;
}

int Mapper::Map_Blocks_Threaded(){
    int start_x=MappingArray[X_Start];
    int start_y=MappingArray[Y_Start];
    int end_y=MappingArray[Y_End];
    int end_x=MappingArray[X_End];

    std::thread threads[FINDERTHREADS];
    std::vector<FinderThread> blocks(FINDERTHREADS, FinderThread(BLOCK));
    for(int i = 0; i < FINDERTHREADS;i++){
        threads[i] = std::thread(&FinderThread::search,
                    &blocks[i],start_x,end_x,start_y,start_y,this);
        start_y+=1;
    }
    for(int i = 0; i<FINDERTHREADS;i++){
        threads[i].join();
    }
    return 0;
}

int Mapper::Map_Enemys_Threaded(){
    /*FinderThread enemys(ENEMY);
    enemys.search(MappingArray[X_Start],MappingArray[X_End],MappingArray[Y_Start],MappingArray[Y_End],this);*/
    int start_x=MappingArray[X_Start];
    int start_y=MappingArray[Y_Start];
    int end_y=MappingArray[Y_End];
    int end_x=MappingArray[X_End];

    std::thread threads[FINDERTHREADS];
    std::vector<FinderThread> enemys(FINDERTHREADS, FinderThread(ENEMY));
    for(int i = 0; i < FINDERTHREADS;i++){
        threads[i] = std::thread(&FinderThread::search,
                    &enemys[i],start_x,end_x,start_y,start_y,this);
        start_y+=1;
    }
    for(int i = 0; i<FINDERTHREADS;i++){
        threads[i].join();
    }
    return 0;
}

int Mapper::Map_Items_Threaded(){
    int start_x=MappingArray[X_Start];
    int start_y=MappingArray[Y_Start];
    int end_y=MappingArray[Y_End];
    int end_x=MappingArray[X_End];

    std::thread threads[FINDERTHREADS];
    std::vector<FinderThread> items(FINDERTHREADS, FinderThread(ITEM));
    for(int i = 0; i < FINDERTHREADS;i++){
        threads[i] = std::thread(&FinderThread::search,
                    &items[i],start_x,end_x,start_y,start_y,this);
        start_y+=1;
    }
    for(int i = 0; i<FINDERTHREADS;i++){
        threads[i].join();
    }
    return 0;
}