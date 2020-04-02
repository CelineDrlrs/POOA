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
    if (pixmapCoeur.load("./data/coeur.bmp")==false)
    {
        cout<<"Impossible d'ouvrir coeur.bmp"<<endl;
        exit(-1);
    }
    if (pixmapGameOver.load("./data/gameover.bmp")==false)
    {
        cout<<"Impossible d'ouvrir gameover.bmp"<<endl;
        exit(-1);
    }
    if (pixmapVictoire.load("./data/victoire.bmp")==false)
    {
        cout<<"Impossible d'ouvrir victoire.bmp"<<endl;
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

    //Bouton rejouer
    PacmanButton *btnrejouer = new PacmanButton(this);
    btnrejouer->setFixedSize(70,32);
    btnrejouer->move(400,0);
    btnrejouer->setText("Rejouer");
    btnrejouer->setFont(QFont("Segoe UI"));

    //connection à la méthode
    connect(btnrejouer, PacmanButton::clicked, this, PacmanWindow::rejouer);

    //Bouton mode INSA
    PacmanButton *btninsa = new PacmanButton(this);
    btninsa->setFixedSize(70,32);
    btninsa->move(500,0);
    btninsa->setText("Mode INSA");
    btninsa->setFont(QFont("Segoe UI"));

    //connection à la méthode
    connect(btninsa, PacmanButton::clicked, this, PacmanWindow::insa);


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
    Tagscore->setFont(QFont("Segoe UI"));
    Tagscore->move(270,35);
    Affiscore = new QLCDNumber(this);
    Affiscore->setGeometry(400,10,50,20);
    Affiscore->display(jeu.scoreactuel());
    Affiscore->setStyleSheet("background-color:black");
    Affiscore->move(320, 35);
}

void PacmanWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(jeu.getnbvie()>0)                                // On teste si le joueur a encore des vies
    {
        list<Fantome>::const_iterator itFantome;
        list<point>::const_iterator itpoint;
        list<gum>::const_iterator itgum;
        int x, y ;

        //Fond du jeu en noir
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

        // Dessine les coeurs
                int i;
                for(i=1;i<=jeu.getnbvie();i++)
                {
                    painter.drawPixmap(240 + i*32, 0, pixmapCoeur);     // On affiche les coeurs autant de fois que le ou les joueurs ont de vie en les décalant pour chacun
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

        //Condition d'affichage de la victoire
        if (jeu.gagne()==true)
        {
            painter.drawPixmap(0, 70, pixmapVictoire); //si on gagne, l'image de la vitoire apparaît

        }

    }
    else
    {
        painter.drawPixmap(50, 70, pixmapGameOver);      // Si toutes les vies sont épuisées, l'image de Game Over apparait à la place du terrain
    }
}

void PacmanWindow::keyPressEvent(QKeyEvent *event) //Blocage des mouvements du pacman lorsque le jeu est gagné
{
    if (event->key()==Qt::Key_Left && jeu.gagne()!=true)
        jeu.deplacePacman(GAUCHE);
    else if (event->key()==Qt::Key_Right && jeu.gagne()!=true)
        jeu.deplacePacman(DROITE);
    else if (event->key()==Qt::Key_Up && jeu.gagne()!=true)
        jeu.deplacePacman(HAUT);
    else if (event->key()==Qt::Key_Down && jeu.gagne()!=true)
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

void PacmanWindow::ajoutfantome()       //Méthode associée au bouton "ajouter fantome".
{
    int x, y;
    do                                      // Les fantomes sont placés aléatoirement sur des cases valides (hors des murs)
    {
        x = rand()%(jeu.getNbCasesX());
        y = rand()%(jeu.getNbCasesY());
    } while (!jeu.posValide(x,y));

    jeu.fantomes.push_back(Fantome(x,y));       //Une fois des coordonnées valides trouvées, le fantôme est ajouté à la liste

}

void PacmanWindow::retirefantome()      //Méthode connectée au bouton "supprimer fantome"
{
    if(jeu.fantomes.size()!=0)              //On fait attention à ce que la liste ne soit pas déjà vide avant de chercher à retirer un fantome supplémentaire, sinon, le programme plante
     {
         jeu.fantomes.pop_back();
     }
}

void PacmanWindow::rejouer()                 //Méthode connectée au bouton "rejouer", le score est remis à 0 et le jeu est réinitialisé
{
    //jeu.scoreactuel(0);
    jeu.init();
}

void PacmanWindow::insa()                 //Map INSA
{
    jeu.insa();
}
