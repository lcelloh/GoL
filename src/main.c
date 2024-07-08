//--------------------------------------------------
// INCLUDES
//--------------------------------------------------
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "raylib.h"

//--------------------------------------------------
// DEFINES 
//--------------------------------------------------
#define MYBLACK (Color) {33,26,35,255}

const size_t width = 800;
const size_t height = 600;
const size_t gside = 1000;  //number of cells per side

typedef enum State {ALIVE, DEAD, BOUND} State;
typedef enum Scene{TITLE, GAME, } Scene;

typedef struct Cell{
    size_t x,y;
    struct Cell* nx;    //using compass directions for nearby cell
    struct Cell* sx;    // nx == north, nex = north-est, ecc 
    struct Cell* wx;   
    struct Cell* ex;   
    struct Cell* nwx;   
    struct Cell* nex;   
    struct Cell* swx;   
    struct Cell* sex;   
    State state;
} Cell;

//--------------------------------------------------
// PROTOTYPES 
//--------------------------------------------------
void InitGrid(Cell grid[gside][gside]);

//--------------------------------------------------
// ENTRY POINT
//--------------------------------------------------
int main(int argc, char* argv[argc+1]){

    Camera2D camera =  {0};
    camera.zoom = 1.0f;
    Scene scene = GAME; 

    size_t frameCounter = 0;
    size_t generations = 0;
    size_t population = 0;
    Cell grid[gside][gside];
    
    InitGrid(grid);

    SetTargetFPS(60);
    InitWindow(width, height, "Gol");
    // Main loop 
    while (!WindowShouldClose())   
    {
        BeginDrawing();

        ClearBackground(MYBLACK);

        EndDrawing();
    }
    CloseWindow();
    return EXIT_SUCCESS;
}

void InitGrid(Cell grid[gside][gside]){
    for(size_t i = 0; i <= gside; ++i){  // i = x -> Width
        for(size_t j = 0; j <= gside; ++j){  // j = y -> Height
            grid[i][j].x = i;
            grid[i][j].y = j;
            grid[i][j].state = DEAD;
            
            // Initialize neighbor pointers to NULL
            grid[i][j].nx = NULL;
            grid[i][j].sx = NULL;
            grid[i][j].wx = NULL;
            grid[i][j].ex = NULL;
            grid[i][j].nwx = NULL;
            grid[i][j].nex = NULL;
            grid[i][j].swx = NULL;
            grid[i][j].sex = NULL;
            
            // Set neighbor pointers
            if (i > 0) grid[i][j].wx = &grid[i-1][j];
            if (i < gside - 1) grid[i][j].ex = &grid[i+1][j];
            if (j > 0) grid[i][j].nx = &grid[i][j-1];
            if (j < gside - 1) grid[i][j].sx = &grid[i][j+1];
            if (i > 0 && j > 0) grid[i][j].nwx = &grid[i-1][j-1];
            if (i < gside - 1 && j > 0) grid[i][j].nex = &grid[i+1][j-1];
            if (i > 0 && j < gside - 1) grid[i][j].swx = &grid[i-1][j+1];
            if (i < gside - 1 && j < gside - 1) grid[i][j].sex = &grid[i+1][j+1];
        }
    }
}









