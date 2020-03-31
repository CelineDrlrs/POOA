#ifndef PACMANWINDOW_H
#define PACMANWINDOW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.h"

// d�claration d'une nouvelle classe h�ritant de QPushButton pour que les touches soient actives en m�me temps que les boutons

class PacmanButton : public QPushButton
{
  public:
    void keyPressEvent(QKeyEvent *);
    PacmanButton(QWidget* parent):QPushButton(parent){};
};

class PacmanWindow : public QFrame
{
  protected:
    Jeu jeu;
    QLCDNumber *Affiscore;
    QPixmap pixmapPacmanD, pixmapPacmanG, pixmapPacmanH, pixmapPacmanB, pixmapFantome, pixmapMur, pixmappoint ;
    PacmanButton *btnajout,*btnsuppr;

  public:
    PacmanWindow(QWidget *pParent=0, Qt::WindowFlags flags=0);
    void handleTimer();

  protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void ajoutfantome();
    void retirefantome();
};

#endif
