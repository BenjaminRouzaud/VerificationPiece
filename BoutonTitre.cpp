#include "BoutonTitre.h"

BoutonTitre::BoutonTitre(TypeBouton type, QWidget *parent) : QAbstractButton(parent), typeBouton (type), etat (ETAT_NORMAL), boutonNormal (NULL), boutonHovered(NULL), boutonCliquer(NULL){

}

BoutonTitre::~BoutonTitre(){
    delete boutonNormal;
    delete boutonHovered;
    delete boutonCliquer;
}

void BoutonTitre::resizeEvent(QResizeEvent *event){
    Q_UNUSED(event);

     InitPixmaps();
}

void BoutonTitre::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QPainter painter(this);

    if (isEnabled()){
        switch(etat){
            case ETAT_NORMAL:
                if (boutonNormal !=NULL) painter.drawPixmap(0,0,*boutonNormal);
            break;
            case ETAT_HOVERED:
                if(boutonHovered !=NULL) painter.drawPixmap(0,0, *boutonHovered);
            break;
            case ETAT_CLIQUE:
                if (boutonCliquer !=NULL) painter.drawPixmap(0,0, *boutonCliquer);
            break;
           }
     }
    else{
        if (boutonNormal != NULL) painter.drawPixmap(0,0, *boutonNormal);
     }
}


void BoutonTitre::InitPixmaps(){
    InitPixmap(&boutonNormal);
    InitPixmap(&boutonHovered);
    InitPixmap(&boutonCliquer);

    switch(typeBouton){
        case BOUTON_MINIMIZE:
            InitMinimize();
        break;
        case BOUTON_MAXIMAZE:
            InitMaximize();
        break;
        case BOUTON_CLOSE:
            InitClose();
        break;
    }
}

void BoutonTitre::InitPixmap(QPixmap **pixmap){
    delete *pixmap;

    *pixmap = new QPixmap (size());

    (*pixmap)->fill(Qt::transparent);
}

void BoutonTitre::InitMinimize(){
    QPolygon border;

    border << QPoint(          0,            4)
           << QPoint(          4,            0)
           << QPoint(width() - 1,            0)
           << QPoint(width() - 1, height() - 1)
           << QPoint(          0, height() - 1);

    QPolygon symbol;

     symbol << QPoint(          4, height() - 8)
                << QPoint(width() - 4, height() - 8)
                << QPoint(width() - 4, height() - 4)
                << QPoint(          4, height() - 4);

     QColor gradientStart(  0,   0,   0,   0);
      QColor gradientEnd  (  0,   0,   0, 220);

      QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
      linearGrad.setColorAt(0, gradientStart);
      linearGrad.setColorAt(1, gradientEnd  );

      QLinearGradient invertlinearGrad(QPointF(0, 0), QPointF(0, height()));
      invertlinearGrad.setColorAt(0, gradientEnd  );
      invertlinearGrad.setColorAt(1, gradientStart);

      QPainter painter;

      painter.begin(boutonNormal);

      painter.setPen  (QPen(Qt::black   ));
      painter.setBrush(QBrush(linearGrad));

      painter.drawPolygon(border);

      painter.setPen  (Qt::NoPen        );
      painter.setBrush(QBrush(Qt::black));

      painter.drawPolygon(symbol);

      painter.end();

      painter.begin(boutonHovered);

      painter.setPen  (QPen  (Qt::black ));
      painter.setBrush(QBrush(linearGrad));

      painter.drawPolygon(border);

      painter.setPen  (Qt::NoPen        );
      painter.setBrush(QBrush(Qt::white));

      painter.drawPolygon(symbol);

      painter.end();

      painter.begin(boutonCliquer);

      painter.setPen  (QPen  (Qt::black       ));
      painter.setBrush(QBrush(invertlinearGrad));

      painter.drawPolygon(border);

      painter.setPen  (Qt::NoPen        );
      painter.setBrush(QBrush(Qt::white));

      painter.drawPolygon(symbol);

      painter.end();

}

void BoutonTitre::InitMaximize()
{
  /********** Button's border **********/
  QPolygon border;

  border << QPoint(          0,            0)
         << QPoint(width() - 5,            0)
         << QPoint(width() - 1,            4)
         << QPoint(width() - 1, height() - 1)
         << QPoint(          0, height() - 1);

  /********** Button's symbol **********/
  QPolygon symbol1, symbol2;

  symbol1 << QPoint(          4, 4)
          << QPoint(width() - 4, 4)
          << QPoint(width() - 4, 8)
          << QPoint(          4, 8);

  symbol2 << QPoint(          4,            8)
          << QPoint(width() - 4,            8)
          << QPoint(width() - 4, height() - 4)
          << QPoint(          4, height() - 4);
  /*************************************/

  QColor gradientStart(  0,   0,   0,   0);
  QColor gradientEnd  (  0,   0,   0, 220);

  QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
  linearGrad.setColorAt(0, gradientStart);
  linearGrad.setColorAt(1, gradientEnd  );

  QLinearGradient invertlinearGrad(QPointF(0, 0), QPointF(0, height()));
  invertlinearGrad.setColorAt(0, gradientEnd  );
  invertlinearGrad.setColorAt(1, gradientStart);

  QPainter painter;

  /********** Normal **********/
  painter.begin(boutonNormal);

  painter.setPen  (QPen(Qt::black   ));
  painter.setBrush(QBrush(linearGrad));

  painter.drawPolygon(border);

  painter.setPen  (QPen  (Qt::black));
  painter.setBrush(QBrush(Qt::black));

  painter.drawPolygon(symbol1);

  painter.setPen  (QPen(Qt::black));
  painter.setBrush(Qt::NoBrush    );

  painter.drawPolygon(symbol2);

  painter.end();
  /****************************/

  /********** Hovered **********/
  painter.begin(boutonHovered);

  painter.setPen  (QPen  (Qt::black       ));
  painter.setBrush(QBrush(linearGrad));

  painter.drawPolygon(border);

  painter.setPen  (QPen  (Qt::white));
  painter.setBrush(QBrush(Qt::white));

  painter.drawPolygon(symbol1);

  painter.setPen  (QPen(Qt::white));
  painter.setBrush(Qt::NoBrush    );

  painter.drawPolygon(symbol2);

  painter.end();
  /*****************************/

  /********** Clicked **********/
  painter.begin(boutonCliquer);

  painter.setPen  (QPen  (Qt::black ));
  painter.setBrush(QBrush(invertlinearGrad));

  painter.drawPolygon(border);

  painter.setPen  (QPen  (Qt::white));
  painter.setBrush(QBrush(Qt::white));

  painter.drawPolygon(symbol1);

  painter.setPen  (QPen(Qt::white));
  painter.setBrush(Qt::NoBrush    );

  painter.drawPolygon(symbol2);

  painter.end();
  /*****************************/
}

void BoutonTitre::InitClose()
{
  /********** Button's border **********/
  QPolygon border;

  border << QPoint(          0,            4)
         << QPoint(          4,            0)
         << QPoint(width() - 5,            0)
         << QPoint(width() - 1,            4)
         << QPoint(width() - 1, height() - 5)
         << QPoint(width() - 5, height() - 1)
         << QPoint(          4, height() - 1)
         << QPoint(          0, height() - 5);
  /*************************************/

  /********** Button's symbol **********/
  QLine symbol1(QPoint(          4, 4), QPoint(width() - 5, height() - 5));
  QLine symbol2(QPoint(width() - 5, 4), QPoint(          4, height() - 5));
  /*************************************/

  QColor gradientStart(  0,   0,   0,   0);
  QColor gradientEnd  (  0,   0,   0, 220);

  QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
  linearGrad.setColorAt(0, gradientStart);
  linearGrad.setColorAt(1, gradientEnd  );

  QLinearGradient invertlinearGrad(QPointF(0, 0), QPointF(0, height()));
  invertlinearGrad.setColorAt(0, gradientEnd  );
  invertlinearGrad.setColorAt(1, gradientStart);

  QPainter painter;

  /********** Normal **********/
  painter.begin(boutonNormal);

  painter.setPen  (QPen(Qt::black   ));
  painter.setBrush(QBrush(linearGrad));

  painter.drawPolygon(border);

  painter.setPen(QPen(QBrush(Qt::black), 2.0));

  painter.drawLine(symbol1);
  painter.drawLine(symbol2);

  painter.end();
  /****************************/

  /********** Hovered **********/
  painter.begin(boutonHovered);

  painter.setPen  (QPen  (Qt::black ));
  painter.setBrush(QBrush(linearGrad));

  painter.drawPolygon(border);

  painter.setPen(QPen(QBrush(Qt::white), 2.0));

  painter.drawLine(symbol1);
  painter.drawLine(symbol2);

  painter.end();
  /*****************************/

  /********** Clicked **********/
  painter.begin(boutonCliquer);

  painter.setPen  (QPen  (Qt::black       ));
  painter.setBrush(QBrush(invertlinearGrad));

  painter.drawPolygon(border);

  painter.setPen(QPen(QBrush(Qt::white), 2.0));

  painter.drawLine(symbol1);
  painter.drawLine(symbol2);

  painter.end();
  /*****************************/
}


void BoutonTitre::enterEvent(QEvent *event)
{
  Q_UNUSED(event);

  etat = ETAT_HOVERED;

  update();
}

void BoutonTitre::leaveEvent(QEvent *event)
{
  Q_UNUSED(event);

  etat = ETAT_NORMAL;

  update();
}

void BoutonTitre::mousePressEvent(QMouseEvent *event)
{
  QAbstractButton::mousePressEvent(event);

  etat = ETAT_CLIQUE;

  update();
}

void BoutonTitre::mouseReleaseEvent(QMouseEvent *event)
{
  QAbstractButton::mouseReleaseEvent(event);

  if(underMouse()) etat = ETAT_HOVERED;
  else             etat = ETAT_NORMAL;

  update();
}
