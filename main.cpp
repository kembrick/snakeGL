#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <GL/glut.h>

const int N = 30, M = 20, SCALE = 30; // количество ячеек и масштаб
const int INITIAL_LEN = 4, START_SPEED = 80, FEED_NUM = 10; // начальная длина змеи, скорость, количество кормушек
int W = SCALE * N, H = SCALE * M;
int dir, num = INITIAL_LEN, speed = START_SPEED;

struct
{
    int x;
    int y;
} s[500];

class Fruits
{
    public:	int x, y;
    void New()
    {
        int loop;
        do {
            loop = 0;
            x = (int)random() % N;
            y = (int)random() % M;
            for (int i = 0; i < num; i++) {
                if (s[i].x == x && s[i].y == y) {
                    loop = 1;
                    break;
                }
            }
        } while (loop);
    }
    void DrawApple()
    {
       glColor3f(0.5, 0.5, 0.0); // цвет корма
       glRectf(x * SCALE,y * SCALE,(x + 0.98) * SCALE,(y + 0.98) * SCALE);
    }
} m[FEED_NUM];

void drawSnake()
{
  glColor3f(0.0, 0.4, 0.0); // цвет змеи
  for (int i = 0; i < num; i++) {
      glRectf(s[i].x * SCALE, s[i].y * SCALE, (s[i].x + 0.98) * SCALE, (s[i].y + 0.98) * SCALE);
  }
}

void setTitleScore() {
    char winTitle[256];
    sprintf(winTitle, "Snake - your score: %d", (num - INITIAL_LEN));
    glutSetWindowTitle(winTitle);
}

void tick()
{
    // Проверка не врезалась ли змея
    if (s[0].x >= N) dir = 0;
    if (s[0].x < 0)  dir = 2;
    if (s[0].y >= M) dir = 3;
    if (s[0].y < 0)  dir = 1;
    for (int i = 1; i < num; i++) if (s[0].x == s[i].x && s[0].y == s[i].y) {
            num = INITIAL_LEN;
            setTitleScore();
            speed = START_SPEED;
        }
    for (int i = num; i > 0; --i) {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }
    if (dir == 0) s[0].x--;
    if (dir == 1) s[0].y++;
    if (dir == 2) s[0].x++;
    if (dir == 3) s[0].y--;
    for (auto & i : m) if ((s[0].x == i.x) && (s[0].y == i.y)) { // змея растет
        num++;
        i.New();
        setTitleScore();
        if (speed > 40) speed -= (int)((num - INITIAL_LEN) / 5);
    }
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

void keyboardEvent(int key, int a, int b)
{
    if (key > 99 && key < 104) dir = key - 100;
}

void timer(int = 0)
{
    display();
    tick();
    glutTimerFunc(speed, timer,0);
}

int main(int argc, char **argv) {
    srand(time(nullptr));
	for (int i = 0; i < FEED_NUM; i++) m[i].New();
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (W, H);
    glutCreateWindow ("Snake");
    //glutSetIconTitle("worm.ico");
    setTitleScore();
    glClearColor(0.1, 0.1, 0.1, 1.0);  // цвет фона
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, W, 0, H);
    glutDisplayFunc (display);
    glutSpecialFunc(keyboardEvent);
    glutTimerFunc(speed, timer, 0);
    glutMainLoop();
}