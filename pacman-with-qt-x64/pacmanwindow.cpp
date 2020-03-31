#include <iostream>
#include "pacmanwindow.h"

using namespace std;

PacmanWindow::PacmanWindow(QWidget *pParent, Qt::WindowFlags flags):QFrame(pParent, flags)
{
    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    if (pixmapPacmanD.load("./data/pacmanD.png")==false)
    {
        cout<<"Impossible d'ouvrir pacmanD.png"<<endl;
        exit(-1);
    }
    if (pixmapPacmanG.load("./data/pacmanG.png")==false)
    {
        cout<<"Impossible d'ouvrir pacmanG.png"<<endl;
        exit(-1);
    }
    if (pixmapPacmanH.load("./data/pacmanH.png")==false)
    {
        cout<<"Impossible d'ouvrir pacmanH.png"<<endl;
        exit(-1);
    }
    if (pixmapPacmanB.load("./data/pacmanB.png")==false)
    {
        cout<<"Impossible d'ouvrir pacmanB.png"<<endl;
        exit(-1);
    }

    if (pixmapFantome.load("./data/fantome.png")==false)
    {
        cout<<"Impossible d'ouvrir fantome.png"<<endl;
        exit(-1);
    }

    if (pixmapMur.load("./data/mur.png")==false)
    {
        cout<<"Impossible d'ouvrir mur.png"<<endl;
        exit(-1);
    }

    if (pixmappoint.load("./data/point.png")==false)
    {
        cout<<"Impossible d'ouvrir point.png"<<endl;
        exit(-1);
    }

    jeu.init();

    QTimer *timer = new QTimer(this);
    connect(timer, QTimer::timeout, this, PacmanWindow::handleTimer);
    timer->start(100);

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    resize(jeu.getNbCasesX()*largeurCase, jeu.getNbCasesY()*hauteurCase);

    QLabel *Tagscore = new QLabel(this);
    Tagscore->setStyleSheet("background-color:pink");
    Tagscore->setGeometry(400,20,50,20);
    Tagscore->setText("  Score");
    Affiscore = new QLCDNumber(this);
    Affiscore->setGeometry(450,20,50,20);
    Affiscore->display(jeu.scoreactuel());
    Affiscore->setStyleSheet("background-color:black");
}

void PacmanWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    list<Fantome>::const_iterator itFantome;
    list<point>::const_iterator itpoint;
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


    // Dessine les points (important de le mettre avant les fantomes et pacman sinon superposition non voulue)
    for (itpoint=jeu.points.begin(); itpoint!=jeu.points.end(); itpoint++)
        painter.drawPixmap(itpoint->getPosX()*largeurCase, itpoint->getPosY()*hauteurCase, pixmappoint);


    // Dessine les fantomes
    for (itFantome=jeu.fantomes.begin(); itFantome!=jeu.fantomes.end(); itFantome++)
        painter.drawPixmap(itFantome->getPosX()*largeurCase, itFantome->getPosY()*hauteurCase, pixmapFantome);

	// Dessine Pacman en fonction de la touche appuyée pour le tourner dans la bonne direction

	if (jeu.PosPac==BAS)
    {
        painter.drawPixmap(jeu.getPacmanX()*largeurCase, jeu.getPacmanY()*hauteurCase, pixmapPacmanB);
    }
    else if (jeu.PosPac==HAUT)
    {
        painter.drawPixmap(jeu.getPacmanX()*largeurCase, jeu.getPacmanY()*hauteurCase, pixmapPacmanH);
    }
    else if (jeu.PosPac==GAUCHE)
    {
        painter.drawPixmap(jeu.getPacmanX()*largeurCase, jeu.getPacmanY()*hauteurCase, pixmapPacmanG);
    }
    else if (jeu.PosPac==DROITE)
    {
        painter.drawPixmap(jeu.getPacmanX()*largeurCase, jeu.getPacmanY()*hauteurCase, pixmapPacmanD);
    }

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
    Affiscore->display(jeu.scoreactuel());
    update();
}
