//--------------------------------------------------
// INCLUDES
//--------------------------------------------------
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//--------------------------------------------------
// DEFINES 
//--------------------------------------------------
#define MYBLACK (Color) {33,26,35,255}

const size_t width = 800;
const size_t height = 1000;
const size_t gWidth = width;    // width in which is drawn the grid
const size_t uHeight = 200;
const size_t gHeight= height - uHeight;  // width in which is drawn the grid
const size_t gSide = 100;   //number of cells per side
const size_t cSide = gWidth / gSide; //lenght of the cell side
const Vector2 gOrigin = {0, 0};
const Rectangle gArea = {gOrigin.x,gOrigin.y, gWidth, gHeight };

typedef enum State {ALIVE, DEAD, } State;
typedef enum Scene {TITLE, GAME, } Scene;

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
void InitGrid(Cell** grid, size_t gSide); 
void FreeGrid(Cell** grid, size_t gSide);
void DrawGridArea(Rectangle, size_t spacing);
void CameraMovement(Camera2D*);

//--------------------------------------------------
// ENTRY POINT
//--------------------------------------------------
int main(int argc, char* argv[argc+1]){

    Scene scene = GAME; 
    float zoom = 1.0f;
    Camera2D camera = {.zoom = zoom, .target = gOrigin
            //.target = Vector2Add(gOrigin, (Vector2){gWidth/2.0f, gHeight/2.0f})
            };
    size_t frameCounter = 0;
    size_t generations = 0;
    size_t population = 0;
    
    // Allocate memory for the grid
    Cell** grid = (Cell**)malloc(gSide * sizeof(Cell*));
    if (!grid) {
        perror("Failed to allocate memory for grid rows");
        return EXIT_FAILURE;
    }

    for(size_t i = 0; i < gSide; ++i){
        grid[i] = (Cell*)malloc(gSide * sizeof(Cell));
        if (!grid[i]) {
            perror("Failed to allocate memory for grid columns");
            // Free already allocated rows before exiting
            for (size_t j = 0; j < i; ++j) {
                free(grid[j]);
            }
            free(grid);
            return EXIT_FAILURE;
        }
    }

    InitGrid(grid,gSide);

    SetTargetFPS(60);
    InitWindow(width, height, "Gol");

    // Main loop 
    while (!WindowShouldClose())   
    {
        // Inputs
        CameraMovement(&camera);   

        // Draw
        BeginDrawing();
        ClearBackground(MYBLACK);
        
        BeginMode2D(camera);
        
        // Create the 2d Grid
        DrawGridArea(gArea,cSide);
        EndDrawing();
    }

    FreeGrid(grid,gSide);
    CloseWindow();
    return EXIT_SUCCESS;
}

void InitGrid(Cell** grid, size_t gSide){
    for(size_t i = 0; i < gSide; ++i){  // i = x -> Width
        for(size_t j = 0; j < gSide; ++j){  // j = y -> Height
            grid[i][j].x = i * cSide;
            grid[i][j].y = j * cSide;
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
            if (i < gSide - 1) grid[i][j].ex = &grid[i+1][j];
            if (j > 0) grid[i][j].nx = &grid[i][j-1];
            if (j < gSide - 1) grid[i][j].sx = &grid[i][j+1];
            if (i > 0 && j > 0) grid[i][j].nwx = &grid[i-1][j-1];
            if (i < gSide - 1 && j > 0) grid[i][j].nex = &grid[i+1][j-1];
            if (i > 0 && j < gSide - 1) grid[i][j].swx = &grid[i-1][j+1];
            if (i < gSide - 1 && j < gSide- 1) grid[i][j].sex = &grid[i+1][j+1];
        }
   }
}

void FreeGrid(Cell** grid, size_t gSide){
    for(size_t i = 0; i < gSide; ++i){ 
           free(grid[i]);
    }
    free(grid);
}

void DrawGridArea(Rectangle gArea, size_t spacing){
    size_t sX = (size_t)gArea.x;    // starting positions
    size_t sY = (size_t)gArea.y;
    size_t eX = (size_t)(gArea.x + gArea.width);   // ending positions
    size_t eY = (size_t)(gArea.y + gArea.height);
    
    for(size_t i = sX; i <= eX; i += spacing){
        if (i == sX || i == eX) DrawLine(i, sY, i, eY, RED);
        else DrawLine(i, sY, i, eY, GRAY);
    } 

    for(size_t i = sY; i <= eY; i+= spacing){
        if (i == sY || i == eY) DrawLine(sX, i, eX, i, RED);
        else DrawLine(sX, i, eX, i, GRAY);
    } 
}

void CameraMovement(Camera2D* camera){
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/ camera->zoom);
        camera->target = Vector2Add(camera->target, delta);
    }
}



