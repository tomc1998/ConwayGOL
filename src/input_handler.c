#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include "state.h"
#include "input_handler.h"

const int CONTROL_QUIT = GLFW_KEY_ESCAPE;
const int CONTROL_STEP = GLFW_KEY_SPACE;
const int CONTROL_RUN = GLFW_KEY_E;

State* state = NULL;
int lmbDown = 0;
double mouseXPos, mouseYPos;
// Stores the index of the cell last modified by the mouse
int lastCellModifiedIndex;

void keyCallback(GLFWwindow* window,
                 int key,
                 int scancode,
                 int action,
                 int mods) {
  if (key == CONTROL_QUIT) {
    state->endflag = 1;
  }
  else if (key == CONTROL_STEP && action == GLFW_PRESS) {
    step(state);
  }
  else if (key == CONTROL_RUN && action == GLFW_PRESS) {
    state->running = !state->running;
  }
}

void mouseButtonCallback(GLFWwindow* window,
                           int button,
                           int action,
                           int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    lmbDown = 1;
    // Translate absolute screen positions into positions relative to
    // the board, using the top-left of the board at the origin
    double xPos = mouseXPos - state->boardScreenX;
    double yPos = mouseYPos - state->boardScreenY;
    // Toggle clicked cell value
    int cellX = floor(xPos / state->cellSize);
    int cellY = floor(yPos / state->cellSize);
    int index = cellX + cellY*state->boardWidth;
    lastCellModifiedIndex = index;
    state->board[index] = !state->board[index];
  }
  else if (button == GLFW_MOUSE_BUTTON_LEFT &&
           action == GLFW_RELEASE) {
    lmbDown = 0;
  }
}

void cursorPosCallback(GLFWwindow* window,
                              double xpos,
                              double ypos) {
  mouseXPos = xpos;
  mouseYPos = ypos;
  if (lmbDown) {
    double xPos = mouseXPos - state->boardScreenX;
    double yPos = mouseYPos - state->boardScreenY;
    // Toggle clicked cell value
    int cellX = floor(xPos / state->cellSize);
    int cellY = floor(yPos / state->cellSize);
    int index = cellX + cellY*state->boardWidth;
    if (index < 0 ||
        index >= state->boardWidth*state->boardHeight) {
      return;
    }
    if (index != lastCellModifiedIndex) {
      state->board[index] = !state->board[index];
      lastCellModifiedIndex = index;
    }
  }
}

void setInputHandlerStateRef(State* _state) {
  state = _state;
}
