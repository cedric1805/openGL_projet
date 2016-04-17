// #include <windows.h> // a decommenter sous windows
#include <GL/glut.h>
GLfloat angle = 0.0 ;
unsigned int delay = 100 ; /* milliseconds */
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT) ;
    glLoadIdentity() ;
    glRotatef(angle,0,0,1) ;
    glRectf(-0.5,-0.5,0.5,0.5) ;
    glFlush();
}

void timer(int theTimer)
{
    angle ++ ;
    glutPostRedisplay() ;
    glutTimerFunc(delay, timer, theTimer) ;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv) ;
    glutInitDisplayMode(GLUT_RGB) ;
    glutCreateWindow(argv[0]) ;
    glutDisplayFunc(display) ;
    glutTimerFunc(delay, timer, 0) ;
    glutMainLoop() ;
    return 0 ;
}
