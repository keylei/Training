/****************************************************************************
** Meta object code from reading C++ file 'StyleSetting.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Style/StyleSetting.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StyleSetting.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StyleSetting_t {
    QByteArrayData data[17];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StyleSetting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StyleSetting_t qt_meta_stringdata_StyleSetting = {
    {
QT_MOC_LITERAL(0, 0, 12), // "StyleSetting"
QT_MOC_LITERAL(1, 13, 13), // "setThemeColor"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 10), // "themeIndex"
QT_MOC_LITERAL(4, 39, 9), // "ColorType"
QT_MOC_LITERAL(5, 49, 9), // "colorType"
QT_MOC_LITERAL(6, 59, 5), // "color"
QT_MOC_LITERAL(7, 65, 13), // "getThemeColor"
QT_MOC_LITERAL(8, 79, 9), // "themeList"
QT_MOC_LITERAL(9, 89, 9), // "ThemeType"
QT_MOC_LITERAL(10, 99, 5), // "LIGHT"
QT_MOC_LITERAL(11, 105, 4), // "DARK"
QT_MOC_LITERAL(12, 110, 12), // "USER_DEFINED"
QT_MOC_LITERAL(13, 123, 7), // "PRIMARY"
QT_MOC_LITERAL(14, 131, 6), // "ACCENT"
QT_MOC_LITERAL(15, 138, 9), // "FORGROUND"
QT_MOC_LITERAL(16, 148, 10) // "BACKGROUND"

    },
    "StyleSetting\0setThemeColor\0\0themeIndex\0"
    "ColorType\0colorType\0color\0getThemeColor\0"
    "themeList\0ThemeType\0LIGHT\0DARK\0"
    "USER_DEFINED\0PRIMARY\0ACCENT\0FORGROUND\0"
    "BACKGROUND"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StyleSetting[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       2,   36, // properties
       2,   42, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x02 /* Public */,
       7,    2,   31,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, QMetaType::QColor,    3,    5,    6,
    QMetaType::QColor, QMetaType::Int, 0x80000000 | 4,    3,    5,

 // properties: name, type, flags
       3, QMetaType::Int, 0x00095103,
       8, QMetaType::QStringList, 0x00095001,

 // enums: name, flags, count, data
       9, 0x2,    3,   50,
       4, 0x2,    4,   56,

 // enum data: key, value
      10, uint(StyleSetting::ThemeType::LIGHT),
      11, uint(StyleSetting::ThemeType::DARK),
      12, uint(StyleSetting::ThemeType::USER_DEFINED),
      13, uint(StyleSetting::ColorType::PRIMARY),
      14, uint(StyleSetting::ColorType::ACCENT),
      15, uint(StyleSetting::ColorType::FORGROUND),
      16, uint(StyleSetting::ColorType::BACKGROUND),

       0        // eod
};

void StyleSetting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StyleSetting *_t = static_cast<StyleSetting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setThemeColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< ColorType(*)>(_a[2])),(*reinterpret_cast< QColor(*)>(_a[3]))); break;
        case 1: { QColor _r = _t->getThemeColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< ColorType(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        StyleSetting *_t = static_cast<StyleSetting *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->themeIndex(); break;
        case 1: *reinterpret_cast< QStringList*>(_v) = _t->themeList(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        StyleSetting *_t = static_cast<StyleSetting *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setThemeIndex(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject StyleSetting::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_StyleSetting.data,
      qt_meta_data_StyleSetting,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StyleSetting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StyleSetting::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StyleSetting.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int StyleSetting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
