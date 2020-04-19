#ifndef Globals_h
#define Globals_h
#define TILESIZE 16
#define SKY 0
#define MARIO 1
#define BLOCK 2
#define ENEMY 3
#define ITEM 4
#define GRIDRADIUS 15 //5x5grid
#define MAPPINGDATA 4 //positions from to where
#define X_Start 0 //For Mappings Array 
#define Y_Start 1
#define X_End 2
#define Y_End 3
#define STATIC 0
#define NONSTATIC 1
#define ABWEICHUNG 30 // umso kleiner umso genauer: => Abweichung von pixelwerten //bei 50 wird mario richtig detektiert mit momentaner lib
#define tilesize_mario_big_x 9
#define tilesize_mario_big_y 8
#define tilesize_mario_x 7
#define tilesize_mario_y 5
#define GEWONNEN 1
#define TOT 2
//genauigkeitsformel. MATCH hängt intern noch von ABWEICHUNG ab
//zb: es kan 180 raus ==> ismatch(180) = 256/2 < 180-32 = 128<148
//#define IS_A_MATCH(x) ( ((TILESIZE*TILESIZE) / 2) < x-(TILESIZE*2) )
#define MAX_FEHLER 8 //bei 4 kann mario small nicht gefunden werden?
#define MAX_FEHLER_BLOECKE 10//34//wegen Pipe
//#define IS_A_MATCH(x) ( ((TILESIZE*TILESIZE) - MAX_FEHLER_BLOECKE <= x ))
#define IS_A_MATCH(x) ( ((TILESIZE*TILESIZE) - MAX_FEHLER_BLOECKE <= x ))
#define IS_A_MARIO_MATCH(x) ( (tilesize_mario_x*tilesize_mario_y)-MAX_FEHLER<=x )
#define IS_A_BIG_MARIO_MATCH(x) ((tilesize_mario_big_x*tilesize_mario_big_y)-MAX_FEHLER<=x  )
#define IS_A_PIPE_MATCH(x) ( 220 <= x >= 260)
#define IS_A_DEATHSCREEN(x) (x==15840)
//FOR GRIDS:
#define BLOCK_UNTERE_FLANKE ((TILESIZE*TILESIZE)-MAX_FEHLER_BLOECKE)
#define BLOCK_OBERE_FLANKE ((TILESIZE*TILESIZE)+MAX_FEHLER_BLOECKE)
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

//QLearning
#define NUMBER_OF_STATES 3 * ((GRIDRADIUS / 2) + 1) * GRIDRADIUS * GRIDRADIUS
#define ALPHA 0.4 //Learning rate
#define GAMMA 0.9 //Discount factor
#define EPSILON 0.1 //Propability of choosing a random action
#define REWARDSTEP -0.05

//Features
#define NUMBER_OF_FEATURES 4
#endif