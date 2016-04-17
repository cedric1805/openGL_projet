// #include <windows.h> // a decommenter sous windows
#include <GL/glut.h>
GLfloat angle = 0.0 ;
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT) ;
    glLoadIdentity() ;
    glRotatef(angle,0,0,1) ;
    glRectf(-0.5,-0.5,0.5,0.5) ;
    glutSwapBuffers() ;
}

void idle(void)
{
    angle = ((int)angle++) % 360 ;
    glutPostRedisplay() ;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv) ;
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE) ;
    glutCreateWindow(argv[0]) ;
    glutDisplayFunc(display) ;
    glutIdleFunc(idle) ;
    glutMainLoop() ;
    return 0 ;
}
