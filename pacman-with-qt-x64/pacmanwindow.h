#ifndef PACMANWINDOW_H
#define PACMANWINDOW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.h"

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
    QPixmap pixmapPacman, pixmapFantome, pixmapMur;
    PacmanButton *btnajout/*,*btnsuppr, *btnquitter*/;       // déclaration des boutons de l'interface

  public:
    PacmanWindow(QWidget *pParent=0, Qt::WindowFlags flags=0);
    void handleTimer();

  protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void ajoutfantome();
//    void retirefantome();
//    void quitte();
};



#endif
