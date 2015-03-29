#include "glew/glew.h"
#include "glfw/glfw3.h"

#include "game/world.h"
#include "shader/vertex.h"
#include "shader/fragment.h"

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

  const int vertex_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_id, 1, &block_game::vertex_glsl, nullptr);
  glCompileShader(vertex_id);

  const int fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_id, 1, &block_game::fragment_glsl, nullptr);
  glCompileShader(fragment_id);

  const int program_id = glCreateProgram();
  glAttachShader(program_id, vertex_id);
  glAttachShader(program_id, fragment_id);

  glLinkProgram(program_id);
  glValidateProgram(program_id);

  const float matrix[] =
  {
    1.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 1.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 1.0F, 0.0F,
    0.0F, 0.0F, 0.0F, 1.0F
  };

  glUseProgram(program_id);
  glUniformMatrix4fv(glGetUniformLocation(program_id, "matrix"), 1, false, matrix);

  glEnable(GL_CULL_FACE);

  while (!glfwWindowShouldClose(window))
  {
    new_time = glfwGetTime();
    delta = new_time - time;
    time = new_time;
    world.Update(delta);

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    world.Display();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDisable(GL_CULL_FACE);

  glUseProgram(0);

  glDetachShader(program_id, vertex_id);
  glDetachShader(program_id, fragment_id);

  glDeleteShader(vertex_id);
  glDeleteShader(fragment_id);

  glDeleteProgram(program_id);

  glfwDestroyWindow(window);
  glfwTerminate();
}
