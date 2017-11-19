主要参考:
<<Google Protocol Buffer 的使用和原理>>
    来自与https://www.ibm.com/developerworks/cn/linux/l-cn-gpb/


# 1. 静态编译使用:
###         1.1 创建一个.proto 文件


    package protocolBuffer;
    message typeCollection
    {
        required int32     int32ID = 1;
        required int64     int64ID = 2;
        optional uint32   uint32ID = 3;
        required uint64   uint64ID = 4 ;
        required sint32    sint32ID = 5;
        required sint64    sint64ID = 6;
        required fixed32 fint32ID = 7;
        required fixed64  fint64ID = 8;
        required sfixed32 sfint32ID = 9;
        required sfixed64 sfint64ID = 10;

        required bool   isNull  = 11;
        required string  name = 12;
        required float height = 13;
        required double with = 14;

        enum NestedEnum {
          MOBILE = 0;
          HOME = 1;
          WORK = 2;
        }
        optional NestedEnum enumVal = 15;
    }

==注意:==

1. 这里的package等于是c++的namespace, 用于防止命名冲突, 所以起名的时候需要考虑到尽量避免与现有项目中的
                  namespace发生冲突

2. message代表了数据结构部分,后面的名称代表了类型名, 如上面的文件最后编译的类,相当与:
    **class typeCollection : public ::google::protobuf::Message**

3. protocolBuf的数据类型及C++类型的对应关系如下:

    protocolBuf | C++ | 备注
    ------|------|-------
    double | double | -
    float | float | -
    int32 | int32 | 使用可变长的编码方式, 编码负数时不够搞笑--如果字段可能含有负数, 使用sint32
    int64 | int64 | 使用可变长的编码方式, 编码负数时不够搞笑--如果字段可能含有负数, 使用sint64
    uint32 | uint32 | 使用可变长度编码
    uint64 | uint64 | 使用可变长度编码
    sint32 | int32 | 使用可变长度编码,有符号的整形值,编码时通常比int32高效
    sint64 | int64 | 使用可变长度编码,有符号的整形值,编码时通常比int64高效
    fixed32 | uint32 | 总是4个字节.如果数值总是比228大的话,这个类型比uint32高效
    fixed64 | uint64 | 总是8个字节,如果数值总是比256大的话,这个类型会比uint64高效
    sfixed32 | int32 | 总是4个字节
    sfixed64 | int64 | 总是8个字节
    bool | bool | -
    string | strin | 可能包含任意顺序的字节数据

4. 访问修饰符,这个含义和Parquet一样
>     required：一个格式良好的消息一定要含有1个这种字段。表示该值是必须要设置的；
>     optional：消息格式中该字段可以有0个或1个值（不超过1个），也就是可有可无；
>     repeated：在一个格式良好的消息中，这种字段可以重复任意多次（包括0次）。重复的值的顺序会被保留。

5. 分配编号

    定义字段的编号,在Protocol Buffers中,字段的编号非常重要,字段名仅仅是作为参考和生成代码用。需要注意的是字段的编号区间范围,其中19000 ~ 19999被Protocol Buffers作为保留字段。一旦开始使用就不能够再改变。

    ==注：==[1,15]之内的标识号在编码的时候会占用一个字节。[16,2047]之内的标识号则占用2个字节。所以应该为那些频繁出现的消息元素保留 [1,15]之内的标识号。切记：==要为将来有可能添加的、频繁出现的标识号预留一些标识号。==

6. protoc的文件名命名要规范
    packageName.MessageName.proto

###         1.2 编译
编译该文件,  protoc -I=. --cpp_out=. ./protocolBuffer.typeCollection.proto

    -I=:后面加源目录
    --cpp_out=:后面加输出目录, 后面紧跟着文件

最后输出**protocolBuffer.typeCollection.pb.cc**和**protocolBuffer.typeCollection.pb.h**两个文件


### 1.3 如何调用
序列化

    //创建对象
    protocolBuffer::typeCollection obj;

    //...给对象赋值

    QString filePath = m_parquetDataPath+"staticComplieTest";
    fstream output(filePath.toStdString().data(), ios::out | ios::trunc | ios::binary);
    obj.SerializeToOstream(&output);
    output.close();

反序列化

    protocolBuffer::typeCollection obj1;
    fstream input(filePath.toStdString().data(), ios::in | ios::binary);
    obj1.ParseFromIstream(&input);
    input.close();



---
# 2. 动态编译使用:
## 2.1 创建对象
> 一般情况下，使用 Protobuf 的人们都会先写好 .proto 文件，再用 Protobuf 编译器生成目标语言所需要的源代码文件。将这些生成的代码和应用程序一起编译。

可是在某且情况下，人们无法预先知道 .proto 文件，他们需要动态处理一些未知的 .proto 文件。比如一个通用的消息转发中间件，它不可能预知需要处理怎样的消息。这需要动态编译 .proto 文件，并使用其中的 Message。


**代码**

    auto newObj = protoc.createMessageInstance("protocolBuffer.typeCollection");


## 2.2 调用字段

```
auto pField =  ProtocolBuffer::findFieldByName(message, "int32ID");
int32_t val = ProtocolBuffer::getValue<int32_t>(newObj, pField)
```
## 2.3 设置字段

```
auto pField =  ProtocolBuffer::findFieldByName(message, "int32ID");
ProtocolBuffer::setValue(newObj, pField, 1);
```

## 2.4 序列化

```
QString objFilePath = m_parquetDataPath+QString("typeCollection_dynamicComplieTest");
ProtocolBuffer::serializeToFilePath(*newObj.get(), objFilePath.toStdString());
```
## 2.5 反序列化

```
auto newObj1 = protoc.createMessageInstance("protocolBuffer.typeCollection");
ProtocolBuffer::deserializeFromFilePath(*newObj1.get(), objFilePath.toStdString());

```
