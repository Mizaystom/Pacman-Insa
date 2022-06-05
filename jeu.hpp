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
    //Compteur d'incrément de temps pour l'état mangeable
    int compteur;

  public:
    Fantome();                      // Constructeur d'un fantome
    int getPosX() const;            // Retourne la position du fantome
    int getPosY() const;

    bool getEstMangeable() const;   // Retourne l'état du fantome
    void setEstMangeable(bool);     // Change l'état du fantome

    int getCompteur() const;   // Retourne le numéro du compteur
    void setCompteur(int);     // Change le numéro du compteur
};

class Jeu
{
  protected:
    Case *terrain;
    int largeur, hauteur; // Nombre de cases en largeur et en hauteur
    int posPacmanX, posPacmanY;
    int nbVies;
    int score;
    Direction directionPacman, directionPacmanFuture;
    bool finNiveau;

  public:
    std::list<Fantome> fantomes;

  public:
    Jeu();
    Jeu(const Jeu &)=delete;
    ~Jeu();

    Jeu &operator=(const Jeu &)=delete;

    bool init();
    void evolue();
    void ajouter_fantome();
    void supprimer_fantome();

    // Retourne les dimensions (en nombre de cases)
    int getNbCasesX() const;
    int getNbCasesY() const;

    // Retourne la position du Pacman
    int getPacmanX() const;
    int getPacmanY() const;
    // Change la position du Pacman
    void setPacmanX(int);
    void setPacmanY(int);

    //Change l'état des fantomes
    void rendFantomesMangeables();
    void rendFantomesNonMangeables();

    // Retourne le nombre de vies
    int getNbVie() const;
    // Change le nombre de vies
    void setNbVie(int);

    //Change le score
    void setScore(int);

    // Retourne la case à une position donnée (Mur/Vide/Pion/Gros Pion)
    Case getCase(int, int) const;

    //Retourne si le niveau est terminé
    bool getFinNiveau() const;

    // Indique si la case à une position donnée existe et est vide
    // (Pacman ou les fantomes peuvent l'occuper)
    bool posValide(int, int) const;

    // Déplace Pacman dans une direction (si la case à atteindre est valide)
    bool deplacePacman(Direction);
    bool deplacePacman();

    //Set Direction pacman
    void setDirectionPacman(Direction);
    void setDirectionPacman();

    //Test de position
    void testPositionPacman();

    //Test de fin de niveau
    bool testFinNiveau();
};

#endif
