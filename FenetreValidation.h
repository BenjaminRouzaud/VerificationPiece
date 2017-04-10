#ifndef FENETREVALIDATION_H
#define FENETREVALIDATION_H

#include <QApplication>
#include <QtWidgets>
#include "BarTitreFenetre.h"

class QwtPlot;
class QwtPlotCurve;
class QwtPlotZoomer;

class FenetreValidation : public QWidget{

    Q_OBJECT

    public:
    FenetreValidation();
    ~FenetreValidation();
     void setWindowTitle(const QString &titre );
     bool eventFilter(QObject *obj, QEvent *event);

    public slots:
    void ouvrirDialogueReel();
    void ouvrirDialogueTheorique();
    void ouvrirDialogueDeuxiemeReel();
    void choixFichier();
    void remplirTheorique(QwtPlot *plot);
    void remplirPremiereReel(QwtPlot *plot);
    void remplirDeuxiemeReel(QwtPlot *plot);
    void decalerCourbe();
    void afficherErreur(double x1, double x2);
    void lireFichier(QString fileName);
    void changerVisibility();

    signals:
    void WindowTitleChanged();

    protected:
    void showEvent(QShowEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    private:
    void centerOnScreen();
    QVBoxLayout *mainLayout;
    BarTitreFenetre *titreFenetre;
    QSizeGrip *sizeGrip;
    QHBoxLayout *layoutTitre;
    QHBoxLayout *layoutGraphe;
    QHBoxLayout *layoutCourbe;
    QHBoxLayout *layoutSlider;
    QPushButton *boutonChoixFichier;
    QPushButton *boutonPremierReel;
    QPushButton *boutonDeuxiemeReel;
    QPushButton *boutonTheorique;
    QwtPlotCurve *curveTheoriqueHaut;
    QwtPlotCurve *curveTheoriqueBas;
    QwtPlotCurve *curvePremierReel;
    QwtPlotCurve *curveDeuxiemeReel;
    QwtPlot  *myPlot;
    QwtPlotZoomer *myZoomer;
    QSlider *mySlider;
    QVector<double> *XTheoriqueHaut;
    QVector<double> *YTheoriqueHaut;
    QVector<double> *XTheoriqueBas;
    QVector<double> *YTheoriqueBas;
    QVector<double> *XReelHaut;
    QVector<double> *YReelHaut;
    QVector<double> *XReelBas;
    QVector<double> *YReelBas;
    QVector<QString> *listeAna14;
    QVector<QString> *listeAna15;
    QVector<QString> *listeX1r0;
    QCheckBox *caseTheorique;
    QCheckBox *caseReel;
 };

#endif // FENETREVALIDATION_H

