// #include <windows.h> // a decommenter sous windows
#include <GL/glut.h>
typedef void (*tfunction)(int,int);


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT) ;
    glutWireCube(.5);
    glFlush() ;
}

int main(int argc, char **argv)
{
    void reshape_ortho(int width, int height);
    glutInit(&argc, argv) ;
    glutInitDisplayMode(GLUT_RGB) ;
    glutCreateWindow(argv[0]) ;
    glutDisplayFunc(display) ;
    glutMainLoop() ;
    return 0 ;
}
