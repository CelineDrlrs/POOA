#ifndef JEU_H
#define JEU_H

#include <list>
using namespace std;

typedef enum {VIDE, MUR, PORTEG, PORTED, RIEN} Case;
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
    Fantome(int, int);
    int getPosX() const;
    int getPosY() const;
};

class gum
{
        friend class Jeu;

    protected:
        int posX, posY;
        Direction dir;

    public:
        gum();
        int getPosX() const;
        int getPosY() const;
};


class point
{
        friend class Jeu;

    protected:
        int posX, posY;
        Direction dir;

    public:
        point();
        int getPosX() const;
        int getPosY() const;
};

class Jeu
{
  protected:
    Case *terrain;
    int largeur, hauteur; // Nombre de cases en largeur et en hauteur
    int posPacmanX, posPacmanY;
    int nbvie;

  public:
    list<Fantome> fantomes;
    list<point> points;
    list<gum> gums;
    int nbpoint, score ;
    Direction PosPac;
    int gumMiam;

    Jeu();
    Jeu(const Jeu &)=delete;
    ~Jeu();

    Jeu &operator=(const Jeu &)=delete;

    bool init();
    void evolue();
    bool insa();

    //Score
    int scoreactuel() const;

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

    // Teste la perte de vie
    bool testpertevie();

    // Getteur et setteur vie
    int getnbvie() const;
    void setnbvie(int);

    bool gagne ();
};

#endif
