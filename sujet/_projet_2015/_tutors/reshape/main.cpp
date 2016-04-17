// #include <windows.h> // a decommenter sous windows
#include <GL/glut.h>
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT) ;
//    glRectf(-0.5,-0.5,0.5,0.5) ;
    glutSolidCube(.5);
    glutSwapBuffers() ;
}

int main(int argc, char **argv)
{
    void reshape(int, int);
    glutInit(&argc, argv) ;
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE) ;
    glutCreateWindow(argv[0]) ;
    glutDisplayFunc(display) ;
    glutReshapeFunc(reshape) ;
    glutMainLoop() ;
    return 0 ;
}

void reshape(int width, int height)
{
    GLdouble aspect = (GLdouble) width / height ;
    GLdouble n = .5, f = 1.0 ;
    GLdouble fovy = 60.0 ;
    glViewport(0, 0, width, height) ;
    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    gluPerspective(fovy, aspect, n, f) ;
    glMatrixMode(GL_MODELVIEW) ;
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 1.0, /* oeil */
              0.0, 0.0, 0.0, /* point observé */
              0.0, 1.0, 0.0) ; /* où est le ciel ? */
}
