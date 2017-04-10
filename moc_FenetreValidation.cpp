/****************************************************************************
** Meta object code from reading C++ file 'FenetreValidation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "FenetreValidation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FenetreValidation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FenetreValidation_t {
    QByteArrayData data[19];
    char stringdata0[266];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FenetreValidation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FenetreValidation_t qt_meta_stringdata_FenetreValidation = {
    {
QT_MOC_LITERAL(0, 0, 17), // "FenetreValidation"
QT_MOC_LITERAL(1, 18, 18), // "WindowTitleChanged"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 18), // "ouvrirDialogueReel"
QT_MOC_LITERAL(4, 57, 23), // "ouvrirDialogueTheorique"
QT_MOC_LITERAL(5, 81, 26), // "ouvrirDialogueDeuxiemeReel"
QT_MOC_LITERAL(6, 108, 12), // "choixFichier"
QT_MOC_LITERAL(7, 121, 16), // "remplirTheorique"
QT_MOC_LITERAL(8, 138, 8), // "QwtPlot*"
QT_MOC_LITERAL(9, 147, 4), // "plot"
QT_MOC_LITERAL(10, 152, 19), // "remplirPremiereReel"
QT_MOC_LITERAL(11, 172, 19), // "remplirDeuxiemeReel"
QT_MOC_LITERAL(12, 192, 13), // "decalerCourbe"
QT_MOC_LITERAL(13, 206, 14), // "afficherErreur"
QT_MOC_LITERAL(14, 221, 2), // "x1"
QT_MOC_LITERAL(15, 224, 2), // "x2"
QT_MOC_LITERAL(16, 227, 11), // "lireFichier"
QT_MOC_LITERAL(17, 239, 8), // "fileName"
QT_MOC_LITERAL(18, 248, 17) // "changerVisibility"

    },
    "FenetreValidation\0WindowTitleChanged\0"
    "\0ouvrirDialogueReel\0ouvrirDialogueTheorique\0"
    "ouvrirDialogueDeuxiemeReel\0choixFichier\0"
    "remplirTheorique\0QwtPlot*\0plot\0"
    "remplirPremiereReel\0remplirDeuxiemeReel\0"
    "decalerCourbe\0afficherErreur\0x1\0x2\0"
    "lireFichier\0fileName\0changerVisibility"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FenetreValidation[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    1,   79,    2, 0x0a /* Public */,
      10,    1,   82,    2, 0x0a /* Public */,
      11,    1,   85,    2, 0x0a /* Public */,
      12,    0,   88,    2, 0x0a /* Public */,
      13,    2,   89,    2, 0x0a /* Public */,
      16,    1,   94,    2, 0x0a /* Public */,
      18,    0,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   14,   15,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,

       0        // eod
};

void FenetreValidation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FenetreValidation *_t = static_cast<FenetreValidation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->WindowTitleChanged(); break;
        case 1: _t->ouvrirDialogueReel(); break;
        case 2: _t->ouvrirDialogueTheorique(); break;
        case 3: _t->ouvrirDialogueDeuxiemeReel(); break;
        case 4: _t->choixFichier(); break;
        case 5: _t->remplirTheorique((*reinterpret_cast< QwtPlot*(*)>(_a[1]))); break;
        case 6: _t->remplirPremiereReel((*reinterpret_cast< QwtPlot*(*)>(_a[1]))); break;
        case 7: _t->remplirDeuxiemeReel((*reinterpret_cast< QwtPlot*(*)>(_a[1]))); break;
        case 8: _t->decalerCourbe(); break;
        case 9: _t->afficherErreur((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 10: _t->lireFichier((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->changerVisibility(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FenetreValidation::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FenetreValidation::WindowTitleChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject FenetreValidation::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FenetreValidation.data,
      qt_meta_data_FenetreValidation,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FenetreValidation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FenetreValidation::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FenetreValidation.stringdata0))
        return static_cast<void*>(const_cast< FenetreValidation*>(this));
    return QWidget::qt_metacast(_clname);
}

int FenetreValidation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void FenetreValidation::WindowTitleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
