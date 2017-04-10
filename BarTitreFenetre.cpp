
#include "BarTitreFenetre.h"

BarTitreFenetre::BarTitreFenetre(QWidget *parent) : QWidget(parent), cache(NULL){

    this->setFixedHeight(33);

     titre = new QLabel(this);

     titre->setStyleSheet("color: black; font-family: 'Gabriela', serif; font-weight: bold; font-size: 14px;  text-align: center;");

    minimize = new BoutonTitre(BoutonTitre::BOUTON_MINIMIZE,this);
    maximize = new BoutonTitre(BoutonTitre::BOUTON_MAXIMAZE,this);
    exit = new BoutonTitre(BoutonTitre::BOUTON_CLOSE,this);

    layoutBouton =  new QHBoxLayout(this);

    int size = 20;
    minimize->setFixedSize(size,size);
    maximize->setFixedSize(size,size);
    exit->setFixedSize(size,size);

    layoutBouton->addWidget(titre);
    layoutBouton->addWidget(minimize);
    layoutBouton->addWidget(maximize);
    layoutBouton->addWidget(exit);

    this->setLayout(layoutBouton);


     UpdateWindowTitle();

     connect(minimize, SIGNAL(clicked  ()), this, SLOT  (Minimized()));

      connect(maximize, SIGNAL(clicked  ()), this, SLOT  (Maximized()));

      connect(exit   , SIGNAL(clicked  ()), this, SLOT  (Quit()));


}

BarTitreFenetre::~BarTitreFenetre(){

}

void BarTitreFenetre::resizeEvent(QResizeEvent *event)
{
      Q_UNUSED(event);
      static int number = 0;

      if(cache != NULL)
            delete cache; // Remove old cache

      number ++;
      cache = new QPixmap(size());  // Create a cache with same size as the widget

      cache->fill(Qt::transparent);  // Create a the transparent background

      QPainter painter(cache); // Start painting the cache

      QColor grey    (240, 239, 240, 255);
      QColor gradientStart(  200,   200,   200,   0);
      QColor gradientEnd  (  255,   255,  255, 220);

      QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
      linearGrad.setColorAt(0, gradientStart);
      linearGrad.setColorAt(1, gradientEnd);
      titre->move(width()/2.5, 4);
      titre->resize(width() - 116, 29);
      /********** Title bar's frame **********/
      QPolygon frame;

      frame << QPoint(4,  4)
            << QPoint(width() - 4,  4)
            << QPoint(width() - 4, 32)
            << QPoint(          4, 32)
            << QPoint(          4, 20);

      painter.setPen  (QPen  (grey ));
      painter.setBrush(QBrush(linearGrad));

      painter.drawPolygon(frame);
      /***************************************/

      /********** Title bar's buttons area **********/
      QPolygon buttons;

      buttons << QPoint(width()- 87 ,  4)
              << QPoint(width() -  4,  4)
              << QPoint(width() -  4, 32)
              << QPoint(width() - 88, 32)
              << QPoint(width() - 88, 12);

      painter.setPen  (QPen  (grey));
      painter.setBrush(QBrush(grey));

      painter.drawPolygon(buttons);

      /**********************************************/
}

void BarTitreFenetre::paintEvent(QPaintEvent *event)
{
      Q_UNUSED(event);

      if(cache != NULL) {
        QPainter painter(this);

        painter.drawPixmap(0, 0, *cache);
     }
}


void BarTitreFenetre::UpdateWindowTitle(){

    titre->setText(window()->windowTitle());
}

void BarTitreFenetre::Minimized(){
  window()->showMinimized();
}

void BarTitreFenetre::Maximized(){
  if(window()->windowState() == Qt::WindowMaximized) {
     window()->showNormal();
  }
  else{
    window()->showMaximized();
  }
}

void BarTitreFenetre::Quit(){
  qApp->quit();
}


void BarTitreFenetre::mousePressEvent(QMouseEvent *event){
    diff = event->pos();

    setCursor(QCursor(Qt::SizeAllCursor));
}

void BarTitreFenetre::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event);

    setCursor(QCursor(Qt::ArrowCursor));
}

void BarTitreFenetre::mouseMoveEvent(QMouseEvent *event){
    QPoint p = event->globalPos();

    window()->move(p-diff);
}

