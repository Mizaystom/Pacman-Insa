#ifndef PACMANWINDOW_HPP
#define PACMANWINDOW_HPP

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.hpp"

class PacmanWindow : public QFrame
{
  protected:
    Jeu jeu;
    QPixmap pixmapPacman, pixmapFantome, pixmapMur;

  public:
    PacmanWindow(QWidget *pParent=0, Qt::WindowFlags flags=0);
    void handleTimer();
    void handleBoutonAjoutFantomes();
    void handleBoutonSupprFantomes();

  protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
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
