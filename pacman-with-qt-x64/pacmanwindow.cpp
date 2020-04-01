#include <iostream>
#include "pacmanwindow.h"

using namespace std;

PacmanWindow::PacmanWindow(QWidget *pParent, Qt::WindowFlags flags):QFrame(pParent, flags)
{
    // Taille des cases en pixels
    int largeurCase, hauteurCase, decalage;
    decalage = 60 ;

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
   if (pixmapGum.load("./data/Gum.png")==false)
    {
        cout<<"Impossible d'ouvrir Gum.png"<<endl;
        exit(-1);
    }

   if (pixmapFantBleu.load("./data/FantBleu.png")==false)
    {
        cout<<"Impossible d'ouvrir FantBleu.png"<<endl;
        exit(-1);
    }

    //Bouton ajout d'un fantôme
    PacmanButton *btnajout = new PacmanButton(this);
    btnajout->resize(110,32);
    btnajout->setText("Ajouter un fantome");
    btnajout->setFont(QFont("Segoe UI"));

    //création de l'action
    connect(btnajout, PacmanButton::clicked, this, PacmanWindow::ajoutfantome);

    //Bouton supprimer un fantôme
    PacmanButton *btnsuppr = new PacmanButton(this);
    btnsuppr->resize(110,32);
    btnsuppr->move(122,0);
    btnsuppr->setText("Retirer un fantome");
    btnsuppr->setFont(QFont("Segoe UI"));

    //création de l'action
    connect(btnsuppr, PacmanButton::clicked, this, PacmanWindow::retirefantome);

    jeu.init();

    QTimer *timer = new QTimer(this);
    connect(timer, QTimer::timeout, this, PacmanWindow::handleTimer);
    timer->start(100);

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    resize(jeu.getNbCasesX()*largeurCase, decalage + jeu.getNbCasesY()*hauteurCase);


    // Affichage du score et du label "score" devant"

    QLabel *Tagscore = new QLabel(this);
    Tagscore->setStyleSheet("background-color:pink");
    Tagscore->setGeometry(400,10,50,20);
    Tagscore->setText("  Score");
    Affiscore = new QLCDNumber(this);
    Affiscore->setGeometry(450,10,50,20);
    Affiscore->display(jeu.scoreactuel());
    Affiscore->setStyleSheet("background-color:black");
}

void PacmanWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    list<Fantome>::const_iterator itFantome;
    list<point>::const_iterator itpoint;
    list<gum>::const_iterator itgum;
    int x, y ;

    //Fond du jeu en nois
    painter.fillRect(0, 0, 828, 828, Qt::black);
    painter.beginNativePainting();

    // Taille des cases en pixels
    int largeurCase, hauteurCase, decalage;

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();
    decalage = 60;

    // Dessine les cases
    for (y=0;y<jeu.getNbCasesY();y++)
        for (x=0;x<jeu.getNbCasesX();x++)
			if (jeu.getCase(x,y)==MUR)
                painter.drawPixmap(x*largeurCase,y*hauteurCase+decalage, pixmapMur);


    // Dessine les points (important de le mettre avant les fantomes et pacman sinon superposition non voulue)
    for (itpoint=jeu.points.begin(); itpoint!=jeu.points.end(); itpoint++) painter.drawPixmap(itpoint->getPosX()*largeurCase, decalage + itpoint->getPosY()*hauteurCase, pixmappoint);

    // Dessine les Gum
    for (itgum=jeu.gums.begin(); itgum!=jeu.gums.end(); itgum++) painter.drawPixmap(itgum->getPosX()*largeurCase, decalage + itgum->getPosY()*hauteurCase, pixmapGum);

    // Dessine les fantomes

    if (jeu.gumMiam == 1)
    {
        for (itFantome=jeu.fantomes.begin(); itFantome!=jeu.fantomes.end(); itFantome++) painter.drawPixmap(itFantome->getPosX()*largeurCase, decalage + itFantome->getPosY()*hauteurCase, pixmapFantBleu);

    }
    else
    {
        for (itFantome=jeu.fantomes.begin(); itFantome!=jeu.fantomes.end(); itFantome++) painter.drawPixmap(itFantome->getPosX()*largeurCase, decalage + itFantome->getPosY()*hauteurCase, pixmapFantome);
    }

	// Dessine Pacman en fonction de la touche appuyée pour le tourner dans la bonne direction

	if (jeu.PosPac==BAS)
    {
        painter.drawPixmap(jeu.getPacmanX()*largeurCase, decalage + jeu.getPacmanY()*hauteurCase, pixmapPacmanB);
    }
    else if (jeu.PosPac==HAUT)
    {
        painter.drawPixmap(jeu.getPacmanX()*largeurCase, decalage + jeu.getPacmanY()*hauteurCase, pixmapPacmanH);
    }
    else if (jeu.PosPac==GAUCHE)
    {
        painter.drawPixmap(jeu.getPacmanX()*largeurCase, decalage + jeu.getPacmanY()*hauteurCase, pixmapPacmanG);
    }
    else if (jeu.PosPac==DROITE)
    {
        painter.drawPixmap(jeu.getPacmanX()*largeurCase, decalage + jeu.getPacmanY()*hauteurCase, pixmapPacmanD);
    }
    else
    {
        painter.drawPixmap(jeu.getPacmanX()*largeurCase, decalage + jeu.getPacmanY()*hauteurCase, pixmapPacmanD);
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


void PacmanButton::keyPressEvent(QKeyEvent *e)
{
    if (parent()!=NULL)
        QCoreApplication::sendEvent(parent(), e);
}

void PacmanWindow::ajoutfantome()
{
    int x, y;
    do                                      // Les fantomes sont placés sur des cases valides, soit des cases qui ne sont pas des murs
    {
        x = rand()%(jeu.getNbCasesX());
        y = rand()%(jeu.getNbCasesY());
    } while (!jeu.posValide(x,y));

    jeu.fantomes.push_back(Fantome(x,y));       // une fois des coordonnées valides trouvées, le fantôme est ajouté à la liste

}

void PacmanWindow::retirefantome()
{
    if(jeu.fantomes.size()!=0)              // On fait attention à ce que la liste ne soit aps déjà vide avant de chercher à retirer un fantome supplémentaire, sinon, le programme plante
     {
         jeu.fantomes.pop_back();
     }
}
