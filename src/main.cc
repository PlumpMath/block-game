#include <cmath>
#include <GL/glut.h>

float points[][2] = {{-0.5f, -0.5f}, {0.5f, -0.5f}, {0.5f, 0.5f}, {-0.5f, 0.5f}};
float theta = 0;

void Display()
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

void Update()
{
  theta += 0.01f;
  glutPostRedisplay();
}

void StartTimer();

void Timer(int value)
{
  StartTimer();
  Update();
}

void StartTimer()
{
  glutTimerFunc(1000 / 60, Timer, 0);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutCreateWindow("BlockGame");
  glutDisplayFunc(Display);
  StartTimer();
  glutMainLoop();
}
