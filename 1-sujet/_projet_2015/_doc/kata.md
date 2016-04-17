#Wiki GeomatiqueGL
==================

##Kata I (minigl)
~~~~~~~~~~~~~~~~~
Soit le code minimal suivant :

    * Faire tourner le code
    * Quelle ligne de code faut-il ajouter pour dessiner une théière
    * Quelle sont les limites geometriques du volume de vision par défaut
    * Que se passe-t-il lorsque la fenêtre est redimensionnée

    ::
        #include <windows.h>
        #include <GL/glut.h>
        void display(void)
        {
            glClear(GL_COLOR_BUFFER_BIT) ;
         
            glFlush() ;
        }
         
        int main(int argc, char **argv)
        {
            glutInit(&argc, argv) ;
            glutInitDisplayMode(GLUT_RGB) ;
            glutCreateWindow(argv[0]) ;
            glutDisplayFunc(display) ;
            glutMainLoop() ;
            return 0 ;
        }
 

##Kata II.a (reshape)
~~~~~~~~~~~~~~~~~~~~~

On souhaite capturer la taille de la fenetre de (largeur, hauteur) à chaque que la fenetre est redimentionnée.

    * Quelle callback utiliser?
    * Quel est le prototype de la fonction passée à la callback?
    * Définir une fonction reshape qui affiche (un print suffit) la largeur et la hauteur de la fenêtre à chaque fois que celle-ci est redimensionnée.


##Kata II.b (reshape_ortho)
~~~~~~~~~~~~~~~~~~~~~~~~~~~

On considère la fonction reshape ci-dessous:

    * Brancher cette fonction de manière adéquate au code existant.
    * Modofier les valeurs de near, far, bottom, top, left, right.
    * Quel est le constat? A quoi sert cette fonction?
    * Commenter la ligne glViewport(0, 0, width, height). Que se passe-t-il lorsque la fenêtre est redimensionnée? A quoi sert cette ligne?
    * A quoi servent les appels glLoadIdentity()?
    * Décrire de manière simple et synthétique ce que fait cette fonction reshape.
    Indication: 
    Rajouter cette ligne, observer la variation des valeurs quand l'on redimensionne la fenêtre.
    printf("(%.3f, %.3f, %.3f, %.3f)\n", left, right, bottom, top, near, far);

    ::
        void reshape(int width, int height) {
            GLdouble aspect = (GLdouble) width / height ;
            GLdouble near = -1.0, far = 1.0 ;
            GLdouble left = -1.0, right = 1.0 ;
            GLdouble bottom = -1.0, top = 1.0 ;
            glViewport(0, 0, width, height) ;
            glMatrixMode(GL_PROJECTION) ;
            glLoadIdentity() ;
            if ( aspect < 1.0 ) {
                left /= aspect ;
                right /= aspect ;
            } else {
                bottom *= aspect ;
                top *= aspect ;
            }
            glOrtho(left, right, bottom, top, near, far) ;
            glMatrixMode(GL_MODELVIEW) ;
            glLoadIdentity() ;
        }


##Kata II.c (reshape_persp)
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Remplacer la fonction reshape précédente par la suivante. Décrire de manière simple la différence.

    ::
        void reshape(int width, int height) {
            GLdouble aspect = (GLdouble) width / height ;
            GLdouble near = -1.0, far = 1.0 ;
            GLdouble fovy = 60.0 ;
            glViewport(0, 0, width, height) ;
            glMatrixMode(GL_PROJECTION) ;
            glLoadIdentity() ;
            gluPerspective(fovy, aspect, near, far) ;
            glMatrixMode(GL_MODELVIEW) ;
            glLoadIdentity();
            gluLookAt(
                0.0, 0.0, 5.0, /* œil */
                0.0, 0.0, 0.0, /* point observé */
                0.0, 1.0, 0.0 /* où est le ciel ? */
            ) ;
        }


##Kata III.a (keyboard)
~~~~~~~~~~~~~~~~~~~~~~~

Soit le fonction ci-dessous :
    
    * Décrire très simplement ce qu'elle
    * Via quelle fonction de callback peut-on l'utiliser
    * Ajouter une touche qui permette :
        - de changer la couleur d'un objet dessiné
        - de faire tourner l'objet autour de lui même

    ::
        void keyboard(unsigned char key, int x, int y){
            void (*f)(int, int) ;
            switch (key) {
                case 27:
                    exit(0);
                    break;
                case 'o':
                case 'O':
                    f = &reshapeo;
                    break;
                case 'p':
                case 'P':
                    f = &reshapep;
                    break;
                default:
                    break;
            }
     
            int w = glutGet(GLUT_WINDOW_WIDTH);
            int h = glutGet(GLUT_WINDOW_HEIGHT);
         
            glutReshapeFunc(f);
            f(w, h);
            glutPostRedisplay();
        }


##Kata III.b (special)
~~~~~~~~~~~~~~~~~~~~~~

    * Trouver le prototype de la fonction de callback glutSpecialFunc
    * glutSpecialFunc est analogue à glutKeyboardFunc. Quelle est la différence fonctionnelle principale.
    * 'Associer' les touches
        - "flêche du bas / du haut)" pour faire tourner la scène atour de l'axe (0, x)
        - "droite / gauche" pour faire tourner la scène atour de l'axe (0, y)


##Kata IV (mouse + motion)
~~~~~~~~~~~~~~~~~~~~~~~~~~

Pour associer les actions de la souris au programme openGL, glut se offre la callback glutMouseFunc et glutMotionFunc (cf. prototype ci-dessous)

    ::
        glutMouseFunc(void (*func)(int button, int state, int x, int y))
        glutMotionFunc(void (* func)(int x, int y))

Les deux callbacks sont indépendant, mais on peut les faire communiquer par variable globale interposée.

D'une manière générale lorsque l'utilisateur veut manipuler un objet de la scène à l'aide de la souris, il maintien un bouton B enfoncé (c'est à dire dans dans un état E := 'enfoncé') en exécutant un mouvement de translation T (Tx, Ty) en coordonnée fenetre.

    * La callback glutMouseFunc permet de capturer l'identificateur du bouton B (gauche, droit, milieu, etc.), son état E et sa position M(x, y) en coordonnée fenêtre à l'instant de l'action (clic ou "dé-clic").
    * glutMotionFunc permet de connaître la position de la souris (toujours en coordonnées fenetre) à chaque mouvement de la souris
    * Soit _moving_ la variable booléenne à *true* si le bouton gauche de la souris est enfoncé, *false* sinon. Utiliser la mécanique décrite pour afficher les coordonées de la souris quand le bouton gauche de la souris est enfoncée.



##Kata V.a (idle)
~~~~~~~~~~~~~~~

La callback _glutIdleFunc(void (*func)(void))_ rappelle la fonction passée en parametre à chaque fois que le cpu est inoccupé. Cette caractérisique est souvent utilisée pour réaliser des animations. 

Le principe de l'animation demeure simple. Il s'agit de dessiner une séquence d'images successives au cours du temps. En opengl, cela correspond à des ordres succesives d'effacement et de dessin de la scene.

Le code suivant montre comment cabler ce mécanisme. 

    * Le completer pour faire tourner un objet simple autour de l'axe z.
    * L'appel à glutIdleFunc(NULL) stoppe l'animation. 
    Cabler la possibiliter de stopper et de redémarrer l'animation au clavier.

    ::
        void idle() {
            // changement des parametre de dessin
            // ex. rot_z = (rot_z + 1) % 360;
            glutPostRedisplay() ;
        }

        void display(){
            glClear(GL_COLOR_BUFFER_BIT);
            //...
            glRoratef(rot_z, 0., 0., 1.);
            glPushMatrix();
            //dessin de l'objet à animer
            glPopMatrix();
            //dessin d'autres objets
            glFlush();
        }

        int main(int argc, char **argv){
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_RGB);
            //...
            glutIdleFunc(idle);
            glutDisplayFunc(display);
            glutMainLoop();
        }


##Kata V.b (double buffer)
~~~~~~~~~~~~~~~~~~~~~~~~~~

Le double buffering consiste à dessiner l'image suivante d'une séquence I(n+1) en arriere plan (sur le back buffer) au moment ou l'image courante I(n) est affichée à l'écran (front buffer). De sorte que'une simple permutation du _front_ et du _back_ suffisent à afficher I(n+1). Le double buffering est utilisé pour fluidifier les animations.

La mise en place du double buffering se fait:
    #. en ajoutant GLUT_DOUBLE au "display mode" 
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    #. en remplaçant glFlush par l'appel à glutSwapBuffers 

    ::
        void idle() {
            // changement des parametre de dessin
            // ex. rot_z = (rot_z + 1) % 360;
            glutPostRedisplay();
        }

        void display(){
            glClear(GL_COLOR_BUFFER_BIT);
            //...
            glRoratef(rot_z, 0., 0., 1.);
            glPushMatrix();
            //dessin d'un objet complexe
            glPopMatrix();
            //dessin d'autres objets
            glutSwapBuffers(); // à la place de glFlush
        }

        int main(int argc, char **argv){
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // GL_DOUBLE en plus
            //...
            glutIdleFunc(idle);
            glutDisplayFunc(display);
            glutMainLoop();
        }


##Kata V.c (timer)
~~~~~~~~~~~~~~~~~~

cf. le tutoriel timer dans le répertoire _turors/




