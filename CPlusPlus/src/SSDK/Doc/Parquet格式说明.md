# Parquet简要说明

### 1. Parquet支持嵌套的数据模型

    类似于Protocol Buffers，每一个数据模型的schema包含多个字段，每一个字段又可以包含多个字段


        每一个字段有三个属性：重复数、数据类型和字段名，重复数可以是以下三种：
              required(出现1次)，
              repeated(出现0次或多次)，
              optional(出现0次或1次)。

        每一个字段的数据类型可以分成两种：group(复杂类型)和primitive(基本类型)

 --------------------------------------------------------------------------------------


### 2. Parquet的每一列值都包好了三部分
value、repetition level和definition level。

####     Value:
>     具体的值, 详细见Parquet::Type

####     Repetition Levels:
> 等于它和前面的值在哪一层节点是不共享的。在读取的时候根据该值可以推导出哪一层上需要创建一个新的节点,例如对于这样的一个schema和两条记录。

    message nested
    {
        repeated group leve1
        {
            repeated string leve2;
        }
    }

    r1:[[a,b,c,] , [d,e,f,g]]
    r2:[[h] , [i,j]]

#### 计算repetition level值的过程如下：
1. value=a是一条记录的开始，和前面的值(已经没有值了)在根节点(第0层)上是不共享的，所以repeated level=0.

2. value=b它和前面的值共享了level1这个节点，但是level2这个节点上是不共享的，所以repeated level=2.同理value=c, repeated level=2.

3. value=d和前面的值共享了根节点(属于相同记录)，但是在level1这个节点上是不共享的，所以repeated level=1.

4.  value=h和前面的值不属于同一条记录，也就是不共享任何节点，所以repeated level=0.

==注意:==
1. 可以看出repeated level=0表示一条记录的开始，并且repeated level的值只是针对路径上的repeated类型的节点
2. 计算该值的时候可以忽略非repeated类型的节点，在写入的时候将其理解为该节点和路径上的哪一个repeated节点是不共享的
3. 取的时候将其理解为需要在哪一层创建一个新的repeated节点
4. 每一列最大的repeated level值就等于路径上的repeated节点的个数（不包括根节点）
5. 减小repeated level的好处能够使得在存储使用更加紧凑的编码方式，节省存储空间。

### Definition Levels:
> 值仅仅对于空值是有效的，表示在该值的路径上第几层开始是未定义的，对于非空的值它是没有意义的，因为非空值在叶子节点是定义的，所有的父节点也肯定是定义的，因此它总是等于该列最大的definition levels


    message ExampleDefinitionLevel
    {
        optional group a
        {
            optional group b
            {
                optional string c;
            }
        }
    }

                               Value            |           Definition Levels
                  --------------------------------------------------------------
                               a:null            |                0
                  --------------------------------------------------------------
                               b:null            |                1
                   --------------------------------------------------------------
                               c:null            |                2
                   --------------------------------------------------------------
                               c:"foo"           |                3


==注意:==
1. 由于definition level只需要考虑未定义的值，而对于required类型的节点，只要父节点是已定义的，该节点就必须定义
2. 所以计算definition level的值时可以忽略路径上的required节点，这样可以减小definition level的最大值，优化存储。


---------------------------------------------------------------------------------------
### 3. Parquet文件是以二进制方式存储的，
不可以直接读取的，文件中包括该文件的数据和元数据

> 数据:一个RowGroup的vector, 每一个RowGroup包含一定的行数,Parquet读写的时候会将整个行组缓存在内存中，      所以如果每一个行组的大小是由内存大小决定的，例如记录占用空间比较小的Schema可以在每一个行组中存储更多的行。

> 元数据:包含了"file schema"和RowGroup的列属性,file schema是一个节点树, 每一个节点是简单的类型(叶节点)或者复杂类型(嵌套节点)

 具体请参照网址:
          <新一代列式存储格式Parquet>    http://blog.csdn.net/yu616568/article/details/50993491
---

### 4. 代码中Parquet的一些注意事项
#### 4.1 关于数据结构ByteArray
目前看下来关于parquet::ByteArray时都缺陷的, 具体表现为ByteArray内部为一个带有长度的uint8_t指针,而parquet::ByteArray本身却不负责该指针的释放,所以在使用该结构的时候需要特别小心,稍不留意就会发生内存泄露. 下面以==读==和==写==两方面说明该问题:

==写==:需要注意创建ByteArray的时候,指针对象的来源:
- 像来自于string类型中,会由string对象销毁, 自己不需要销毁;由string销毁


    //由str负责销毁, 不需要销毁
    std::string str("It's a test");
    auto byteArr = parquet::ByteArray(
        str.size(),
        (const uint8_t*)str.data());

- 由自己new的数组, 需要自己负责销毁, 否则会产生内存泄露


    uint8_t* pInt = new uint8_t[20];
    auto byteArr = parquet::ByteArray(pInt, 20);
    ...
    //用完之后需要记得手动释放
    delete[] pInt;

- 写可以调用Parquet中的**ColumnVector**数据结构, 如果想要一次性释放的**ColumnVector**所有数据的话, 调用**dispose**函数

==读==: 读调用Parquet统一的读函数**readIndicatedColumn**,这是一个可变模板函数, 当模板类型为ByteArray时, 会出现问题:

     template<typename T>
    typename std::enable_if<std::is_same<T, int>::value ||
                            std::is_same<T, int64_t>::value ||
                            std::is_same<T, float>::value ||
                            std::is_same<T, double>::value ||
                            std::is_same<T, parquet::Int96>::value>::type//除了bool和ByteArray以外的所有类型
        Parquet:: readIndicatedRowValue(std::shared_ptr<parquet::ColumnReader>& colReader, ColumnVector<T>& columnVector, uint rowIndex)
        {
            int64_t foundCnt;

            /*问题:如果T的类型为ByteArray的话, columnVector.values()[rowIndex]在括号范围内被正确赋值,
            一旦除了这个括号范围, 指针就被销毁了,再也获取不到正确的值,怀疑这在parquet-cpp中某一次被释放了*/
            this->getColReaderPtr<T>(colReader.get())->ReadBatch(
                        1,
                        &columnVector.definitionLevels()[rowIndex],
                        &columnVector.repetitionLevels()[rowIndex],
                        &columnVector.values()[rowIndex],
                        &foundCnt);

             columnVector.isNulls()[rowIndex] = (foundCnt == 0);
        }

想要避免上面的问题, 就需要使用深复制, 拷贝数据到columnVector结构中

    template<typename T>
    typename std::enable_if<std::is_same<T, parquet::ByteArray>::value>::type//ByteArray需要单独处理
    Parquet::readIndicatedRowValue(  std::shared_ptr<parquet::ColumnReader>& colReader, ColumnVector<T>& columnVector, uint rowIndex)
    {
        int64_t foundCnt;
        parquet::ByteArray value;
        this->getColReaderPtr<T>(colReader.get())->ReadBatch(
                        1,
                        &columnVector.definitionLevels()[rowIndex],
                        &columnVector.repetitionLevels()[rowIndex],
                        &value,
                        &foundCnt);

        /*注意:
            1.这里必须重新new一个byte数组, 否则的话一旦出了这个花括号,value原来的数据会被释放
             这里还需要注意的是,一旦new的新数组, 在外部用完了需要手动释放
            2.这里的深复制代码不能写在ByteArray中, 因为一旦写了深复制, 在ByteArray中就需要添加相应的销毁指针代码,
              第一是需要考虑避免重复释放的问题,
              第二也会影响效率
        */
        columnVector.values()[rowIndex].ptr   = new uint8_t[value.len];
        columnVector.values()[rowIndex].len =  value.len;
        memcpy(const_cast<uint8_t*>(columnVector.values()[rowIndex].ptr), value.ptr, value.len);

        columnVector.isNulls()[rowIndex] = (foundCnt == 0);
    }

综上所述, 调用了**readIndicatedColumn**的函数,==同时数据类型有ByteArray的话 在调用端统一调用dispose函数, 否则会产生内存泄露==

    std::string str1((char*)colByteArrayVecor1.values()[0].ptr,colByteArrayVecor1.values()[0].len);
    QVERIFY(str1 == std::string("04/01/09"));
    std::string str2((char*)colByteArrayVecor1.values()[1].ptr, colByteArrayVecor1.values()[1].len);
    QVERIFY(str2 == std::string("04/01/09"));

    //如果时ByteArray时,需要手动释放
    colByteArrayVecor1.dispose();
    colByteArrayVecor2.dispose();







