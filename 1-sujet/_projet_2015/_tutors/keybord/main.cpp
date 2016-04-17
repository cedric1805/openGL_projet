// #include <windows.h> // a decommenter sous windows
#include <GL/glut.h>
#include <stdlib.h>
GLfloat angle = 0.0 ;
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT) ;
    glLoadIdentity() ;
    glRotatef(angle,0,0,1) ;
    glutSolidTeapot(.5);
    glFlush() ;
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
        angle ++ ;
        glutPostRedisplay() ;
        break ;
    case 27 /* Esc */:
        exit(1) ;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv) ;
    glutInitDisplayMode(GLUT_RGB) ;
    glutCreateWindow(argv[0]) ;
    glutDisplayFunc(display) ;
    glutKeyboardFunc(keyboard) ;
    glutMainLoop() ;
    return 0 ;
}
