#include "MemoryArray.h"

void MemoryArray::init_mem_arr()
{
    for (int i = 0; i < MEMORYSIZE; i++) {
        for (int x = 0; x < GRIDRADIUS; x++) {
            for (int y = 0; y < GRIDRADIUS; y++) {
                memory_array[i][x][y] = 0;
            }
        }
    }
}

MemoryArray::MemoryArray() : mem_count(0), first_not_found(false)
{
    init_mem_arr();
}

bool MemoryArray::retrieve_last_enemy_memory(int arr[GRIDRADIUS][GRIDRADIUS])
{
    for (int i = 0; i < mem_count; i++) {
        bool mario_found = false;
        bool enemy_found = false;
        for (int x = 0; x < GRIDRADIUS; x++) {
            for (int y = 0; y < GRIDRADIUS; y++) {
                if (memory_array[i][x][y] == MARIO) {
                    mario_found = true;
                }
                if (memory_array[i][x][y] == ENEMY) {
                    enemy_found = true;
                }
            }
        }
        if (mario_found && enemy_found) {
            //cpy in arr
            for (int x = 0; x < GRIDRADIUS; x++) {
                for (int y = 0; y < GRIDRADIUS; y++) {
                    arr[x][y] = memory_array[i][x][y];
                }
            }
            return true;
        }
    }
	return false;
}

int MemoryArray::push_in_memory_array(int arr[GRIDRADIUS][GRIDRADIUS])
{
    if (mem_count < MEMORYSIZE) { //1: memcount = 1; for(0) => put arr in mem[0]; //2: memcount=2; for(0 bis 2-1 = 1 mal)
        mem_count++;
    }
    //schiebe alle nach vorne
    for (int i = mem_count - 1; i > 0; i--) {
        for (int x = 0; x < GRIDRADIUS; x++) {
            for (int y = 0; y < GRIDRADIUS; y++) {
                memory_array[i][x][y] = memory_array[i - 1][x][y];
            }
        }
    }
    //put in first spot
    for (int x = 0; x < GRIDRADIUS; x++) {
        for (int y = 0; y < GRIDRADIUS; y++) {
            memory_array[0][x][y] = arr[x][y];
        }
    }
	return 0;
}

bool MemoryArray::return_first_not_found()
{
    return first_not_found;
}

void MemoryArray::set_first_not_found(bool state)
{
    first_not_found = state;
}
