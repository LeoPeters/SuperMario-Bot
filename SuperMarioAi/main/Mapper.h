#ifndef mapper_h
#define mapper_h
//#include "../../ImageTools/header/PngImage.h"
#include "ImageDistributor.h"
#include "Globals.h"
class Mapper{
private:
    int ErgebnisArray[GRIDRADIUS][GRIDRADIUS];
    int MappingArray[MAPPINGDATA];
    int last_mario_pos_x;
    int last_mario_pos_y;
    ImageDistributor distr;
    int Create_Array_Around_Mario(bool bigflag);
public:
    Mapper();
    bool Map_Mario();
    int Map_Blocks_Threaded();
    int Map_Items_Threaded();
    int Map_Enemys_Threaded();
    bool check_if_free(int grid_x, int grid_y);
    bool write_to_output_array(int grid_x, int grid_y, int DISTR_IMAGES);
    int return_erg_array(int arr[GRIDRADIUS][GRIDRADIUS]);
    ~Mapper();
    int print_erg_radius();
};
#endif