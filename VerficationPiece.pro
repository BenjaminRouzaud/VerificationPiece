QT += widgets core gui

SOURCES += \
    main.cpp \
    BarTitreFenetre.cpp \
    FenetreValidation.cpp \
    BoutonTitre.cpp

HEADERS += \
    BarTitreFenetre.h \
    FenetreValidation.h \
    BoutonTitre.h

# QWT
INCLUDEPATH += /home/brouzaud/SOURCE/qwt-6.1-other/src
LIBS += -L/home/brouzaud/SOURCE/qwt-6.1-other/lib -lqwt

DISTFILES +=
