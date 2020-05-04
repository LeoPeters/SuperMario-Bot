#ifndef Globals_h
#define Globals_h
#define TILESIZE 16
#define SKY 0
#define MARIO 1
#define BLOCK 2
#define ENEMY 3
#define ITEM 4
#define WINNINGCONDS 5
#define GRIDRADIUS 15 //5x5grid
#define MAPPINGDATA 4 //positions from to where
#define X_Start 0 //For Mappings Array 
#define Y_Start 1
#define X_End 2
#define Y_End 3
#define STATIC 0
#define NONSTATIC 1
#define ABWEICHUNG 25 // umso kleiner umso genauer: => Abweichung von pixelwerten //bei 50 wird mario richtig detektiert mit momentaner lib
#define tilesize_mario_big_x 9
#define tilesize_mario_big_y 8
#define tilesize_mario_x 7
#define tilesize_mario_y 5
//STATUS RETURN:
#define NOT_FOUND 0
#define GEWONNEN 1
#define TOT 2
//memory size
#define MEMORYSIZE 5
//genauigkeitsformel. MATCH h�ngt intern noch von ABWEICHUNG ab
//zb: es kan 180 raus ==> ismatch(180) = 256/2 < 180-32 = 128<148
//#define IS_A_MATCH(x) ( ((TILESIZE*TILESIZE) / 2) < x-(TILESIZE*2) )
#define MAX_FEHLER_SMALL 8 //ab 16 gehts immer, aber big mario wird als small erkannt.
#define MAX_FEHLER 8
#define MAX_FEHLER_BLOECKE 25//34//wegen Pipe
//#define IS_A_MATCH(x) ( ((TILESIZE*TILESIZE) - MAX_FEHLER_BLOECKE <= x ))
#define IS_A_MATCH(x) ( ((TILESIZE*TILESIZE) - MAX_FEHLER_BLOECKE <= x ))
#define IS_A_MARIO_MATCH(x) (((tilesize_mario_x*tilesize_mario_y)>=x) && x>=28  )//( (tilesize_mario_x*tilesize_mario_y)-MAX_FEHLER_SMALL<=x )
#define IS_A_BIG_MARIO_MATCH(x) (45<=x && x<=tilesize_mario_big_x*tilesize_mario_big_y )//(52<=x && x<=tilesize_mario_big_x*tilesize_mario_big_y )//((tilesize_mario_big_x*tilesize_mario_big_y)-MAX_FEHLER<=x  )
#define IS_A_PIPE_MATCH(x) ( 220 <= x >= 260)
#define IS_A_DEATHSCREEN(x) (x==15840)
#define IS_A_FLAGPOLE(x) (50 <= x && x <= 54)
//FOR GRIDS:
#define BLOCK_UNTERE_FLANKE ((TILESIZE*TILESIZE)-MAX_FEHLER_BLOECKE)
#define BLOCK_OBERE_FLANKE ((TILESIZE*TILESIZE)+MAX_FEHLER_BLOECKE)
#define WINNINGCONDITIONS_UNTERE_FLANKE 50
#define WINNINGCONDITIONS_OBERE_FLANKE 60
#define PIPES_UNTERE_FLANKE 220
#define PIPES_OBERE_FLANKE 260
#define ENEMY_UNTERE_FLANKE 175
#define ENEMY_OBERE_FLANKE 195 
#define SHROOM_UNTERE_FLANKE 175
#define SHROOM_OBERE_FLANKE 190
#define FLOWER_UNTERE_FLANKE 155
#define FLOWER_OBERE_FLANKE 170
//THREADCOUNTS
#define MARIOFINDERTHREADS 25
#define FINDERTHREADS GRIDRADIUS //threads pro FINDER
//Paths
#define PNG_NAME "pictures/Input/input.png"
#define PNG_LNAME L"pictures/Input/input.png"
#define SUPER_MARIO_PATH L"..\\Mesen\\Mesen.exe"

//Features
#define NUMBER_OF_FEATURES 4
#define MAX_NUMBER_ENEMIES 4

//QLearning
#define NUMBER_OF_STATES (GRIDRADIUS - 1) * (GRIDRADIUS - 1) * (GRIDRADIUS - 1)+(GRIDRADIUS - 1)*2*(GRIDRADIUS - 1)
#define ALPHA 0.4 //Learning rate
#define GAMMA 0.9 //Discount factor
#define EPSILON 0.1 //Propability of choosing a random action
#define REWARDMOVERIGHT 0.08
#define REWARDSTEP -0.1
#define REWARDLOSE -10
#define REWARDWIN 100
#define INIT_STATE 0

#define MAX_KEYBOARD_INPUTS 10
#define Max_TABLE_SIZE 6000

#define SAVEFILE_PATH "saves/"
#endif