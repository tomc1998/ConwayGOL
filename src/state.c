#include <stdlib.h>
#include <string.h>
#include "state.h"

// Gets the number of alive cells adjacent to the one on the board at
// the given index
// Loops around at edge
int getNumAdjCells(State* state, int index) {
  // Free if at borders of board
  // Booleans to specify which sides of the cell are valid to free
  int freeTop = 0, freeLeft = 0, freeBottom = 0, freeRight = 0;
  // Assign these free* booleans
  if (index % state->boardWidth != 0)
    {freeLeft = 1;}
  if (index % state->boardWidth != state->boardWidth - 1)
    {freeRight = 1;}
  if (index >= state->boardWidth)
    {freeTop = 1;}
  if (index < state->boardWidth*(state->boardHeight-1))
    {freeBottom = 1;}

  int bw = state->boardWidth;
  int bh = state->boardHeight;
  // Now free adjacent cells
  int numCells = 0;
  if (freeLeft) { // Free left 3 cells
    if (state->board[index-1] == 1) {++numCells;}
    if (freeTop) {
      if (state->board[index-bw-1] == 1) {++numCells;}
    }
    else {
      if (state->board[(bh-1)*bw + index - 1] == 1) {++numCells;}
    }
    if (freeBottom) {
      if(state->board[index+bw-1] == 1) {++numCells;}
    }
    else {
      if (state->board[index%bw-1] == 1) {++numCells;}
    }
  }
  else { // Left 3 cells are against edge of board
    if (state->board[index+bw-1] == 1) {++numCells;}
    if (freeTop) {
      if (state->board[index-1] == 1) {++numCells;}
    }
    else {
      if (state->board[bh*bw-1] == 1) {++numCells;}
    }
    if (freeBottom) {
      if(state->board[index+bw+bw-1] == 1) {++numCells;}
    }
    else {
      if (state->board[bw-1] == 1) {++numCells;}
    }
  }

  if (freeRight) { // Free right 3 cells
    if (state->board[index+1] == 1) {++numCells;}
    if (freeTop) {
      if(state->board[index-bw+1] == 1) {++numCells;}
    }
    else {
      if (state->board[(bh-1)*bw + index + 1] == 1) {++numCells;}
    }
    if (freeBottom) {
      if(state->board[index+bw+1] == 1) {++numCells;}
    }
    else {
      if (state->board[index%bw+1] == 1) {++numCells;}
    }
  }
  else { // Left 3 cells are against edge of board
    if (state->board[index-bw+1] == 1) {++numCells;}
    if (freeTop) {
      if(state->board[index-bw-bw+1] == 1) {++numCells;}
    }
    else {
      if (state->board[bw*(bh-1)] == 1) {++numCells;}
    }
    if (freeBottom) {
      if(state->board[index+1] == 1) {++numCells;}
    }
    else {
      if (state->board[0] == 1) {++numCells;}
    }
  }

  
  if (freeTop) { // Free mid top cell
    if (state->board[index-bw] == 1) {++numCells;}
  }
  else {
    if (state->board[index + bw*(bh-1)] == 1) {++numCells;}
  }

  if (freeBottom) { // Free mid bottom cell
    if (state->board[index+bw] == 1) {++numCells;}
  }
  else {
    if (state->board[index%bw] == 1) {++numCells;}
  }

  return numCells;
}

void initState(State* state, int screenWidth, int screenHeight) {
  state->SCREEN_WIDTH = screenWidth;
  state->SCREEN_HEIGHT = screenHeight;
  state->endflag = 0;
  state->board = 0;
  state->boardScreenX = 0;
  state->boardScreenY = 0;
  state->running = 0;
}

void step(State* state) {
  int ii = 0;
  int numCells = state->boardWidth*state->boardHeight;

  // Initialise temporary memory to hold the state of the new board
  // An optimisation would be to make this always there, so as to
  // avoid the malloc every step, but meh
  int* tmpBoard =
    (int*) malloc(sizeof(int)*state->boardWidth*state->boardHeight);
  for (; ii < numCells; ii ++) {
    // Get num cells alive
    int aliveCells = getNumAdjCells(state, ii);
    if (state->board[ii] == 0) {
      if (aliveCells == 3) {
        tmpBoard[ii] = 1;
      }
      else {
        tmpBoard[ii] = 0;
      }
    }
    else {
      if (aliveCells < 2 || aliveCells > 3) {
        tmpBoard[ii] = 0;
      }
      else {
        tmpBoard[ii] = 1;
      }
    }
  }
  memcpy(state->board,
         tmpBoard,
         sizeof(int)*state->boardWidth*state->boardHeight);
}

void initBoard(State* state, int width, int height) {
  if (state->board != 0) {
    free(state->board);
    state->board = 0;
  }
  state->board = (int*) malloc(sizeof(int)*width*height);
  state->boardWidth = width;
  state->boardHeight = height;
  state->cellSize = 16;
  state->boardScreenX = 0;
  state->boardScreenY = 0;
  int ii = 0;
  for (; ii < width*height; ii ++) {
    state->board[ii] = 0;
  }
}

void freeBoard(State* state) {
  free(state->board);
  state->board = 0;
  state->boardWidth = 0;
  state->boardHeight = 0;
}
