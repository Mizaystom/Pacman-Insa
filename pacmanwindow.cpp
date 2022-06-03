#include <iostream>
#include "pacmanwindow.hpp"
#define Offset 50

using namespace std;

PacmanWindow::PacmanWindow(QWidget *pParent, Qt::WindowFlags flags):QFrame(pParent, flags)
{
    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    //Chargement des images
    loadImages();

    //Initialisation de la partie
    jeu.init();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PacmanWindow::handleTimer);
    timer->start(100);

    PacmanBouton *btn_AjoutFantomes = new PacmanBouton(this);
    btn_AjoutFantomes->setFixedSize(130,30);
    btn_AjoutFantomes->setText("Ajouter Fantomes");
    btn_AjoutFantomes->move(10,10);
    connect(btn_AjoutFantomes, &QPushButton::clicked, this, &PacmanWindow::handleBoutonAjoutFantomes);

    PacmanBouton *btn_SupprFantomes = new PacmanBouton(this);
    btn_SupprFantomes->setFixedSize(130,30);
    btn_SupprFantomes->setText("Supprimer Fantomes");
    btn_SupprFantomes->move(150,10);
    connect(btn_SupprFantomes, &QPushButton::clicked, this, &PacmanWindow::handleBoutonSupprFantomes);

    PacmanBouton *btn_AjoutVie = new PacmanBouton(this);
    btn_AjoutVie->setFixedSize(50,30);
    btn_AjoutVie->setText("Vie +");
    btn_AjoutVie->move(300,10);
    connect(btn_AjoutVie, &QPushButton::clicked, this, &PacmanWindow::handleBoutonAjoutVie);

    PacmanBouton *btn_SupprVie = new PacmanBouton(this);
    btn_SupprVie->setFixedSize(50,30);
    btn_SupprVie->setText("Vie -");
    btn_SupprVie->move(370,10);
    connect(btn_SupprVie, &QPushButton::clicked, this, &PacmanWindow::handleBoutonSupprVie);

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    resize(jeu.getNbCasesX()*largeurCase, jeu.getNbCasesY()*hauteurCase + Offset);
}

void PacmanWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    list<Fantome>::const_iterator itFantome;
    int x, y;

    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    // Dessine les cases
    for (y=0;y<jeu.getNbCasesY();y++)
        for (x=0;x<jeu.getNbCasesX();x++)
			if (jeu.getCase(x,y)==MUR)
                painter.drawPixmap(x*largeurCase, y*hauteurCase + Offset, pixmapMur);

    // Dessine les fantomes
    for (itFantome=jeu.fantomes.begin(); itFantome!=jeu.fantomes.end(); itFantome++)
        {
            if(itFantome->getEstMangeable() == false)       // Dessine les fantomes normaux
                painter.drawPixmap(itFantome->getPosX()*largeurCase, itFantome->getPosY()*hauteurCase + Offset, pixmapFantome);
            else if(itFantome->getEstMangeable() == true)    // Dessine les fantomes non mangeables
                painter.drawPixmap(itFantome->getPosX()*largeurCase, itFantome->getPosY()*hauteurCase + Offset, pixmapFantome2);
        }

	// Dessine Pacman
	painter.drawPixmap(jeu.getPacmanX()*largeurCase, jeu.getPacmanY()*hauteurCase + Offset, pixmapPacman);

	// Dessine les vies
	if (jeu.getNbVie() >= 1)
        painter.drawPixmap(560, 12, pixmapVie);
	if (jeu.getNbVie() >= 2)
        painter.drawPixmap(520, 12, pixmapVie);
	if (jeu.getNbVie() >= 3)
        painter.drawPixmap(480, 12, pixmapVie);

    //Affiche "Game over"
    if (jeu.getNbVie() == 0)
        painter.drawPixmap(PacmanWindow().width()/2-pixmapGO.width()/2, PacmanWindow().height()/2-pixmapGO.height()/2, pixmapGO);
}

void PacmanWindow::loadImages()
{
    if (pixmapPacman.load("./data/pacman.bmp")==false)
    {
        cout<<"Impossible d'ouvrir pacman.png"<<endl;
        exit(-1);
    }

    if (pixmapFantome.load("./data/fantome.bmp")==false)
    {
        cout<<"Impossible d'ouvrir fantome.bmp"<<endl;
        exit(-1);
    }

    if (pixmapMur.load("./data/mur.bmp")==false)
    {
        cout<<"Impossible d'ouvrir mur.bmp"<<endl;
        exit(-1);
    }

    if (pixmapFantome2.load("./data/fantome2.bmp")==false)
    {
        cout<<"Impossible d'ouvrir fantome2.bmp"<<endl;
        exit(-1);
    }

    if (pixmapVie.load("./data/vie.bmp")==false)
    {
        cout<<"Impossible d'ouvrir vie.bmp"<<endl;
        exit(-1);
    }

    if (pixmapGO.load("./data/game over.bmp")==false)
    {
        cout<<"Impossible d'ouvrir game over.bmp"<<endl;
        exit(-1);
    }
}

void PacmanWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Left)
    {
        jeu.deplacePacman(GAUCHE);
    }
    else if (event->key()==Qt::Key_Right)
    {
        jeu.deplacePacman(DROITE);
    }
    else if (event->key()==Qt::Key_Up)
    {
        jeu.deplacePacman(HAUT);
    }
    else if (event->key()==Qt::Key_Down)
    {
        jeu.deplacePacman(BAS);
    }
    update();
}

void PacmanWindow::handleTimer()
{
    jeu.evolue();
    update();
}

void PacmanWindow::handleBoutonAjoutFantomes()
{
    jeu.ajouter_fantome();
    update();
}

void PacmanWindow::handleBoutonSupprFantomes()
{
    jeu.supprimer_fantome();
    update();
}

void PacmanWindow::handleBoutonAjoutVie()
{
    if(jeu.getNbVie()<3)
        jeu.setNbVie(jeu.getNbVie()+1);
    cout<<"Nombre de vie(s) restante(s) : "<<jeu.getNbVie()<<endl;
    update();
}

void PacmanWindow::handleBoutonSupprVie()
{
    if(jeu.getNbVie()>0)
        jeu.setNbVie(jeu.getNbVie()-1);
    cout<<"Nombre de vie(s) restante(s) : "<<jeu.getNbVie()<<endl;
    update();
}
