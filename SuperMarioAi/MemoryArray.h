#ifndef memarr_h
#define memarr_h
#include "Globals.h"
class MemoryArray {
private:
    int memory_array[MEMORYSIZE][GRIDRADIUS][GRIDRADIUS];
    void init_mem_arr();
    int mem_count;
    bool first_not_found;
public:
    MemoryArray();
    bool retrieve_last_enemy_memory(int arr[GRIDRADIUS][GRIDRADIUS]);
    int push_in_memory_array(int arr[GRIDRADIUS][GRIDRADIUS]);
    bool return_first_not_found();
    void set_first_not_found(bool state);
};

#endif