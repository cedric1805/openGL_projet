// #include <windows.h> // a decommenter sous windows
#include <GL/glut.h>
GLfloat angle = 0.0 ;
int prev_x = -1 ;
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT) ;
    glLoadIdentity() ;
    glRotatef(angle,0,0,1) ;
    glutSolidTeapot(.5);
    glutSwapBuffers() ;
}

void motion(int x, int y)
{
    if (prev_x!=-1)
    {
        angle += x-prev_x ;
        glutPostRedisplay() ;
    }
    prev_x = x ;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv) ;
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE) ;
    glutCreateWindow(argv[0]) ;
    glutDisplayFunc(display) ;
    glutMotionFunc(motion) ;
    glutMainLoop() ;
    return 0 ;
}
