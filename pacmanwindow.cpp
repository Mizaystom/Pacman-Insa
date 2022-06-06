#include <iostream>
#include "pacmanwindow.hpp"
#define Offset 50
#define DelaisFantomes 80

using namespace std;

PacmanWindow::PacmanWindow(QWidget *pParent, Qt::WindowFlags flags):QFrame(pParent, flags)
{
    //cout<<__FUNCTION__<<endl;

    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    //Chargement des images
    loadImages();

    //Ajouts de boutons
    boutonsFenetre();

    //Mise en place du timer
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PacmanWindow::handleTimer);
    timer->setInterval(200);
    timer->start();
    this->timer=timer;
    //timer->isActive();

    //Initialisation de la partie
    jeu.init();

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    resize(jeu.getNbCasesX()*largeurCase, jeu.getNbCasesY()*hauteurCase + Offset);
}

void PacmanWindow::loadImages()
{
    //cout<<__FUNCTION__<<endl;
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

    if (pixmapVide.load("./data/vide.bmp")==false)
    {
        cout<<"Impossible d'ouvrir pacman.png"<<endl;
        exit(-1);
    }

     if (pixmapMur.load("./data/mur.bmp")==false)
    {
        cout<<"Impossible d'ouvrir mur.bmp"<<endl;
        exit(-1);
    }

    if (pixmapPion.load("./data/pion.bmp")==false)
    {
        cout<<"Impossible d'ouvrir pion.png"<<endl;
        exit(-1);
    }

    if (pixmapGrosPion.load("./data/grospion.bmp")==false)
    {
        cout<<"Impossible d'ouvrir grospion.png"<<endl;
        exit(-1);
    }

    if (pixmapDebutDans.load("./data/debut dans.bmp")==false)
    {
        cout<<"Impossible d'ouvrir debut dans.bmp"<<endl;
        exit(-1);
    }

    if (pixmapImage1.load("./data/image1.bmp")==false)
    {
        cout<<"Impossible d'ouvrir image1.bmp"<<endl;
        exit(-1);
    }

    if (pixmapImage2.load("./data/image2.bmp")==false)
    {
        cout<<"Impossible d'ouvrir image2.bmp"<<endl;
        exit(-1);
    }

    if (pixmapImage3.load("./data/image3.bmp")==false)
    {
        cout<<"Impossible d'ouvrir image3.bmp"<<endl;
        exit(-1);
    }
}

void PacmanWindow::boutonsFenetre()
{
    //cout<<__FUNCTION__<<endl;
    //Bouton de nouvelle partie
    PacmanBouton *btn_NouvellePartie = new PacmanBouton(this);
    btn_NouvellePartie->setFixedSize(130,30);
    btn_NouvellePartie->setText("Nouvelle Partie");
    btn_NouvellePartie->move(10,10);
    connect(btn_NouvellePartie, &QPushButton::clicked, this, &PacmanWindow::handleBoutonNouvellePartie);

    //Bouton de niveau suivant
    PacmanBouton *btn_NivSuivant = new PacmanBouton(this);
    btn_NivSuivant->setFixedSize(130,30);
    btn_NivSuivant->setText("Niveau Suivant");
    btn_NivSuivant->move(150,10);
    connect(btn_NivSuivant, &QPushButton::clicked, this, &PacmanWindow::handleBoutonNivSuivant);

    //Bouton d'ajout de vies
    PacmanBouton *btn_AjoutVie = new PacmanBouton(this);
    btn_AjoutVie->setFixedSize(50,30);
    btn_AjoutVie->setText("Vie +");
    btn_AjoutVie->move(290,10);
    connect(btn_AjoutVie, &QPushButton::clicked, this, &PacmanWindow::handleBoutonAjoutVie);

    //Bouton de suppression de vies
    PacmanBouton *btn_SupprVie = new PacmanBouton(this);
    btn_SupprVie->setFixedSize(50,30);
    btn_SupprVie->setText("Vie -");
    btn_SupprVie->move(350,10);
    connect(btn_SupprVie, &QPushButton::clicked, this, &PacmanWindow::handleBoutonSupprVie);
}

void PacmanWindow::paintEvent(QPaintEvent *)
{
    //cout<<__FUNCTION__<<endl;
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
            else if (jeu.getCase(x,y)==PION)
                painter.drawPixmap(x*largeurCase, y*hauteurCase + Offset, pixmapPion);
            else if (jeu.getCase(x,y)==GROSPION)
                painter.drawPixmap(x*largeurCase, y*hauteurCase + Offset, pixmapGrosPion);
            else if (jeu.getCase(x,y)==VIDE)
                painter.drawPixmap(x*largeurCase, y*hauteurCase + Offset, pixmapVide);

    // Dessine les fantomes
    for (itFantome=jeu.fantomes.begin(); itFantome!=jeu.fantomes.end(); itFantome++)
        {
            if(itFantome->getEstMangeable() == true)       // Dessine les fantomes mangeables
                painter.drawPixmap(itFantome->getPosX()*largeurCase, itFantome->getPosY()*hauteurCase + Offset, pixmapFantome2);
            else if(itFantome->getEstMangeable() == false)    // Dessine les fantomes normaux par défaut
                painter.drawPixmap(itFantome->getPosX()*largeurCase, itFantome->getPosY()*hauteurCase + Offset, pixmapFantome);
        }

	// Dessine Pacman
	painter.drawPixmap(jeu.getPacmanX()*largeurCase, jeu.getPacmanY()*hauteurCase + Offset, pixmapPacman);

	// Dessine les coeurs
	if (jeu.getNbVie() >= 1)
        painter.drawPixmap(560, 12, pixmapVie);
	if (jeu.getNbVie() >= 2)
        painter.drawPixmap(520, 12, pixmapVie);
	if (jeu.getNbVie() >= 3)
        painter.drawPixmap(480, 12, pixmapVie);

    //Affiche "Game over"
    if (jeu.getNbVie() == 0)
        {
            painter.drawPixmap(PacmanWindow().width()/2-pixmapGO.width()/2, PacmanWindow().height()/2-pixmapGO.height()/2, pixmapGO);
        }
}

void PacmanWindow::keyPressEvent(QKeyEvent *event)
{
    //cout<<__FUNCTION__<<endl;
    if (event->key()==Qt::Key_Left)
    {
        jeu.setDirectionPacmanFuture(GAUCHE);
        cout<<"Touche Gauche"<<endl;
    }
    else if (event->key()==Qt::Key_Right)
    {
        jeu.setDirectionPacmanFuture(DROITE);
        cout<<"Touche Droite"<<endl;
    }
    else if (event->key()==Qt::Key_Up)
    {
        jeu.setDirectionPacmanFuture(HAUT);
        cout<<"Touche Haut"<<endl;
    }
    else if (event->key()==Qt::Key_Down)
    {
        jeu.setDirectionPacmanFuture(BAS);
        cout<<"Touche Bas"<<endl;
    }
    update();
}

void PacmanWindow::handleTimer()
{
    cout<<__FUNCTION__<<endl;
    list<Fantome>::iterator itFantome;
    jeu.evolue();
    update();

    //Si un fantome est mangeable, le compteur s'incrémente
    //au bout de 80 incrémentations, le compteur se réinitialise
    //et passe les fantomes en non mangeables
    if(jeu.fantomes.begin()->getEstMangeable() == true)
    {
        if(jeu.getCompteur() >= 0 && jeu.getCompteur() < DelaisFantomes)
        {
            //cout<<"Compteur = "<<jeu.getCompteur()<<endl;
            jeu.setCompteur(jeu.getCompteur()+1);
        }

        else if (jeu.getCompteur() >= DelaisFantomes)
        {
            //cout<<"Coucou"<<endl;
            for(itFantome=jeu.fantomes.begin(); itFantome!=jeu.fantomes.end(); itFantome++)
            {
                itFantome->setEstMangeable(false);
                jeu.setCompteur(0);
            }
        }
    }

    //Vérifie si la partie est perdue
    if (jeu.getNbVie() == 0)
    {
        cout<<"nbVies = 0, timer stop"<<endl;
        this->timer->stop();
        //QTimer::singleShot(4000, this, &PacmanWindow::handleBoutonNouvellePartie);
    }

    //Vérifie si niveau finito
    if (jeu.getFinNiveau() == true)
    {
        handleBoutonNivSuivant();
    }
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

void PacmanWindow::handleBoutonNouvellePartie()
{
    cout<<__FUNCTION__<<endl;
    cout<<"Nouvelle partie"<<endl;
    jeu.init();
    jeu.setScore(0);
    this->timer->start();
    update();
}

void PacmanWindow::handleBoutonNivSuivant()
{
    cout<<__FUNCTION__<<endl;
    cout<<"Niveau reussi !"<<endl<<"Nouveau niveau"<<endl;
    this->timer->stop();
    jeu.init();
    update();
    this->timer->start();
}

