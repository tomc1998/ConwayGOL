#include <GLFW/glfw3.h>
#include "state.h"
#include "input_handler.h"

State* state = NULL;

void keyCallback(GLFWwindow* window,
                 int key,
                 int scancode,
                 int action,
                 int mods) {
  if (key == GLFW_KEY_ESCAPE) {
    state->endflag = 1;
  }
}

void setInputHandlerStateRef(State* _state) {
  state = _state;
}
