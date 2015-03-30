#include "glew/glew.h"
#include "glfw/glfw3.h"

#include "game/world.h"
#include "general/matrix_4f.h"
#include "opengl/program.h"
#include "opengl/shader.h"
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

  {
    const block_game::Shader vertex_shader(GL_VERTEX_SHADER, block_game::vertex_glsl);
    const block_game::Shader fragment_shader(GL_FRAGMENT_SHADER, block_game::fragment_glsl);

    block_game::Program program(vertex_shader, fragment_shader);

    program.Use();
    program.SetUniformMatrix4F("matrix", block_game::Matrix4F());

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
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}
