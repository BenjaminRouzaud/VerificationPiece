#ifndef BARTITREFENETRE_H
#define BARTITREFENETRE_H

#include <QtWidgets>
#include "BoutonTitre.h"

class BarTitreFenetre : public QWidget{
    Q_OBJECT

    public:
    BarTitreFenetre(QWidget* parent = 0);
    ~BarTitreFenetre();

    protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    public slots:
    void UpdateWindowTitle();
    void Minimized();
    void Maximized();
    void Quit     ();


    private:
    QPixmap *cache;
    QLabel *titre;
    BoutonTitre *minimize;
    BoutonTitre *maximize;
    BoutonTitre *exit;
    QHBoxLayout *layoutBouton;
    QPoint diff;

};

#endif // BARTITREFENETRE_H

