#ifndef BOUTONTITRE
#define BOUTONTITRE

#include <QtWidgets>

class BoutonTitre : public QAbstractButton {
    Q_OBJECT

    public:
    enum TypeBouton{
        BOUTON_MINIMIZE, BOUTON_MAXIMAZE, BOUTON_CLOSE
    };

    BoutonTitre(TypeBouton type, QWidget *parent = 0);
     ~BoutonTitre();

    protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent (QPaintEvent *event);
    void enterEvent       (QEvent      *event);
    void leaveEvent       (QEvent      *event);
    void mousePressEvent  (QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    private:
    enum EtatBouton{
        ETAT_NORMAL, ETAT_HOVERED, ETAT_CLIQUE
    };

    TypeBouton typeBouton;
    EtatBouton etat;
    QPixmap *boutonNormal;
    QPixmap *boutonHovered;
    QPixmap *boutonCliquer;

    void InitPixmaps();
    void InitPixmap(QPixmap **pixmap);
    void InitMinimize();
    void InitMaximize();
    void InitClose();
};

#endif // BOUTONTITRE

