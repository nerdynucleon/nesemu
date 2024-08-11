#include "nes.h"
#include "opengl.h"

#define GL_SILENCE_DEPRECATION true
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    GL(glViewport(0, 0, width, height));
}

int main(int argc, char* argv[]) {
  nes device;
  device.init();
  device.run();

    // Initialize GLFW
  if (!glfwInit()) {
      std::cerr << "Failed to initialize GLFW" << std::endl;
      return -1;
  }

  // Set GLFW context version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a windowed mode window and its OpenGL context
  GLFWwindow* window = glfwCreateWindow(800, 600, "NES Emu", NULL, NULL);
  if (!window) {
      std::cerr << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  OpenGL gl;
  gl.init();

  // Set the framebuffer size callback
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    gl.render(device.videoBuffer(), device.videoBufferWidth(), device.videoBufferHeight());

		// Swap buffers
		glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }

  // Clean up and exit
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
