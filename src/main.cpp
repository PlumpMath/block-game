#include "glew/glew.h"
#include "glfw/glfw3.h"

#include "game/world.h"

int main()
{
  if (!glfwInit())
  {
    return -1;
  }

  GLFWwindow* window = glfwCreateWindow(512, 512, "BlockGame", nullptr, nullptr);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glewInit();

  double time = 0;
  double new_time;
  double delta;

  int width;
  int height;

  block_game::World world;

  const char* vertex_source = R"(
#version 110

attribute vec4 in_Position;

varying vec4 pass_Color;

void main(void)
{
	gl_Position = in_Position;

	pass_Color = gl_Color;
}
  )";

  const char* fragment_source = R"(
#version 110

varying vec4 pass_Color;

void main(void)
{
	gl_FragColor = pass_Color;
}
  )";

  const int vertex_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_id, 1, &vertex_source, nullptr);
  glCompileShader(vertex_id);

  const int fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_id, 1, &fragment_source, nullptr);
  glCompileShader(fragment_id);

  const int program_id = glCreateProgram();
  glAttachShader(program_id, vertex_id);
  glAttachShader(program_id, fragment_id);

  glLinkProgram(program_id);
  glValidateProgram(program_id);

  while (!glfwWindowShouldClose(window))
  {
    new_time = glfwGetTime();
    delta = new_time - time;
    time = new_time;
    world.Update(delta);

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glUseProgram(program_id);
    world.Display();
    glUseProgram(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }



  glDetachShader(program_id, vertex_id);
  glDetachShader(program_id, fragment_id);

  glDeleteShader(vertex_id);
  glDeleteShader(fragment_id);

  glDeleteProgram(program_id);

  glfwDestroyWindow(window);
  glfwTerminate();
}
