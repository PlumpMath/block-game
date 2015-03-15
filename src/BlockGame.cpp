#include <cmath>

#include <windows.h>
#include <GL/glut.h>

float points[][2] = {{-0.5f, -0.5f}, {0.5f, -0.5f}, {0.5f, 0.5f}, {-0.5f, 0.5f}};
float theta = 0;

void display()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_QUADS);
  glColor3f(1.0f, 0.0f, 0.0f);
  for (float* point : points)
  {
    glVertex2f(point[0] * cos(theta) - point[1] * sin(theta), point[0] * sin(theta) + point[1] * cos(theta));
  }
  glEnd();

  glFlush();
}

void update()
{
  theta += 0.01f;
  glutPostRedisplay();
}

void startTimer();

void timer(int value)
{
  startTimer();
  update();
}

void startTimer()
{
  glutTimerFunc(1000 / 60, timer, 0);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutCreateWindow("BlockGame");
  glutInitWindowSize(320, 320);
  glutInitWindowPosition(50, 50);
  glutDisplayFunc(display);
  startTimer();
  glutMainLoop();
  return 0;
}
