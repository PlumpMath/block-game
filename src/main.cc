#include <cmath>
#include <GL/glut.h>

static const float points [][2] = {{-0.5f, -0.5f}, {0.5f, -0.5f}, {0.5f, 0.5f}, {-0.5f, 0.5f}};
static float angle = 0;

void Display()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_QUADS);
  glColor3f(1.0f, 0.0f, 0.0f);
  for (const float* point : points)
  {
    glVertex2f(point[0] * cos(angle) - point[1] * sin(angle), point[0] * sin(angle) + point[1] * cos(angle));
  }
  glEnd();

  glFlush();
}

void Update()
{
  angle += 0.01f;
  glutPostRedisplay();
}

void StartTimer();

void Timer(const int value)
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
