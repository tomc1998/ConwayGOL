#include <stdio.h>
#include "state.h"
#include "renderer.h"
#include "input_handler.h"
#include <GLFW/glfw3.h>

GLFWwindow* window = 0;

// Initialises GLFW and sets up a GL context given a screen width and
// height in the state pointer
void initGLFW(State* state) {
  glfwInit();
  window = glfwCreateWindow(state->SCREEN_WIDTH, state->SCREEN_HEIGHT,
                            "Conway", NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, keyCallback);
}

int main(int argc, char** argv) {
  State state;
  initState(&state, 800, 450);
  initBoard(&state, 20, 20);
  setInputHandlerStateRef(&state);
  initGLFW(&state);
  initRenderer(&state);
  state.board[21] = 1;
  state.board[22] = 1;
  state.board[23] = 1;

  while(!state.endflag) {
    glClear(GL_COLOR_BUFFER_BIT);

    render(&state);
    
    glfwSwapBuffers(window);
    glfwPollEvents();

    if (glfwWindowShouldClose(window)) {
      state.endflag = 1;
    }
  }

  return 0;
}
