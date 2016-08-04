#include <GLFW/glfw3.h>
#include "state.h"

extern const int CONTROL_QUIT;
extern const int CONTROL_STEP;
extern const int CONTROL_RUN;

void keyCallback(GLFWwindow* window,
                 int key,
                 int scancode,
                 int action,
                 int mods);

void mouseButtonCallback(GLFWwindow* window,
                         int button,
                         int action,
                         int mods);

void cursorPosCallback(GLFWwindow* window,
                              double xpos,
                              double ypos);

// Call this to let input_handler reference the state
void setInputHandlerStateRef(State* _state);

