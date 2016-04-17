/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */


#include <windows.h>
#include <GL/glut.h>
#include <math.h>



#include "../include/api/CDonneesGraphe.h"
#include "../include/api/CGraphe.h"
#include "../include/api/CSommet.h"
#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

// D�claration des tables du graphe
//CDonneesGraphe gdata("SXYZ.TXT", "SIF.TXT", "PAXYZ.TXT", "AXYZ.TXT");
CDonneesGraphe gdata("data/SXYZ.TXT", "data/SIF.TXT", "data/PAXYZ.TXT", "data/AXYZ.TXT");
// Constrcuction de la base de donnees orientee objet du graphe
CGraphe graphe(gdata);



static int slices = 16;
static int stacks = 16;


/* GLUT callback Handlers */





static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    glPushMatrix();
        glTranslated(-2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


//FONCTIONS
void initialisation();
void redimensionnement(int width, int height);

/* Program entry point */

int main(int argc, char *argv[])
{

    glutInit(&argc, argv); // N�gociation des sessions avec le window system */
    initialisation(); //fonction initialisation

    glutReshapeFunc(redimensionnement);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    //glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}


void initialisation(){
    /* Fonction qui initalise la machine OpenGL
    */


    cout << "Bienvenue ! \n" << __FILE__ << endl; // Nom de l'emplacement du fichier si besoin
    cout << "Appuyer sur q pour quitter" << endl; // Instructions

    GLsizei screenWidth, screenHeight ; // a non-negative binary integer, for sizes.
    screenWidth= glutGet(GLUT_SCREEN_WIDTH); // on recupere la largeur de l'ecran
    screenHeight = glutGet(GLUT_SCREEN_HEIGHT); // on recupere la hauteur de l'ecran
    glutInitWindowPosition(screenWidth/4, screenHeight /4); // position de la fenetre : centre
    glutInitWindowSize(screenWidth/2, screenHeight/2); // taille de la fenetre

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // choix mode representation des couleurs

    glutCreateWindow("Projet OpenGL - SAMASSA et MENUT");

    glClearColor(0.8,0.8,0.8,0); //couleur fond de fenetre : grise

    /* D�finir l�espace visible
    ------------------------------- */
    glPointSize(4); // on impose la taille des points
    glLineWidth(1); // on impose l'�paisseur des traits dans le rendu



    /*

    glPointSize(4);
    glLineWidth(2);
    glutFullScreen();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1.0,0.1,1000);*/
}

void redimensionnement(int width, int height)
{
    /* fonction qui permet de garder les memes perspectives en fonction des differentes echelles de visualisation
    Si on modifie la taille de la fenetre, on conserve les m�mes formes dans le rendu
    */
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

}
