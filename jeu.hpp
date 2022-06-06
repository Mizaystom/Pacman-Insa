#ifndef JEU_HPP
#define JEU_HPP

#include <list>

typedef enum {VIDE, MUR, PION, GROSPION} Case;
typedef enum {GAUCHE, DROITE, HAUT, BAS} Direction;

class Jeu;

class Fantome
{
    friend class Jeu;

  protected:
    int posX, posY;
    Direction dir;
    bool estMangeable;

  public:
    Fantome();                      // Constructeur d'un fantome
    int getPosX() const;            // Retourne la position du fantome
    int getPosY() const;

    bool getEstMangeable() const;   //Retourne l'état du fantome
    void setEstMangeable(bool);     //Change l'état du fantome

};

class Jeu
{
  protected:
    //Attributs du terrain
    Case *terrain;
    int largeur, hauteur;

    //Attribut du pacman
    int posPacmanX, posPacmanY;
    Direction directionPacman, directionPacmanFuture;
    int nbVies;

    //Attributs de la partie
    int score;
    int compteur;   //Compteur d'incrément de temps pour l'état mangeable des fantomes
    bool finNiveau;

  public:
    //Fantomes de la partie
    std::list<Fantome> fantomes;

  public:
    Jeu();                          //Constructeur de Jeu
    ~Jeu();                         //Destructeurs de Jeu
    Jeu(const Jeu &)=delete;

    Jeu &operator=(const Jeu &)=delete; //Surcharge d'opérateur

    bool init();                    //Initie une partie
    void evolue();                  //Actualise la partie à chaque coup de timer
    void ajouter_fantome();         //Ajoute un fantome à la liste de fantome du jeu
    void supprimer_fantome();       //Supprime """""""""""""""""""""""""""""""""""""

    int getNbCasesX() const;        //Retourne les dimensions (en nombre de cases)
    int getNbCasesY() const;

    int getPacmanX() const;         //Retourne la position du Pacman
    int getPacmanY() const;

    void setPacmanX(int);           //Change la position du Pacman
    void setPacmanY(int);

    int getNbVie() const;           //Retourne le nombre de vies
    void setNbVie(int);             //Change le nombre de vies

    void setScore(int);             //Change le score

    Case getCase(int, int) const;   //Retourne le type de case à une position donnée (Mur/Vide/Pion/Gros Pion)

    bool getFinNiveau() const;      //Indique si le niveau est terminé

    int getCompteur() const;        //Retourne le numéro du compteur
    void setCompteur(int);          //Change le numéro du compteur

    // Indique si la case à une position donnée existe et est vide
    // (Pacman ou les fantomes peuvent l'occuper)
    bool posValide(int, int) const;

    // Déplace Pacman dans une direction (si la case à atteindre est valide)
    bool deplacePacman(Direction);
    bool deplacePacman();

    //Set Direction pacman
    void setDirectionPacmanFuture(Direction);
    void setDirectionPacman();

    //Test de position
    void testPositionPacman();

    //Test de fin de niveau
    bool testFinNiveau();
};

#endif
