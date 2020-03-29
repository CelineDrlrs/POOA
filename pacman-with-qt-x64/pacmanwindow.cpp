#include <iostream>
#include "pacmanwindow.h"
#include <stdlib.h>
#include "jeu.h"

using namespace std;

PacmanWindow::PacmanWindow(QWidget *pParent, Qt::WindowFlags flags):QFrame(pParent, flags)
{
    // Taille des cases en pixels
    int largeurCase, hauteurCase;

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


   // BOUTONS -------------------------------------------------------

    PacmanButton *btnajout = new PacmanButton(this);
    btnajout->setFixedSize(110,32);
    btnajout->setText("Ajouter un fantome");

    connect(btnajout, PacmanButton::clicked, this, PacmanWindow::ajoutfantome);
//
//    PacmanButton *btnsuppr = new PacmanButton(this);
//    btnsuppr->setFixedSize(110,32);
//    btnsuppr->move(122,0);
//    btnsuppr->setText("Retirer un fantome");
//
//    connect(btnsuppr, PacmanButton::clicked, this, PacmanWindow::retirefantome);
//
//    PacmanButton *btnquitter = new PacmanButton(this);
//    btnquitter->setFixedSize(70,32);
//    btnquitter->move(570,0);
//    btnquitter->setText("Quitter");
//
//    connect(btnquitter, PacmanButton::clicked, this, PacmanWindow::quitte);


    jeu.init();

    QTimer *timer = new QTimer(this);
    connect(timer, QTimer::timeout, this, PacmanWindow::handleTimer);
    timer->start(100);

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    resize(jeu.getNbCasesX()*largeurCase, jeu.getNbCasesY()*hauteurCase+100);
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
                painter.drawPixmap(x*largeurCase, y*hauteurCase, pixmapMur);

    // Dessine les fantomes
    for (itFantome=jeu.fantomes.begin(); itFantome!=jeu.fantomes.end(); itFantome++)
        painter.drawPixmap(itFantome->getPosX()*largeurCase, itFantome->getPosY()*hauteurCase, pixmapFantome);

	// Dessine Pacman
	painter.drawPixmap(jeu.getPacmanX()*largeurCase, jeu.getPacmanY()*hauteurCase, pixmapPacman);
}

void PacmanWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Left)
        jeu.deplacePacman(GAUCHE);
    else if (event->key()==Qt::Key_Right)
        jeu.deplacePacman(DROITE);
    else if (event->key()==Qt::Key_Up)
        jeu.deplacePacman(HAUT);
    else if (event->key()==Qt::Key_Down)
        jeu.deplacePacman(BAS);
    update();
}

void PacmanWindow::handleTimer()
{
    jeu.evolue();
    update();
}

void PacmanWindow::ajoutfantome()
{
    int x, y;
    do                                      // Les fantomes sont placés sur des cases valides, soit des cases qui ne sont pas des murs
    {
        x = rand()%(jeu.getlargeur());
        y = rand()%(jeu.gethauteur());
    } while (!jeu.posValide(x,y));

    jeu.fantomes.push_back(Fantome(x,y));       // une fois des coordonnées valides trouvées, le fantôme est ajouté à la liste

}

void PacmanButton::keyPressEvent(QKeyEvent *e)
{
    if (parent()!=NULL)
        QCoreApplication::sendEvent(parent(), e);
}

