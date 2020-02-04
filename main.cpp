#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <GL/glut.h>

const int N = 30, M = 20;
const int SCALE = 25;
const int INITIAL_LEN = 4;
int W = SCALE * N;
int H = SCALE * M;
int dir, num = INITIAL_LEN;

void setTitleScore();

struct
{
    int x;
    int y;
} s[100];

class Fruits
{
    public:	int x, y;
    void New()
    {
        x = (int)random() % N;
        y = (int)random() % M;
    }
    void DrawApple()
    {
       glColor3f(0.5, 0.0, 0.0); // цвет корма
       glRectf(x * SCALE,y * SCALE,(x + 1) * SCALE,(y + 1) * SCALE);
    }
} m[10];

void drawSnake()
{
  glColor3f(0.0, 0.4, 0.0); // цвет змеи
  for (int i = 0; i < num; i++) {
      glRectf(s[i].x * SCALE, s[i].y * SCALE, (s[i].x + 0.9) * SCALE, (s[i].y + 0.9) * SCALE);
  }
}

void tick()
{
    for (int i = num; i > 0; --i) {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }
    if (dir == 0) s[0].y += 1;
    if (dir == 1) s[0].x -= 1;
    if (dir == 2) s[0].x += 1;
    if (dir == 3) s[0].y -= 1;
    for (auto & i : m) if ((s[0].x == i.x) && (s[0].y == i.y)) {
        num++;
        i.New();
        setTitleScore();
    }
    for (int i = 1; i < num; i++) if (s[0].x == s[i].x && s[0].y == s[i].y) {
        num = INITIAL_LEN; // в оригинале было i - это некорректно
        setTitleScore();
    }
    // проверка с нестрогим равенством приводила к тому, что змея могла уползти за пределы экрана
    if (s[0].x >= N) dir = 1;
    if (s[0].x <= 0) dir = 2;
    if (s[0].y >= M) dir = 3;
    if (s[0].y <= 0) dir = 0;
}

void drawField()
{
   glColor3f(0.2, 0.2, 0.2); // цвет сетки
   glBegin(GL_LINES);
   for (int i = 0; i < W; i += SCALE) {
       glVertex2f(i, 0);
       glVertex2f(i, H);
   }
   for (int j = 0; j < H; j += SCALE) {
       glVertex2f(0, j);
       glVertex2f(W, j);
   }
   glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawField();
    drawSnake();
    for (auto & i : m) i.DrawApple(); // вместо for (int i = 0; i < 10; i++) m[i].DrawApple();
    glFlush();
    glutSwapBuffers();
}

void setTitleScore() {
    char winTitle[256];
    sprintf(winTitle, "Snake - your score: %d", num);
    glutSetWindowTitle(winTitle);
}

void KeyboardEvent(int key, int a, int b)
{
    switch(key) {
        case 101:
            dir = 0;
            break;
        case 102:
            dir = 2;
            break;
        case 100:
            dir = 1;
            break;
        case 103:
            dir = 3;
            break;
        default:
            break;
     }
}

void timer(int = 0)
{
    display();
    tick();
    glutTimerFunc(80, timer,0);
}

int main(int argc, char **argv) {
    int i = 0;
    srand(time(nullptr));
	for (i = 0; i < 10; i++) m[i].New();
    s[i].x = 10;
    s[i].y = 10;
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize (W, H);
    glutCreateWindow ("Snake");
    setTitleScore();
    glClearColor(0.1, 0.1, 0.1, 1.0);  //цвет фона
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, W, 0, H);
    glutDisplayFunc (display);
    glutSpecialFunc(KeyboardEvent);
    glutTimerFunc(80, timer, 0);
    glutMainLoop();
}