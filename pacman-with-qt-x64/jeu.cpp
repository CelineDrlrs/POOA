#include "jeu.h"
#include <iostream>
#include <assert.h>
#include <list>


Fantome::Fantome()
{
    posX = 0; posY = 0;
    dir = BAS;
}

Fantome::Fantome(int x, int y)
{
    posX = x; posY = y;
    dir = BAS;
}

int Fantome::getPosX() const
{
    return posX;
}

int Fantome::getPosY() const
{
    return posY;
}


point::point()
{
    posX = 0; posY = 0;
    dir = BAS;
}

int point::getPosX() const
{
    return posX;
}

int point::getPosY() const
{
    return posY;
}


gum::gum()
{
    posX = 0; posY = 0;
    dir = BAS;
}

int gum::getPosX() const
{
    return posX;
}

int gum::getPosY() const
{
    return posY;
}

Jeu::Jeu()
{
    terrain = NULL;
    score =0;
    largeur = 0; hauteur = 0;
    posPacmanX = 0; posPacmanY = 0;
}

Jeu::~Jeu()
{
    if (terrain!=NULL)
        delete[] terrain;
}

bool Jeu::init()
{
	int x, y;
	nbpoint=0;
	score=0;
	list<Fantome>::iterator itFantome;
	list<point>::iterator itpoint;
	list<gum>::iterator itgum;

	const char terrain_defaut[16][22] = {
		"#####################",
		"#........###........#",
		"#.#####..###...####.#",
		"#........###........#",
		"#...................#",
		"#......#.....#......#",
		"#......#....##......#",
		"#####..#.....#..#####",
		"#......##....#......#",
		"#......#.....#......#",
		"#........###........#",
		"#...................#",
		"#.....#.......#.....#",
		"#.....#.......#.....#",
		"#.....#.......#.....#",
        "#####################"
    };

	largeur = 21;
	hauteur = 16;

	terrain = new Case[largeur*hauteur];

	for(y=0;y<hauteur;++y)
		for(x=0;x<largeur;++x)
            if (terrain_defaut[y][x]=='#')
                terrain[y*largeur+x] = MUR;
            else
            {
                terrain[y*largeur+x] = VIDE;
                nbpoint=nbpoint+1;
            }
    fantomes.resize(4);

// Préparation des fantômes

	for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
    {
        do {
            x = rand()%largeur;
            y = rand()%hauteur;
        } while (terrain[y*largeur+x]!=VIDE);

        itFantome->posX = x;
        itFantome->posY = y;
        itFantome->dir = (Direction)(rand()%4);
    }

// Initialisation des Gum

    gums.resize(4);
    for(itgum=gums.begin(); itgum!=gums.end(); itgum++)
    {
        do {
            x = rand()%largeur;
            y = rand()%hauteur;
        } while (terrain[y*largeur+x]!=VIDE);

        itgum->posX = x;
        itgum->posY = y;
    }
 //Initialisation Points

    points.resize(nbpoint);
    itpoint=points.begin();
    do
    {
        for(y=0;y<hauteur;++y)
            for(x=0;x<largeur;++x)
            {
                if (terrain[y*largeur+x] == VIDE)
                {
                    itpoint->posX = x;
                    itpoint->posY = y;
                    itpoint++;
                }
            }
    }
    while(itpoint!=points.end());

// Initialisation de la position du pacman

    x=10;
    y=11;
//    do {
//        x = rand()%largeur;
//        y = rand()%hauteur;
//    } while (terrain[y*largeur+x]!=VIDE);

    posPacmanX = x,
    posPacmanY = y;

    return true;
}

void Jeu::evolue()
{
    int testX, testY;
	list<Fantome>::iterator itFantome;
	list<point>::iterator itpoint;
	list<gum>::iterator itgum;

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
  // disparition des points et incrémentation du score
    for (itpoint=points.begin(); itpoint!=points.end(); itpoint++)
    {
        testY = itpoint->posY;
        testX = itpoint->posX;
        if ((testY==posPacmanY)&&(testX==posPacmanX))
        {
            score += 10;
            points.erase(itpoint);
            break;
        }
    }
    // Disparition des Gum et incrémentation du score ( 50pt par gum mangée ) + Capacité à manger les fantomes

       for (itgum=gums.begin(); itgum!=gums.end(); itgum++)
    {
        testY = itgum->posY;
        testX = itgum->posX;
        if ((testY==posPacmanY)&&(testX==posPacmanX))
        {
            score += 50;
            gums.erase(itgum);
            Jeu::gumMiam = 1;
            break;
        }
    }
}
int Jeu::getNbCasesX() const
{
    return largeur;
}

int Jeu::getNbCasesY() const
{
    return hauteur;
}

int Jeu::getPacmanX() const
{
    return posPacmanX;
}

int Jeu::getPacmanY() const
{
    return posPacmanY;
}

Case Jeu::getCase(int x, int y) const
{
    assert(x>=0 && x<largeur && y>=0 && y<hauteur);
    return terrain[y*largeur+x];
}

bool Jeu::posValide(int x, int y) const
{
    return (x>=0 && x<largeur && y>=0 && y<hauteur && terrain[y*largeur+x]==VIDE);
}

bool Jeu::deplacePacman(Direction dir)
{
    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};
    int testX, testY;
    PosPac=dir;

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

int Jeu::scoreactuel()const
{
    return score;
}

