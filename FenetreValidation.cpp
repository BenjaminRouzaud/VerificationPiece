#include "FenetreValidation.h"

#include <stdexcept>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_zoneitem.h>


class Zoomer: public QwtPlotZoomer
{
public:
    Zoomer( QWidget *canvas ):
        QwtPlotZoomer( canvas )
    {
        setRubberBandPen( QColor( Qt::gray ) );
        setTrackerMode( QwtPlotPicker::AlwaysOn );
    }

protected:
    virtual QwtText trackerTextF( const QPointF &pos ) const
    {
        const int dx = pos.x() ;
        const int dy = pos.y();

        QString s;
         s +="( "+QString::number(dx) + "," +QString::number(dy) +")" ;
        QwtText text( s );
        text.setColor( Qt::black );

        QColor c = rubberBandPen().color();
        text.setBorderPen( QPen( c ) );
        text.setBorderRadius( 6 );
        c.setAlpha( 170 );
        text.setBackgroundBrush( c );

        return text;
    }
};

double temp = 0;
int nbErreur = 0;

FenetreValidation::FenetreValidation() : QWidget(){

    this->resize(1024, 614);
    this->setWindowTitle("Validation des pièces");
    this->setWindowFlags(Qt::FramelessWindowHint);


    /*Layout principal */
    mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    sizeGrip = new QSizeGrip(this);

    titreFenetre = new BarTitreFenetre(this);
    titreFenetre->setFixedWidth(width());

    mainLayout->addWidget(titreFenetre);

    layoutTitre = new QHBoxLayout;
    QLabel *titreApp = new QLabel ("Vérification des pièces valables", this);
     titreApp->setStyleSheet("margin-left : 50; margin-top: 10; margin-bottom: 10; color: black; font-family: 'Gabriela', serif; font-weight: bold; font-size: 14px;");

    boutonChoixFichier = new QPushButton("Ouvrir un fichier .csv",this);
    boutonChoixFichier->setFixedSize(120,20);

    QSpacerItem *spacerBoutonChoix= new QSpacerItem(25,5, QSizePolicy::Minimum, QSizePolicy::Minimum);

    layoutTitre->addWidget(titreApp);
    layoutTitre->addWidget(boutonChoixFichier,Qt::AlignLeft);
    layoutTitre->addSpacerItem(spacerBoutonChoix);
    mainLayout->addLayout(layoutTitre);

    layoutGraphe = new QHBoxLayout;
    myPlot = new QwtPlot();

    QSpacerItem *spacerPlotGauche= new QSpacerItem(10,20, QSizePolicy::Minimum, QSizePolicy::Minimum);
    QSpacerItem *spacerPlotDroite= new QSpacerItem(50,20, QSizePolicy::Minimum, QSizePolicy::Minimum);
    myPlot->setCanvasBackground(Qt::white);
    myPlot->setAutoReplot(true);
    myPlot->setAxisScale(QwtPlot::xBottom, 0,80);
    myPlot->setAxisScale(QwtPlot::yLeft, -10,10);

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->attach( myPlot );

    layoutGraphe->addItem(spacerPlotGauche);
    layoutGraphe->addWidget(myPlot);
    layoutGraphe->addItem(spacerPlotDroite);
    mainLayout->addLayout(layoutGraphe);


    layoutCourbe = new QHBoxLayout;
    QSpacerItem *spaceCourbeGauche = new QSpacerItem(50,20, QSizePolicy::Minimum, QSizePolicy::Minimum);
    caseTheorique = new QCheckBox(this);
    caseTheorique->setEnabled(false);
    boutonTheorique = new QPushButton("théorique",this);
    boutonTheorique->setFixedSize(120,20);
    boutonTheorique->setEnabled(false);
    QSpacerItem *spaceCourbeEntre = new QSpacerItem(20,20, QSizePolicy::Minimum, QSizePolicy::Minimum);
    caseReel = new QCheckBox(this);
    caseReel->setEnabled(false);
    boutonPremierReel = new QPushButton("1ère Réel",this);
    boutonPremierReel->setFixedSize(120,20);
    boutonPremierReel->setEnabled(false);
    QSpacerItem *spaceCourbeEntreDeux = new QSpacerItem(20,20, QSizePolicy::Minimum, QSizePolicy::Minimum);
    boutonDeuxiemeReel = new QPushButton("2eme Réel",this);
    boutonDeuxiemeReel->setFixedSize(120,20);
    boutonDeuxiemeReel->setEnabled(false);
    QSpacerItem *spaceCourbeDroit = new QSpacerItem(550,20, QSizePolicy::Minimum, QSizePolicy::Minimum);
    QSpacerItem *spaceVertical = new QSpacerItem(10, 50, QSizePolicy::Minimum, QSizePolicy::Minimum);

    layoutCourbe->addItem(spaceCourbeGauche);
    layoutCourbe->addWidget(caseTheorique);
    layoutCourbe->addWidget(boutonTheorique);
    layoutCourbe->addItem(spaceCourbeEntre);
     layoutCourbe->addWidget(caseReel);
    layoutCourbe->addWidget(boutonPremierReel);
    layoutCourbe->addItem(spaceCourbeEntreDeux);
    layoutCourbe->addWidget(boutonDeuxiemeReel);
    layoutCourbe->addItem(spaceCourbeDroit);
    layoutCourbe->addItem(spaceVertical);

//    remplirTheorique(myPlot);

//    remplirDeuxiemeReel(myPlot);
    Zoomer *myZoom = new Zoomer (myPlot->canvas());


    afficherErreur(10,20);

    layoutSlider = new QHBoxLayout;
    mySlider = new QSlider(Qt::Horizontal, this);
    mySlider->setRange(-20,20);
    mySlider->setValue(0);
    mySlider->setFixedWidth(850);

     QSpacerItem *spaceSlider = new QSpacerItem(115,20, QSizePolicy::Minimum, QSizePolicy::Minimum);

    layoutSlider->addWidget(mySlider);
    layoutSlider->addSpacerItem(spaceSlider);
    mainLayout->addLayout(layoutSlider);
    mainLayout->addLayout(layoutCourbe);

    this->setLayout(mainLayout);

    connect(this, SIGNAL(WindowTitleChanged()), titreFenetre, SLOT(UpdateWindowTitle()));
    connect(boutonChoixFichier, SIGNAL(clicked()), this, SLOT(choixFichier()));
    connect(caseTheorique, SIGNAL(stateChanged(int)), this, SLOT(changerVisibility()));
    connect(boutonTheorique, SIGNAL(clicked()), this, SLOT(ouvrirDialogueTheorique()));
    connect(boutonPremierReel, SIGNAL(clicked()), this, SLOT(ouvrirDialogueReel()));
    connect(boutonDeuxiemeReel, SIGNAL(clicked()), this, SLOT(ouvrirDialogueDeuxiemeReel()));
    connect(mySlider, SIGNAL(valueChanged(int)), this, SLOT(decalerCourbe()));
    this->installEventFilter(this);
}

FenetreValidation::~FenetreValidation(){
    delete mainLayout;
    delete titreFenetre;
    delete sizeGrip;
    delete layoutTitre;
    delete layoutGraphe;
    delete layoutCourbe;
    delete boutonPremierReel;
    delete boutonDeuxiemeReel;
    delete boutonTheorique;
    delete curveTheoriqueHaut;
    delete curvePremierReel;
    delete curveDeuxiemeReel;
    delete myPlot;
    delete myZoomer;
}

void FenetreValidation::showEvent(QShowEvent *event)
{
  Q_UNUSED(event);

  centerOnScreen();
}

void FenetreValidation::centerOnScreen(){

    QDesktopWidget screen;

    QRect screenGeom = screen.screenGeometry(this);

     int screenCenterX = screenGeom.center().x();
     int screenCenterY = screenGeom.center().y();

      move(screenCenterX - width () / 2, screenCenterY - height() / 2);

}

void FenetreValidation::paintEvent(QPaintEvent *event){
    QPainter painter(this);


    QColor gradientStart(  190,   190,   190,  220);
    QColor gradientEnd  (  130,   130,  130, 0);

    QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
    linearGrad.setColorAt(0, gradientStart);
    linearGrad.setColorAt(1, gradientEnd);

    painter.setBrush(QBrush(linearGrad));
    painter.setPen(Qt::NoPen);

    painter.drawRect(0,0, width(), height());
}

void FenetreValidation::setWindowTitle(const QString &titre){
    QWidget::setWindowTitle(titre);

    emit WindowTitleChanged();
}

void FenetreValidation::resizeEvent(QResizeEvent *event){
    sizeGrip->move(width()-32, height()-32);
    sizeGrip->resize(32,32);

}

bool FenetreValidation::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *c = dynamic_cast<QKeyEvent *>(event);
        if(c && c->key() == Qt::Key_Escape)
        {
            QCoreApplication::exit(0);
        }
    }
    return false;
}


void FenetreValidation::ouvrirDialogueTheorique(){

    QColor couleur = QColorDialog::getColor(Qt::white, this);

    QPalette palette;
    palette.setColor(QPalette::Button, couleur);
    boutonTheorique->setPalette(palette);
    curveTheoriqueHaut->setPen(couleur,3);
    curveTheoriqueBas->setPen(couleur,3);
    myPlot->replot();

}

void FenetreValidation::ouvrirDialogueReel(){

    QColor couleur = QColorDialog::getColor(Qt::white, this);

    QPalette palette;
    palette.setColor(QPalette::Button, couleur);
    boutonPremierReel->setPalette(palette);
    curvePremierReel->setPen(couleur, 3);
    curveDeuxiemeReel->setPen(couleur,3);
    myPlot->replot();

}

void FenetreValidation::ouvrirDialogueDeuxiemeReel(){

    QColor couleur = QColorDialog::getColor(Qt::white, this);

    QPalette palette;
    palette.setColor(QPalette::Button, couleur);
    boutonDeuxiemeReel->setPalette(palette);
    curveDeuxiemeReel->setPen(couleur,3);
    myPlot->replot();

}

void FenetreValidation::choixFichier(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open .csv file"),
                                                    "/home",
                                                    tr("Csv (*.csv)"));

    lireFichier(fileName);
    remplirTheorique(myPlot);
}

void FenetreValidation::remplirTheorique(QwtPlot *plot){
    curveTheoriqueHaut = new QwtPlotCurve;
    curveTheoriqueHaut->setPen(Qt::red, 3);
    curveTheoriqueBas =  new QwtPlotCurve;
    curveTheoriqueBas->setPen(Qt::red, 3);

    curvePremierReel = new QwtPlotCurve;
    curveDeuxiemeReel = new QwtPlotCurve;
    curvePremierReel->setPen(Qt::black, 3);
    curveDeuxiemeReel->setPen(Qt::black, 3);

    QPalette palette;
    palette.setColor(QPalette::Button, QColor(Qt::red));
    boutonTheorique->setPalette(palette);
    boutonTheorique->setEnabled(true);
    palette.setColor(QPalette::Button, QColor(Qt::white));
    boutonPremierReel->setPalette(palette);
    boutonPremierReel->setEnabled(true);
    caseTheorique->setEnabled(true);
    caseReel->setEnabled(true);

    float tmp3 = 0., axeX = 0., tmp2 = 0., tmp4=0., tmp5=0.;

    XReelHaut = new  QVector<double>;
    YReelHaut = new  QVector<double>;

    XReelBas  = new  QVector<double>;
    YReelBas  = new  QVector<double>;

     XTheoriqueHaut = new QVector<double>;
     YTheoriqueHaut = new  QVector<double>;

     XTheoriqueBas = new QVector<double>;
     YTheoriqueBas = new  QVector<double>;

     if (XTheoriqueHaut->length() > 0 )
         XTheoriqueHaut->clear();

     if (XTheoriqueHaut->length() > 0 )
         YTheoriqueHaut->clear();

     if (XTheoriqueBas->length() > 0 )
         XTheoriqueBas->clear();

     if (YTheoriqueBas->length() > 0 )
         YTheoriqueBas->clear();

      for (int i = 0; i< listeAna14->length(); i++){
           tmp3 = tmp2;
           axeX = -1. * ((float)listeX1r0->value(i).toInt(false, 10) -(float) listeX1r0->value(0).toInt(false,10) )/10000.;
           tmp2= ((float)listeAna14->value(i).toInt(false,10) - 409) * 0.01692;
           if ((qAbs(tmp2) > 0.02) ){
               XTheoriqueHaut->append(axeX);
               XTheoriqueBas->append(axeX);
               YTheoriqueHaut->append(tmp2/2);
               YTheoriqueBas->append(-1*tmp2/2);
            }
           else if(qAbs(tmp3) > 0.02 ){
               XTheoriqueHaut->append(axeX);
               XTheoriqueBas->append(axeX);
               YTheoriqueHaut->append(tmp2/2);
               YTheoriqueBas->append(-1*tmp2/2);
           }
       }

       for (int i = 0; i< listeAna15->length(); i++){
         tmp5 = tmp4;
         axeX = -1. * ((float)listeX1r0->value(i).toInt(false, 10) -(float) listeX1r0->value(0).toInt(false,10) )/10000.;
         tmp4 = ((float)listeAna15->value(i).toInt(false,10) - 409) * 0.01692;
         if (qAbs(tmp4) > 0.02){
             XReelHaut->append(axeX);
             XReelBas->append(axeX);
             YReelHaut->append(tmp4/2);
             YReelBas->append(-1*tmp4/2);
         }
         else if(qAbs(tmp5) > 0.02 ){
             XReelHaut->append(axeX);
             XReelBas->append(axeX);
             YReelHaut->append(tmp4/2);
             YReelBas->append(-1*tmp4/2);
         }
     }
    curveTheoriqueHaut->setData(NULL);
    curveTheoriqueBas->setData(NULL);
    curvePremierReel->setData(NULL);
    curveDeuxiemeReel->setData(NULL);

    curveTheoriqueHaut->setSamples(XTheoriqueHaut->data(),YTheoriqueHaut->data(),XTheoriqueHaut->size());
    curveTheoriqueBas->setSamples(XTheoriqueBas->data(),YTheoriqueBas->data(),XTheoriqueBas->size());
    curvePremierReel->setSamples(XReelHaut->data(),YReelHaut->data(),XReelHaut->size());
    curveDeuxiemeReel->setSamples(XReelBas->data(),YReelBas->data(),XReelBas->size());

    myPlot->detachItems(QwtPlotItem::Rtti_PlotCurve);

    curveTheoriqueHaut->attach(myPlot);
    curveTheoriqueBas->attach(myPlot);

    curvePremierReel->attach(myPlot);
    curveDeuxiemeReel->attach(myPlot);
    myPlot->replot();

}

void FenetreValidation::remplirPremiereReel(QwtPlot *plot){

    curvePremierReel = new QwtPlotCurve;
    curveDeuxiemeReel = new QwtPlotCurve;
    curvePremierReel->setPen(Qt::black, 3);
    curveDeuxiemeReel->setPen(Qt::black, 3);


    XReelHaut = new  QVector<double>;
    YReelHaut = new  QVector<double>;
    XReelBas  = new  QVector<double>;
    YReelBas  = new  QVector<double>;
    XReelHaut->append(0);
    XReelHaut->append(0);
    XReelHaut->append(2);
    XReelHaut->append(10.5);
    XReelHaut->append(11);
    XReelHaut->append(41);

    YReelHaut->append(0);
    YReelHaut->append(0);
    YReelHaut->append( -3.75);
    YReelHaut->append( -5.75);
    YReelHaut->append( -5);
    YReelHaut->append( -4);

    XReelBas->append(0);
    XReelBas->append(0);
    XReelBas->append(2);
    XReelBas->append(10.5);
    XReelBas->append(11);
    XReelBas->append(41);

    YReelBas->append(0);
    YReelBas->append(0);
    YReelBas->append(3.75);
    YReelBas->append(5.75);
    YReelBas->append(5);
    YReelBas->append(4);

    curvePremierReel->setSamples(XReelHaut->data(),YReelHaut->data(),XReelHaut->size());
    curveDeuxiemeReel->setSamples(XReelBas->data(),YReelBas->data(),XReelBas->size());
    curvePremierReel->attach(plot);
    curveDeuxiemeReel->attach(plot);

}

void FenetreValidation::remplirDeuxiemeReel(QwtPlot *plot){

}

void FenetreValidation::decalerCourbe(){
    for (int i =0; i<XReelHaut->size();i++){
       XReelHaut->replace(i,XReelHaut->value(i)+ mySlider->value()-temp);
       XReelBas->replace(i,XReelBas->value(i)+ mySlider->value()-temp);
    }
    curvePremierReel->setSamples(XReelHaut->data(),YReelHaut->data(),XReelHaut->size());
    curveDeuxiemeReel->setSamples(XReelBas->data(),YReelBas->data(),XReelBas->size());
    temp = mySlider->value();
}


void FenetreValidation::afficherErreur(double x1, double x2){
       QwtPlotZoneItem *zone1 = new QwtPlotZoneItem;

       QColor error(  234,   113,   109,  220);
       zone1->setBrush(error);
       zone1->setInterval(x1,x2);
       zone1->setVisible( true );
       zone1->attach( myPlot );

}

void FenetreValidation::lireFichier(QString fileName){
    QStringList list;
    int valeurEana14 = 0;
    int valeurEana15 = 0;
    int valeurX1r0 = 0;
    listeAna14 = new QVector<QString>;
    listeAna15 = new  QVector<QString>;
    listeX1r0 = new  QVector<QString>;

      QFile file (fileName);


      if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
          throw std::logic_error("erreur");


      QTextStream stream(&file);

      while (!stream.atEnd()){
              QString line = stream.readLine();
              list = line.split(";");

              for (int i = 0; i < list.length(); i++){
                  if (list[i] != ""){
                      if (list[i] == "Eana14")
                          valeurEana14 = i ;
                      else if (list[i] == "Eana15")
                          valeurEana15 = i;
                      else if (list[i] == "x1r 0")
                            valeurX1r0 = i;
                    }
              }

              for (int j = valeurEana14; j < list.length(); j++){
                if ((list[j] != "") && (list[j].length() <10)){
                  if (j == valeurEana14)
                      listeAna14->append(list[valeurEana14]);
                  else if (j == valeurEana15)
                      listeAna15->append(list[j]);
                  else if (j == valeurX1r0)
                      listeX1r0->append(list[j]);
                }

              }
      }
      listeAna14->remove(0);
      listeAna15->remove(0);
      listeX1r0->remove(0);
}

void FenetreValidation::changerVisibility(){
    if(curveTheoriqueHaut->isVisible()){
        curveTheoriqueHaut->hide();
    }
    else{
        curveTheoriqueHaut->show();
    }

    if(curveTheoriqueBas->isVisible()){
        curveTheoriqueBas->hide();
    }
    else{
        curveTheoriqueBas->show();
    }
}
