#include <iostream>
#include <cassert>
#include "jeu.hpp"

using namespace std;


//************************Fantomes************************//

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


//************************Jeu************************//

//Constructeur jeu
Jeu::Jeu()
{
    cout<<__FUNCTION__<<endl;
    terrain = NULL;
    largeur = 0; hauteur = 0;
    posPacmanX = 0; posPacmanY = 0;
    finNiveau = false;
    compteur = 0;
    //cout<<"score : "<<score<<endl;
}

//Destructeur jeu
Jeu::~Jeu()
{
    cout<<__FUNCTION__<<endl;
    if (terrain!=NULL)
        delete[] terrain;
}

//Initialisation du jeu
bool Jeu::init()
{
    //cout<<__FUNCTION__<<endl;

	//Déclaration des variables
	int x, y, i;
	list<Fantome>::iterator itFantome;

	//Initialisation des attributs du jeu
    largeur = 19;
	hauteur = 21;
	nbVies = 3;
    fantomes.clear();
    finNiveau = false;
    compteur = 0;

	//Déclaration du terrain
	const char terrain_defaut[hauteur][largeur+1] = {
		"###################",
		"#.0......#........#",
		"#.##.###.#.###.##0#",
		"#.................#",
		"#.##.#.#####.#.##.#",
		"#....#...#...#....#",
		"####.###.#.###.####",
		"####.#.......#.####",
		"####0#.##.##.#.####",
		"xxxx...##.##...xxxx",
		"####.#.#####.#.####",
		"####0#...x...#0...#",
		"####.#.#####.#.##.#",
		"#.0......#.......0#",
		"#.##.###.#.###.##.#",
		"#..#..0.....0..#..#",
		"##.#.#.#####.#.#.##",
		"#....#...#...#....#",
		"#.######.#.######.#",
		"#0................#",
        "###################"
    };
	terrain = new Case[largeur*hauteur];

	//Génération du terrain
	for(y=0;y<hauteur;++y)
		for(x=0;x<largeur;++x)
        {
            if (terrain_defaut[y][x]=='#')
                terrain[y*largeur+x] = MUR;
            else if (terrain_defaut[y][x]=='.')
                terrain[y*largeur+x] = PION;
            else if (terrain_defaut[y][x]=='0')
                terrain[y*largeur+x] = GROSPION;
            else
                terrain[y*largeur+x] = VIDE;
        }

       //Génération du pacman
    do {
        x = 9;
        y = 11;
    } while (terrain[y*largeur+x]==MUR);
    posPacmanX = x,
    posPacmanY = y;
    directionPacman = (Direction) 4;        //Le pacman généré va vers le haut
    directionPacmanFuture = (Direction) 4;  //Le pacman n'a pas de prochaine direction

     //Génération des fantomes
	for (i=0;i<4;i++)
    {
        ajouter_fantome();
    }

    return true;
}

//Actualisation jeu
void Jeu::evolue()
{
    cout<<__FUNCTION__<<endl;
    //Deplacement du pacman en fonction de la direction
    setDirectionPacman();
    deplacePacman(directionPacman);

    //Gestion déplacement des fantomes
    int testX, testY;
	list<Fantome>::iterator itFantome;
    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};

    for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
    {
        testX = itFantome->posX + depX[itFantome->dir];
        testY = itFantome->posY + depY[itFantome->dir];

        if (terrain[testY*largeur+testX]!=MUR)
        {
            itFantome->posX = testX;
            itFantome->posY = testY;
        }
        else
            // Changement de direction
            itFantome->dir = (Direction)(rand()%4);
    }

    testPositionPacman();

    finNiveau = testFinNiveau();
}

void Jeu::ajouter_fantome()
{
    Fantome f1;
    int x,y;

    //Les fantomes spawnent au centre du terrain
    //(vérifie que la position n'est pas un mu)
    do {
            x = 9;
            y = 9;
        } while (terrain[y*largeur+x]==MUR);

        f1.posX = x;
        f1.posY = y;
        f1.dir = HAUT;

    //Ajoute le fantome à la liste
    fantomes.push_back(f1);
}

void Jeu::supprimer_fantome()
{
    fantomes.pop_front();
}

//************Accesseurs et mutateurs du jeu************//
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

//Mutateur nombre de vies restantes
void Jeu::setNbVie(int pNbVies)
    {
        nbVies = pNbVies;
    }

//Mutateur score
void Jeu::setScore(int pScore)
    {
        score = pScore;
    }

//Accesseur type de case (mur/vide)
Case Jeu::getCase(int x, int y) const
{
    assert(x>=0 && x<largeur && y>=0 && y<hauteur);
    return terrain[y*largeur+x];
}

//Accesseur fin de niveau
bool Jeu::getFinNiveau() const
{
    return finNiveau;
}

//Accesseur Compteur
int Jeu::getCompteur() const
{
    return compteur;
}

//Mutateur Compteur
void Jeu::setCompteur(int pCompteur)
    {
        compteur = pCompteur;
    }

//************Méthodes de position du pacman************//

//Renvoie vrai si la position existe et n'est pas un mur
bool Jeu::posValide(int x, int y) const
{
    return (x>=0 && x<largeur && y>=0 && y<hauteur && terrain[y*largeur+x]!=MUR);
}

/*
//Change la direction du pacman si la direction est possible
void Jeu::setDirectionPacman(Direction dir)
{
    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};
    int testX, testY;

    //Associe 2 direction à tester
    testX = posPacmanX + depX[dir];
    testY = posPacmanY + depY[dir];

    //si la nouvelle direction est possible, changement de direction
    if (posValide(testX, testY) && (directionPacman!=directionPacmanFuture))
        {
            directionPacman=dir;
            directionPacmanFuture=(Direction) 4;
        }
    //Sinon, changement de direction à la prochaine case vide
    else
        directionPacmanFuture=dir;
}
*/

void Jeu::setDirectionPacmanFuture(Direction pDirectionFuture)
{
    directionPacmanFuture = pDirectionFuture;
}

//Change la direction du pacman si la direction est possible
void Jeu::setDirectionPacman()
{
    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};
    int testX, testY;

    //Associe 2 direction à tester
    testX = posPacmanX + depX[directionPacmanFuture];
    testY = posPacmanY + depY[directionPacmanFuture];

    //Si test bon,
    if (posValide(testX, testY) && (directionPacman!=directionPacmanFuture))
        {
            directionPacman = directionPacmanFuture;
            directionPacmanFuture = (Direction)4;
        }
}

bool Jeu::deplacePacman(Direction dir)
{
    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};
    int testX, testY;

    //cout<<__FUNCTION__<<endl;

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

void Jeu::testPositionPacman()
{
    list<Fantome>::iterator itFantome;
    //Teste la position du pacman pour les pions
    if (terrain[posPacmanY*largeur+posPacmanX]==PION)
        {
            (terrain[posPacmanY*largeur+posPacmanX]=VIDE);
            score++;
            cout<<"Score : "<<score<<endl;
        }
    //Teste la position du pacman pour les pions
    else if (terrain[posPacmanY*largeur+posPacmanX]==GROSPION)
        {
            (terrain[posPacmanY*largeur+posPacmanX]=VIDE);
            score = score + 10;
            cout<<"Score : "<<score<<endl;
            //Transforme les fantomes en mangeable si compteur <2
            //En non mangeable sinon
            for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
            {
                itFantome->estMangeable = true;
                compteur = 0;
                /*
                if(itFantome->compteur >= 0 && itFantome->compteur <2)
                {

                    //itFantome->compteur++;
                    cout<<"cas 1"<<endl;
                    cout<<"compteur = "<<itFantome->compteur<<endl;
                    cout<<"estMangeable = "<<itFantome->estMangeable<<endl;
                }
                else if (itFantome->compteur >= 2)
                {
                    itFantome->estMangeable = false;
                    itFantome->compteur = 0;
                    cout<<"cas 2"<<endl;
                    cout<<"compteur = "<<itFantome->compteur<<endl;
                    cout<<"estMangeable = "<<itFantome->estMangeable<<endl;
                }*/
            }
            //Timer 20s
            //Si fantomes mangé
            //=> Fantome supprimé et respawn 5s après
            //Fantomes non mangeables
        }
    //for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
    //{
        //if(terrain[posPacmanY*largeur+posPacmanX]==fantome)*/
            //Vies--
            //Si/while(pos initiale pacman != position fantome)
                //setPosPacman initial
    //}

}

bool Jeu::testFinNiveau()
{
    int x, y;
    //cout<<__FUNCTION__<<endl;
    for(y=0;y<hauteur;++y)
    {
        for(x=0;x<largeur;++x)
        {
            if(terrain[y*largeur+x] == PION ||terrain[y*largeur+x] == GROSPION)
            {
                return false;
            }
        }
    }
    return true;
}
