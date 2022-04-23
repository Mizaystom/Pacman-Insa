#ifndef JEU_HPP
#define JEU_HPP

#include <list>

typedef enum {VIDE, MUR} Case;
typedef enum {GAUCHE, DROITE, HAUT, BAS} Direction;

class Jeu;

class Fantome
{
    friend class Jeu;

  protected:
    int posX, posY;
    Direction dir;

  public:
    Fantome();
    int getPosX() const;
    int getPosY() const;
};

class Jeu
{
  protected:
    Case *terrain;
    int largeur, hauteur; // Nombre de cases en largeur et en hauteur
    int posPacmanX, posPacmanY;

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

    // Retourne la case à une position donnée
    Case getCase(int, int) const;

    // Indique si la case à une position donnée existe et est vide
    // (Pacman ou les fantomes peuvent l'occuper)
    bool posValide(int, int) const;

    // Déplace Pacman dans une direction (si la case à atteindre est valide)
    bool deplacePacman(Direction);
};

#endif
