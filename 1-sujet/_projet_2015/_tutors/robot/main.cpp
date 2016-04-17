// #include <windows.h> // a decommenter sous windows
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>

int shoulder = 0, elbow = 0;
bool moving = false;
int prev_x = -1, prev_y = -1;
int dx = 0, dy = 0;


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    {

        glRotatef(dx, 0, 1, 0);
        glRotatef(dy, 1, 0, 0);

        glPushMatrix();
        {

            glTranslatef (-1.0, 0.0, 0.0);
            glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
            glTranslatef (1.0, 0.0, 0.0);
            glPushMatrix();
            {

                glScalef (2.0, 0.4, 1.0);
                glutWireCube (1.0);
            }
            glPopMatrix();

            glTranslatef (1.0, 0.0, 0.0);
            glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
            glTranslatef (1.0, 0.0, 0.0);
            glPushMatrix();
            {

                glScalef (2.0, 0.4, 1.0);
                glutWireCube(1.0);
            }
            glPopMatrix();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glBegin(GL_LINES);
            glColor3f(1., 0., 0.);
            glVertex2i(0, 0);
            glVertex2i(1, 0);

            glColor3f(0., 1., 0.);
            glVertex2i(0, 0);
            glVertex2i(0, 1);
            glEnd();

        }
        glPopMatrix();
        glColor3f(1., 1., 1.);
    }
    glPopMatrix();
    glFlush();
}

void reshape(int w, int h)
{
    GLdouble aspect = (GLdouble) w/h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65., aspect, 1., 20.);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt
    (
        0., 0., 10.,
        0., 0., 0.,
        0., 1., 0.
    );
}



void keys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':
        shoulder = (shoulder + 5) % 360;
        break;
    case 'S':
        shoulder = (shoulder - 5) % 360;
        break;
    case 'e':
        elbow = (elbow + 5) % 360;
        break;
    case 'E':
        elbow = (elbow - 5) % 360;
        break;
    }
//    printf("shoulder %03d\n", shoulder);
    glutPostRedisplay();

}

void motion(int x, int y)
{
    if (!moving)
        return;

    dx += x-prev_x ;
    dy += y-prev_y ;
    glutPostRedisplay() ;
    prev_x = x ;
    prev_y = y ;
}


void mouse(int button, int state, int x, int y)
{
    moving = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
    printf("button=%d, state=%d, x=%d, y=%d ==> moving=%d\n", button, state, x, y, moving);
    if (!moving)
        return;
    prev_x = x;
    prev_y = y;
    glutPostRedisplay();
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keys);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
}

