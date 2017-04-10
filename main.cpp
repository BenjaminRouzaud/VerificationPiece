#include <QApplication>
#include "FenetreValidation.h"
#include <QtWidgets>
#include <QDebug>

int main (int argc, char *argv[]){

    QApplication app(argc,argv);

    FenetreValidation fenetre;
    fenetre.show();

        return app.exec();
}

