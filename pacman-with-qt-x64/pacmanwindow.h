#ifndef PACMANWINDOW_H
#define PACMANWINDOW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.h"

typedef enum {PLAY, PAUSE} Etat;

// déclaration d'une nouvelle classe héritant de QPushButton pour que les touches soient actives en même temps que les boutons
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
    QPixmap pixmapPacmanD, pixmapPacmanG, pixmapPacmanH, pixmapPacmanB, pixmapFantome, pixmapMur, pixmappoint, pixmapGum, pixmapFantBleu, pixmapCoeur, pixmapGameOver, pixmapVictoire, pixmapAjout, pixmapJouer, pixmapQuitter, pixmapSuppr ;
    PacmanButton *btnajout,*btnsuppr, *btnrejouer, *btnquitter;
    Etat Etat;

  public:
    PacmanWindow(QWidget *pParent=0, Qt::WindowFlags flags=0);
    void handleTimer();

  protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void ajoutfantome();
    void retirefantome();
    void rejouer();
    void quitter();
};

#endif
