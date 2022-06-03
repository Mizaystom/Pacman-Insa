#include <iostream>
#include <cassert>
#include "jeu.hpp"

using namespace std;

//Constructeur fantome
Fantome::Fantome()
{
    posX = 0; posY = 0;
    dir = HAUT;
    estMangeable = false;
}

//Accesseur Position X fantome
int Fantome::getPosX() const
{
    return posX;
}
//Accesseur Position Y fantome
int Fantome::getPosY() const
{
    return posY;
}

//Accesseur Etat fantome
bool Fantome::getEstMangeable() const
{
    return estMangeable;
}
//Mutateur Etat fantome
void Fantome::setEstMangeable(bool pEstMangeable)
    {
        estMangeable = pEstMangeable;
    }

//COnstructeur jeu
Jeu::Jeu()
{
    terrain = NULL;
    largeur = 0; hauteur = 0;
    posPacmanX = 0; posPacmanY = 0;
    nbVies = 3;
}
//Destructeur jeu
Jeu::~Jeu()
{
    if (terrain!=NULL)
        delete[] terrain;
}

//Initialisation du jeu
bool Jeu::init()
{
	int x, y, i;
	list<Fantome>::iterator itFantome;

    largeur = 19;
	hauteur = 21;

	const char terrain_defaut[hauteur][largeur+1] = {
		"###################",
		"#........#........#",
		"#.##.###.#.###.##.#",
		"#.................#",
		"#.##.#.#####.#.##.#",
		"#....#...#...#....#",
		"####.###.#.###.####",
		"####.#.......#.####",
		"####.#.##.##.#.####",
		".......##.##.......",
		"####.#.#####.#.####",
		"####.#.......#....#",
		"####.#.#####.#.##.#",
		"#........#........#",
		"#.##.###.#.###.##.#",
		"#..#...........#..#",
		"##.#.#.#####.#.#.##",
		"#....#...#...#....#",
		"#.######.#.######.#",
		"#.................#",
        "###################"
    };

	terrain = new Case[largeur*hauteur];

	for(y=0;y<hauteur;++y)
		for(x=0;x<largeur;++x)
            if (terrain_defaut[y][x]=='#')
                terrain[y*largeur+x] = MUR;
            else
                terrain[y*largeur+x] = VIDE;


	for (i=0;i<4;i++)
    {
        ajouter_fantome();
    }

    do {
        x = 9;
        y = 11;
    } while (terrain[y*largeur+x]!=VIDE);

    posPacmanX = x,
    posPacmanY = y;

    return true;
}

//Actualisation jeu
void Jeu::evolue()
{
    int testX, testY;
	list<Fantome>::iterator itFantome;

    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};

    for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
    {
        testX = itFantome->posX + depX[itFantome->dir];
        testY = itFantome->posY + depY[itFantome->dir];

        if (terrain[testY*largeur+testX]==VIDE)
        {
            itFantome->posX = testX;
            itFantome->posY = testY;
        }
        else
            // Changement de direction
            itFantome->dir = (Direction)(rand()%4);
    }

    //Fonction test position
}

void Jeu::ajouter_fantome()
{
    Fantome f1;
    int x,y;

    do {
            x = 9;
            y = 9;
        } while (terrain[y*largeur+x]!=VIDE);

        f1.posX = x;
        f1.posY = y;
        f1.dir = HAUT;

    fantomes.push_back(f1);
}

void Jeu::supprimer_fantome()
{
    fantomes.pop_front();
    //rendFantomesMangeables(); //Pour test
}

//Accesseur Largeur jeu
int Jeu::getNbCasesX() const
{
    return largeur;
}
//Accesseur Hauteur jeu
int Jeu::getNbCasesY() const
{
    return hauteur;
}
//Accesseur Position X pacman
int Jeu::getPacmanX() const
{
    return posPacmanX;
}
//Accesseur Position Y pacman
int Jeu::getPacmanY() const
{
    return posPacmanY;
}
//Mutateur Position X pacman
void Jeu::setPacmanX(int pPosPacmanX)
    {
        posPacmanX = pPosPacmanX;
    }
//Mutateur Position Y Pacman
void Jeu::setPacmanY(int pPosPacmanY)
    {
        posPacmanY = pPosPacmanY;
    }

//Accesseur nombre de vies restantes
int Jeu::getNbVie() const
{
    return nbVies;
}

void Jeu::setNbVie(int pNbVies)
    {
        nbVies = pNbVies;
    }

//Accesseur type de case (mur/vide)
Case Jeu::getCase(int x, int y) const
{
    assert(x>=0 && x<largeur && y>=0 && y<hauteur);
    return terrain[y*largeur+x];
}

//Renvoie vrai si position existante et est vide
bool Jeu::posValide(int x, int y) const
{
    return (x>=0 && x<largeur && y>=0 && y<hauteur && terrain[y*largeur+x]==VIDE);
}

bool Jeu::deplacePacman(Direction dir)
{
    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};
    int testX, testY;

    testX = posPacmanX + depX[dir];
    testY = posPacmanY + depY[dir];

    if (posValide(testX, testY))
    {
        posPacmanX = testX;
        posPacmanY = testY;
        return true;
    }
    else
        return false;
}

//Fonction test de position
    //Test à chaque incrément de temps si position des fantomes = position pacman
    //(pour collisions)

    //Test à chaque incrément de temps si position du pacman = position grosse boule
    /*
    if(poscapcman == grosseboule) //Attention pas tester position grosseboule mais si case = grousseboule (pas vide ou mur)
    {
        rendFantomesMangeables();
    }
    //mettre en place timer puis désactiver état mangeable (timer =QTSingleshot)
    rendFantomesNonMangeables();
    */

// A revoir
void Jeu::rendFantomesMangeables()
{
    //int i = 0;
    list<Fantome>::iterator itFantome;
    for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
    {
        itFantome->estMangeable = true;
        //i++;
        //cout<<"Fantome "<< i <<" = "<<itFantome->estMangeable<<endl;
    }
}


