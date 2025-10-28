/****************************************************************************
** Meta object code from reading C++ file 'principal.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../Memoriavirtual/principal.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'principal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_principal_t {
    QByteArrayData data[17];
    char stringdata0[301];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_principal_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_principal_t qt_meta_stringdata_principal = {
    {
QT_MOC_LITERAL(0, 0, 9), // "principal"
QT_MOC_LITERAL(1, 10, 13), // "addProcessRow"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 21), // "removeSelectedProcess"
QT_MOC_LITERAL(4, 47, 17), // "loadProcessSample"
QT_MOC_LITERAL(5, 65, 14), // "clearProcesses"
QT_MOC_LITERAL(6, 80, 23), // "runSchedulingSimulation"
QT_MOC_LITERAL(7, 104, 16), // "algorithmChanged"
QT_MOC_LITERAL(8, 121, 5), // "index"
QT_MOC_LITERAL(9, 127, 20), // "loadScenarioFromFile"
QT_MOC_LITERAL(10, 148, 18), // "saveScenarioToFile"
QT_MOC_LITERAL(11, 167, 19), // "exportSchedulingCsv"
QT_MOC_LITERAL(12, 187, 21), // "exportSchedulingImage"
QT_MOC_LITERAL(13, 209, 24), // "runConcurrencySimulation"
QT_MOC_LITERAL(14, 234, 26), // "concurrencyScenarioChanged"
QT_MOC_LITERAL(15, 261, 19), // "runMemorySimulation"
QT_MOC_LITERAL(16, 281, 19) // "loadReferenceSample"

    },
    "principal\0addProcessRow\0\0removeSelectedProcess\0"
    "loadProcessSample\0clearProcesses\0"
    "runSchedulingSimulation\0algorithmChanged\0"
    "index\0loadScenarioFromFile\0"
    "saveScenarioToFile\0exportSchedulingCsv\0"
    "exportSchedulingImage\0runConcurrencySimulation\0"
    "concurrencyScenarioChanged\0"
    "runMemorySimulation\0loadReferenceSample"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_principal[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    1,   89,    2, 0x08 /* Private */,
       9,    0,   92,    2, 0x08 /* Private */,
      10,    0,   93,    2, 0x08 /* Private */,
      11,    0,   94,    2, 0x08 /* Private */,
      12,    0,   95,    2, 0x08 /* Private */,
      13,    0,   96,    2, 0x08 /* Private */,
      14,    1,   97,    2, 0x08 /* Private */,
      15,    0,  100,    2, 0x08 /* Private */,
      16,    0,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void principal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<principal *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addProcessRow(); break;
        case 1: _t->removeSelectedProcess(); break;
        case 2: _t->loadProcessSample(); break;
        case 3: _t->clearProcesses(); break;
        case 4: _t->runSchedulingSimulation(); break;
        case 5: _t->algorithmChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->loadScenarioFromFile(); break;
        case 7: _t->saveScenarioToFile(); break;
        case 8: _t->exportSchedulingCsv(); break;
        case 9: _t->exportSchedulingImage(); break;
        case 10: _t->runConcurrencySimulation(); break;
        case 11: _t->concurrencyScenarioChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->runMemorySimulation(); break;
        case 13: _t->loadReferenceSample(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject principal::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_principal.data,
    qt_meta_data_principal,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *principal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *principal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_principal.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int principal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
