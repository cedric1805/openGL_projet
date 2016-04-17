Projet OpenGL 2015
##################

Dossier de projet
=================

Le répertoire _projet_2015 contient les détails du projet et des exemples en fonction du type problème
à résoudre.

    - _api/ contient l'API de parcourt de graphe (vous pouvez faire sans)
    - _doc/ contient le sujet au format texte.
    - _tutors/ regroupe les réponse des Katas (des réponses à des problèmatiques isolée .
      Chaque sujet est abordé de manière isolée
        + rendu,
        + transformations,
        + redimensionnement de fenetre,
        + clavier,
        + souris,
        + animation


Comment installer CodeBlocks + OpenGL
=====================================

**Sous windows**

Il faut:
    - Installer CodeBlocks comme d'hab.
    - Télécharger glut32-bin.zip sur le site de Nate Robin's http://user.xmission.com/~nate/glut/glut-3.7.6-bin.zip
    - Le dezipper
        + Copier glut.def et glut32.lib dans CodeBlocks/MinGW/lib
        + Copier glut.h dans CodeBlocks/MinGW/include/GL
        + Copier glut32.dll dans CodeBlocks/MinGW/bin

**Sous linux**

Il suffit de suivre les instructions sur http://singhgurjot.wordpress.com/2012/05/17/how-to-install-openglglut-libraries-in-ubuntu-12-04/


Sujet
=====

On considère un graphe dont la topologie est la métrique sont modélisées par 4 tables comme suit:

 - SIF: table des topologie du graphe à 2 colonnes dans l'ordre sommet_initial, sommet_final
   + de 1 à NA (le nombre d'arcs)
   + la a-ème ligne de la table correspond à l'arc numéro a.

 - SXYZ: table des coordonnées des sommets à 3 colonnes dans l'ordre X, Y, Z
    + de 1 à NS (le nombre de sommets)
    + la s-ème ligne de la table correspond au sommet numéro s

 - AXYZ: table des coordonnées des points annexes supportés par un arc. à 3 colonnes X, Y, Y
    + de 1 à NPA (le nombre de points annexes)
    + la p-ème ligne donne de les coordonnées spatiales du points annexe d'indice p

 - PAXYZ: table d'indirection vers AXYZ à 2 colonnes p_debut, nb_point_annex
    + de 1 à NA (le nombre d'arcs)
    + la a-ème ligne renseigne pour l'arc d'indice a, sur:
        * l'indice p_debut dans AXYZ du premier point annexe supportées
        * le nombre nb_point_annex de points annexes

cf. Fig 1.

Une base de données objets a été peuplée à partir de ces tables. Désormais, l'on dispose des classes:

    - Sommet,
    - Arc,
    - PointAnnexe, et
    - Graphe

ainsi que des relations qui existent entre elles.

Ainsi:

- Un graphe connait ses composantes : list_arc, list_sommet, list_point_annexe.
- Un point annexe porte ses coordonnées et il en est de même pour Sommet.
- Un sommet connait ses arcs entrants et sortants.
- De la même manière tout arc connait ses sommets initial et final.
- Enfin, un arc connait la liste des points annexes qu’il supporte.

Le code source fourni, n'a aucune dépendance en dehors de la librairie standard C++.
Un exemple d'utilisation se trouve dans le fichier main.cpp du répertoire _api/.

Pour faciliter le parcours du graphe des routines ont été écrites:

    .. code:: c++

        // Récupérer la liste des arcs qui entrent dans le sommet passé en paramètre
        Graphe::getListArcEntrantDansSommet(const CSommet &sommet)

        // Récupérer la liste des points annexes de l'arc passé en paramètre
        Graphe::getListPointAnnexeArc(const CArc &arc)

Exemple:

    .. code:: c++

        #include "CDonneesGraphe.h"
        #include "CGraphe.h"
        #include "CSommet.h"
        #include <vector>
        #include <iostream>
        #include <time.h>
        #include <stdlib.h>
        using namespace std;
        int main() {

            // construction des tables du graphe
            CDonneesGraphe gdata("data/SXYZ.TXT", "data/SIF.TXT", "data/PAXYZ.TXT", "data/AXYZ.TXT");
            // affichage des donnees
            gdata.afficheDonnees();

            // Constrcuction de la base de donnees objet du graphe
            CGraphe graphe(gdata);

            // Preparation du generateur de nombre aleatoire
            srand((unsigned)time(NULL));
            // Tirage d'un nombre aleatoire entre 0 et NS (nombre de sommet)
            int iSommet = rand() % gdata.NS;
            cout<<iSommet<<endl;

            // Recuperation du sommet
            CSommet sommet = graphe.list_sommet.at(iSommet);
            cout<<sommet.toString()<<endl;

            // Recuperation arcs entrants
            vector<CArc> list_arc_entrant = graphe.getListArcEntrantDansSommet(sommet);
            int nb_arc_entrant = list_arc_entrant.size();
            for (int i = 0; i < nb_arc_entrant; ++i) {
                CArc arc = list_arc_entrant.at(i);
                cout<<arc.toString()<<endl;
            }
            graphe.afficheSommets();
            graphe.afficheArcs();
            graphe.buildExtent();
            cout<<graphe.getExtentLowerLeft().toString()<<endl;
            cout<<graphe.getExtentUpperRight().toString()<<endl;
            return EXIT_SUCCESS;
        }

Hypothèse : on considère que le graphe est non orienté et que les mobiles peuvent circuler dans les deux sens

L’objet de l’exercice est de représenter en 3D le graphe et de déplacer des mobiles dessus.

Le travail peut se décomposer en plusieurs étapes :

#. Représentation tridimensionnelle du graphe
#. Représentation des sommets (sous forme de sphère)
#. et des arcs (dans une autre couleur)
#. Déplacement des mobiles
#. Les mobile sont des trains (ensemble articulé d’au moins deux cubes)
#. Gestion des collisions:
    - Les mobiles doivent s’attendre lorsqu’ils se dirigent vers le même sommet
    - Ils doivent éviter le nez à nez
    - Une distance de sécurité doit etre respectée lorsque deux mobiles occupent successivement les
      mêmes arcs.

#. Interaction clavier/souris
#. Rapport
#. Tout effort de rendu 3D, et d’ergonomie sera récompensé !




Grille de notation
==================

#. Rendu +13

    - Graphe: 7
    - Déplacement: 3
    - Collision: 2
    - Clavier: 1
    - Souris: 2

#. Rapport +5

    - Installation: +1
    - Utilisation: +1
    - MCD: +1.5
    - Algo: +1.5

#. Qualité du livrable +2
    - vidéo +1.5
    - arborescence du livrable +.5

	::
		Nom1-Nom2-Nom3.zip
			doc/  # rapport
			demo/ # vidéo
			bin/  # binaires du projets
			src/  # code source du projet
			data/ # données du projets

#. Bonus +3

    - Texture: 1.5
    - Paysage: 1.5


#. Malus -3

    - Conception: -3