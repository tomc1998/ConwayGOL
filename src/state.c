#include <stdlib.h>
#include "state.h"

void initState(State* state, int screenWidth, int screenHeight) {
  state->SCREEN_WIDTH = screenWidth;
  state->SCREEN_HEIGHT = screenHeight;
  state->endflag = 0;
  state->board = 0;
}

void step() {
}

void initBoard(State* state, int width, int height) {
  if (state->board != 0) {
    free(state->board);
    state->board = 0;
  }
  state->board = (int*) malloc(sizeof(int)*width*height);
  state->boardWidth = width;
  state->boardHeight = height;
}

void freeBoard(State* state) {
  free(state->board);
  state->board = 0;
  state->boardWidth = 0;
  state->boardHeight = 0;
}
