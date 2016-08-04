#include <GLFW/glfw3.h>
#include "state.h"
#include "input_handler.h"

const int CONTROL_QUIT = GLFW_KEY_ESCAPE;
const int CONTROL_STEP = GLFW_KEY_SPACE;

State* state = NULL;

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
}

void setInputHandlerStateRef(State* _state) {
  state = _state;
}
