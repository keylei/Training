#ifndef COLORMAKER_HPP
#define COLORMAKER_HPP

#include <QObject>
#include <QString>
#include <QColor>
#include <QTimerEvent>
#include <QDateTime>

//想要一个类或对象导出到QML中，必须满足前提条件:
//1. 从QObject或QObject的派生类继承
//2. 使用Q_OBJECT宏

class ColorMaker: public QObject
{
    Q_OBJECT

    //必须是C++中已经定义的枚举类型，使用Q_ENUMS注册到元对象系统中
    //一旦注册了，QML中就可以直接使用类型.枚举来访问了
    Q_ENUMS(GenerateAlgorithm)

    //1.这里的名称对应了读取函数的名称，一定要一一对应，如果没有这样的函数的话，会导致
    //编译出错

    //2.关于C++和QML可以传输的类型，具体参照：
    //      http://doc.qt.io/qt-5/qtqml-cppintegration-data.html

    //3.Q_PROPERTY 用来定义可通过元对象系统访问的属性，可以在QML中进访问.修改，
    //    原型为：
    //    Q_PROPERTY(type name
    //               (READ getFunction [WRITE setFunction] |
    //                MEMBER memberName [(READ getFunction | WRITE setFunction)])
    //               [RESET resetFunction]
    //               [NOTIFY notifySignal]
    //               [REVISION int]
    //               [DESIGNABLE bool]
    //               [SCRIPTABLE bool]
    //               [STORED bool]
    //               [USER bool]
    //               [CONSTANT]
    //               [FINAL])
    //    具体在Helper中输入:The Property System

    //read标记: 如果没有为属性指定MEMBER标记，则READ标记是必不可少的；声明一个
    //       读取属性，该函数一般没有参数，返回定义的属性
    //write标记: 可选配置，声明一个设定属性的函数，函数没有返回值，只能有一个与属性
    //       类型匹配的参数。
    //NOTIFY:   可选配置，给属性一个关联一个信号，当属性的值发生改变会触发该信号
    Q_PROPERTY(QColor currentColor READ currentColor WRITE setCurrentColor
               NOTIFY colorChanged)
    Q_PROPERTY(QColor timeColor READ timeColor )

public:
    enum class GenerateAlgorithm
    {
        RANDOM_RGB,
        RANDOM_RED,
        RANDOM_GREEN,
        RANDOM_BLUE,
        LINEAR_INCREASE
    };

    //对于继承了QObject的类，这个单参的构造函数重载是一定需要有的，否则会编译出错
    ColorMaker(QObject* parent = 0);
    ~ColorMaker();

    QColor timeColor() const;

    //指定一个可以在元系统中被调用的成员函数，Q_INVOKABLE必须放在类型前面
    Q_INVOKABLE GenerateAlgorithm algorithm() const;
    Q_INVOKABLE void setAlgorithm(GenerateAlgorithm algorithm);

    QColor currentColor() const;
    void setCurrentColor(const QColor &currentColor);

    //只要是信号/槽，都可以在QML中访问，有三种方式可以连接在一起:
    // 1. 把C++对象的符号连接到QML中定义的方法
    // 2.把QML对象的信号链接到C++对象的槽
    // 3. 直接调用的C++对象的槽或者信号
signals:
    void colorChanged(const QColor& color);
    void currentTime(const QString& strTime);

    //信号和槽的关系，可以参考：
    //https://www.ibm.com/developerworks/cn/linux/guitoolkit/qt/signal-slot/index.html
    //槽用于接受信号，他们是普通的成员函数，一个槽并不知道是否有信号和自己相连
    //你可以：
    //1.将很多信号和单个槽相连
    //2.将单个信号和很多槽相连
    //3.一个信号和另外一个信号相连
public slots:
    void start();
    void stop();

protected:
    void timerEvent(QTimerEvent *e);

private:
    GenerateAlgorithm m_algorithm;
    QColor m_currentColor;
    int m_colorTimer;
};

#endif // COLORMAKER_HPP
