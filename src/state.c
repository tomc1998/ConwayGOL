#include <stdlib.h>
#include <string.h>
#include "state.h"

// Gets the number of alive cells adjacent to the one on the board at
// the given index
int getNumAdjCells(State* state, int index) {
  // Check if at borders of board
  // Booleans to specify which sides of the cell are valid to check
  int checkTop = 0, checkLeft = 0, checkBottom = 0, checkRight = 0;
  // Assign these check* booleans
  if (index % state->boardWidth != 0) {checkLeft = 1;}
  if (index % state->boardWidth != state->boardWidth - 1) {checkRight = 1;}
  if (index >= state->boardWidth) {checkTop = 1;}
  if (index < state->boardWidth*(state->boardHeight-1)) {checkBottom = 1;}

  // Now check adjacent cells
  int numCells = 0;
  if (checkLeft) { // Check left 3 cells
    if (state->board[index-1] == 1) {++numCells;}
    if (checkTop) {
      if(state->board[index-state->boardWidth-1] == 1) {++numCells;}
    }
    if (checkBottom) {
      if(state->board[index+state->boardWidth-1] == 1) {++numCells;}
    }
  }
  if (checkRight) { // Check right 3 cells
    if (state->board[index+1] == 1) {++numCells;}
    if (checkTop) {
      if(state->board[index-state->boardWidth+1] == 1) {++numCells;}
    }
    if (checkBottom) {
      if(state->board[index+state->boardWidth+1] == 1) {++numCells;}
    }
  }
  if (checkTop) { // Check mid top cell
    if (state->board[index-state->boardWidth] == 1) {++numCells;}
  }
  if (checkBottom) { // Check mid bottom cell
    if (state->board[index+state->boardWidth] == 1) {++numCells;}
  }
  return numCells;
}

void initState(State* state, int screenWidth, int screenHeight) {
  state->SCREEN_WIDTH = screenWidth;
  state->SCREEN_HEIGHT = screenHeight;
  state->endflag = 0;
  state->board = 0;
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
  state->cellSize = 4;
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
