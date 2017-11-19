#ifndef QMLHELPER_HPP_INL
#define QMLHELPER_HPP_INL

////feel no use
//template<typename ClassType>
//const QList<QString> Sung::SSDK::Core::QmlHelper:: enumStringList(std::string enumTypeName)
//{
//    auto list = QList<QString>();

//    auto meta = ClassType::staticMetaObject;
//    for (int i=0; i < meta.enumeratorCount(); ++i)
//    {
//        QMetaEnum m  =meta.enumerator(i);
//        if(std::string(m.name()) == enumTypeName)
//        {
//            for(int j=0; j <m.keyCount(); ++j)
//            {
//                list.push_back(QObject::tr(m.key(j)));
//            }

//            return list;
//        }
//    }
//}

//template<typename ClassType>
//void Sung::SSDK::Core::QmlHelper::setEnumStringMap(QVariantMap* pEumStringMap,std::string enumTypeName)
//{
//    if(nullptr==pEumStringMap)
//        return;

//    auto meta = ClassType::staticMetaObject;
//    for (int i=0; i < meta.enumeratorCount(); ++i)
//    {
//        QMetaEnum m  =meta.enumerator(i);
//        if(std::string(m.name()) == enumTypeName)
//        {
//            for(int j=0; j <m.keyCount(); ++j)
//            {
//                pEumStringMap->insert(QString(m.key(j)),m.value(j));
//            }

//            return;
//        }
//    }
//}

#endif // QMLHELPER_HPP_INL
