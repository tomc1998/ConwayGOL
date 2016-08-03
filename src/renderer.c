#include <stdio.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include "state.h"

void initRenderer(State* state) {
  glClearColor(1, 0, 0, 1);

  glViewport(0, 0, state->SCREEN_WIDTH, state->SCREEN_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, state->SCREEN_WIDTH, state->SCREEN_HEIGHT, 0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void render(State* state) {
  if (state->board == 0) {
    printf("Board not initialised\n");
    return;
  }
  int jj;
  int ii = 0;
  glPointSize(16);
  glColor3f(1, 1, 1);
  glBegin(GL_POINTS);
  for (; ii < state->boardWidth; ++ii) {
    for (jj = 0; jj < state->boardHeight; ++jj) {
      int val = state->board[ii + jj*state->boardWidth];
      if (val == 0) {
        glColor3f(0, 0, 0);
      }
      else if (val == 1) {
        glColor3f(1, 1, 1);
      }
      glVertex2f(ii*16 + 8, jj*16 + 8);
    }
  }
  glEnd();
}