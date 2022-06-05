#ifndef PACMANWINDOW_HPP
#define PACMANWINDOW_HPP

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.hpp"

class PacmanWindow : public QFrame
{
  protected:
    Jeu jeu;

    //Images apparaissant dans la fenetre en tant qu'objets QPixmap
    QPixmap pixmapPacman, pixmapFantome, pixmapFantome2, pixmapVie, pixmapGO;
    QPixmap pixmapMur, pixmapVide, pixmapGrosPion, pixmapPion;

    //Déclaration pour être utilisable dans paintEvent
    QTimer *timer;

  public:
    //Fenetre du jeu
    PacmanWindow(QWidget *pParent=0, Qt::WindowFlags flags=0);

    //Timer
    void handleTimer();

    //Boutons
    void boutonsFenetre();
    void handleBoutonAjoutVie();
    void handleBoutonSupprVie();
    void handleBoutonNouvellePartie();
    void handleBoutonNivSuivant();

    //Chargement des images
    void loadImages();

  protected:
    //Affichage des images
    void paintEvent(QPaintEvent *);

    //Gestions des touches clavier
    void keyPressEvent(QKeyEvent *);

    //Quand le jour perd la partie (nbVies<=0)
    void rebootGame();
    void finPartie();
};

class PacmanBouton : public QPushButton
{
  public:
    void keyPressEvent(QKeyEvent *e)
    {
        if(parent()!=NULL)
            QCoreApplication::sendEvent(parent(), e);
    }
    PacmanBouton(QWidget *pParent=0):QPushButton(pParent) {}
};
#endif
