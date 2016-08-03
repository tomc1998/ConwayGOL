#include <GLFW/glfw3.h>
#include "state.h"

void keyCallback(GLFWwindow* window,
                 int key,
                 int scancode,
                 int action,
                 int mods);

// Call this to let input_handler reference the state
void setInputHandlerStateRef(State* _state);

