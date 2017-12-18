/****************************************************************************
** Meta object code from reading C++ file 'translator.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Translation/Translator.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'translator.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Translator_t {
    QByteArrayData data[8];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Translator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Translator_t qt_meta_stringdata_Translator = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Translator"
QT_MOC_LITERAL(1, 11, 15), // "langTypeChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 13), // "chageLangType"
QT_MOC_LITERAL(4, 42, 8), // "LangType"
QT_MOC_LITERAL(5, 51, 8), // "langType"
QT_MOC_LITERAL(6, 60, 2), // "EN"
QT_MOC_LITERAL(7, 63, 2) // "CN"

    },
    "Translator\0langTypeChanged\0\0chageLangType\0"
    "LangType\0langType\0EN\0CN"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Translator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       1,   28, // properties
       1,   32, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,

 // properties: name, type, flags
       5, 0x80000000 | 4, 0x0049510b,

 // properties: notify_signal_id
       0,

 // enums: name, flags, count, data
       4, 0x2,    2,   36,

 // enum data: key, value
       6, uint(Translator::LangType::EN),
       7, uint(Translator::LangType::CN),

       0        // eod
};

void Translator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Translator *_t = static_cast<Translator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->langTypeChanged(); break;
        case 1: _t->chageLangType((*reinterpret_cast< LangType(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Translator::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Translator::langTypeChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Translator *_t = static_cast<Translator *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< LangType*>(_v) = _t->langType(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Translator *_t = static_cast<Translator *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setLangType(*reinterpret_cast< LangType*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject Translator::staticMetaObject = {
    { &QTranslator::staticMetaObject, qt_meta_stringdata_Translator.data,
      qt_meta_data_Translator,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Translator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Translator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Translator.stringdata0))
        return static_cast<void*>(this);
    return QTranslator::qt_metacast(_clname);
}

int Translator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTranslator::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Translator::langTypeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
