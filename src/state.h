#ifndef STATE_H
#define STATE_H

typedef struct {
  int SCREEN_WIDTH, SCREEN_HEIGHT;
  int* board;
  int boardWidth, boardHeight;
  int endflag;
} State;

// Initialises some state
void initState(State* state, int screenWidth, int screenHeight);

// Initialises the board, overwrites previous board data
void initBoard(State* state, int width, int height);

// Deletes the board data
void freeBoard(State* state);

// Steps the board
void step(State* state);

#endif
