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
    niveau =0;
    largeur = 0; hauteur = 0;
    posPacmanX = 0; posPacmanY = 0;
    nbvie = 0;
    timeFant = 50 ;
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
    list<Fantome>::iterator itFantome;
    list<point>::iterator itpoint;
    list<gum>::iterator itgum;

    if(niveau==0)
    {
        const char terrain_defaut[16][22] = {
            "#####################",
            "#........###........#",
            "#.#####..###...####.#",
            "#........###........#",
            "#...................#",
            "#......#.....#......#",
            "#......#....##......#",
            "####...#.....#...####",
            "G   ...##....#...   D",
            "####...#.....#...####",
            "#........###........#",
            "#...................#",
            "#.....#.......#.....#",
            "#.....#.......#.....#",
            "#.....#.......#.....#",
            "#####################"
        };

        largeur = 21;
        hauteur = 16;
        nbvie = 3;

        terrain = new Case[largeur*hauteur];

        for(y=0;y<hauteur;++y)
            for(x=0;x<largeur;++x)
                if (terrain_defaut[y][x]=='#')
                    terrain[y*largeur+x] = MUR;
                else if(terrain_defaut[y][x]=='G')
                {
                    terrain[y*largeur+x] = PORTEG;
                }
                else if(terrain_defaut[y][x]=='D')
                {
                    terrain[y*largeur+x] = PORTED;
                }
                else if(terrain_defaut[y][x]==' ')
                {
                    terrain[y*largeur+x] = RIEN;
                }
                else if(terrain_defaut[y][x]=='.')
                {
                    terrain[y*largeur+x] = VIDE;
                    nbpoint=nbpoint+1;
                }
    }

    else if(niveau==1)
    {
        const char terrain_defaut[16][22] = {
            "#####################",
            "#........###........#",
            "#.#####..###..#####.#",
            "#...#....###....#...#",
            "#...................#",
            "#.......#....#......#",
            "#.......###.###.....#",
            "####....#.....#..####",
            "G   ....#######..   D",
            "####....#.....#..####",
            "#.........###.......#",
            "#...................#",
            "#.....#.......#.....#",
            "#.....#.......#.....#",
            "#.....#.......#.....#",
            "#####################"
        };

        largeur = 21;
        hauteur = 16;
        nbvie = 3;

        terrain = new Case[largeur*hauteur];

        for(y=0;y<hauteur;++y)
            for(x=0;x<largeur;++x)
                if (terrain_defaut[y][x]=='#')
                    terrain[y*largeur+x] = MUR;
                else if(terrain_defaut[y][x]=='G')
                {
                    terrain[y*largeur+x] = PORTEG;
                }
                else if(terrain_defaut[y][x]=='D')
                {
                    terrain[y*largeur+x] = PORTED;
                }
                else if(terrain_defaut[y][x]==' ')
                {
                    terrain[y*largeur+x] = RIEN;
                }
                else if(terrain_defaut[y][x]=='.')
                {
                    terrain[y*largeur+x] = VIDE;
                    nbpoint=nbpoint+1;
                }
    }
    else if(niveau==2)
    {
       const char terrain_defaut[18][22] = {
        "#####################",
		"#...................#",
		"#......#######......#",
		"#...................#",
		"#......#######......#",
		"#.........##........#",
		"#.......##..........#",
        "#......#######......#",
		"####.............####",
		"G   ...#...##....   D",
		"####....##...#...####",
		"#...................#",
		"#......######.......#",
		"#.........####......#",
		"#......######.......#",
		"#...................#",
        "#####################"
    };
    largeur = 21;
    hauteur = 16;
    nbvie = 3;

    terrain = new Case[largeur*hauteur];

    for(y=0;y<hauteur;++y)
        for(x=0;x<largeur;++x)
            if (terrain_defaut[y][x]=='#')
                terrain[y*largeur+x] = MUR;
            else if(terrain_defaut[y][x]=='G')
            {
                terrain[y*largeur+x] = PORTEG;
            }
            else if(terrain_defaut[y][x]=='D')
            {
                terrain[y*largeur+x] = PORTED;
            }
            else if(terrain_defaut[y][x]==' ')
            {
                terrain[y*largeur+x] = RIEN;
            }
            else if(terrain_defaut[y][x]=='.')
            {
                terrain[y*largeur+x] = VIDE;
                nbpoint=nbpoint+1;
            }
    }

    fantomes.resize(4);

// Pr�paration des fant�mes

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

    x=10;  //On a fait en sorte que le pacman soit � une position donn�e � chaque reprise du jeu
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
    if(getnbvie()!=0 && gagne()==false)
    {
        int x,y;
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

    if (Jeu::gumMiam==1)
    {
        timeFant -= 1;
    }

    // disparition des points et incr�mentation du score
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

        // Disparition des Gum et incr�mentation du score ( 50pt par gum mang�e ) + Capacit� � manger les fantomes

        for (itgum=gums.begin(); itgum!=gums.end(); itgum++)
        {
            testY = itgum->posY;
            testX = itgum->posX;
            if ((testY==posPacmanY)&&(testX==posPacmanX))
            {
                score += 50;
                gums.erase(itgum);
                Jeu::gumMiam = 1;
                timeFant = 50 ;
                break;
            }
        }

        // Capacit� � manger les fant�mes si une gum a �t� mang�e ( 250 points par fantome mang� !)

        if(Jeu::gumMiam == 1)
        {
            for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
            {
                testY = itFantome->posY;
                testX = itFantome->posX;
                if ((testY==posPacmanY)&&(testX==posPacmanX))
                {
                    score += 250;
                    fantomes.erase(itFantome);
                    break;
                }
            }
        }
        if(Jeu::timeFant<=0)
        {
            Jeu::gumMiam = 0;
        }

        if(testpertevie())  //On regarde si pacman perd une vie puis on applique la perte sur le nombre de vie et on replace pacman au d�but du jeu
            {
                int largeur = 20;
                int hauteur = 15;
                setnbvie(getnbvie()-1);
                //cout<<"Pacman perd une vie"<<endl;
                do {
                    x = rand()%largeur;
                    y = rand()%hauteur;
                } while (terrain[y*largeur+x]==MUR);

                posPacmanX = 10;
                posPacmanY = 11;
            }
        if (getnbvie()==0)
            {
                cout<<"Game Over"<<endl;
            }
        if (gagne()==true)
        {
            cout<<"Et c'est gagn� !! Oui, oui, oui !!!"<<endl;
        }
    }

    //Cr�ation des portes de passage
    if(terrain[posPacmanY*largeur+posPacmanX]==PORTEG)
    {
        posPacmanX=18;
    }
    if(terrain[posPacmanY*largeur+posPacmanX]==PORTED)
    {
        posPacmanX=1;
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
    return (x>=0 && x<largeur && y>=0 && y<hauteur && (terrain[y*largeur+x]==VIDE ||  terrain[y*largeur+x]==RIEN || terrain[y*largeur+x]==PORTED || terrain[y*largeur+x]==PORTEG));
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

int Jeu::scoreactuel() const
{
    return score;
}

int Jeu::getnbvie() const
{
    return nbvie;
}

void Jeu::setnbvie(int vie)
{
    nbvie=vie;
}



// Perte de vie
bool Jeu::testpertevie()                        // On teste si Pacman perd une vie
{
    list<Fantome>::iterator itFantome;

    if(Jeu::gumMiam == 0)
    {
            for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
        {
            if ((itFantome->posX == posPacmanX) && (itFantome->posY == posPacmanY)&&(nbvie>0))
            {
                return true;
            }
        }
    }
    return false;
}

bool Jeu::gagne()                   // joueur gagnant = le terrain n'a plus de gum
{
        if (points.empty())
        {
            return true;
        }
    return false;
}
