#ifndef TESTJSON_H
#define TESTJSON_H

#include <iostream>
#include <typeinfo>

#include <QString>

#include "unittester.hpp"
#include "Archive/Json/json.hpp"
#include "Archive/Json/ijsonserializable.hpp"
#include "TypeTraits/typetraits.hpp"
#include "Archive/fileinfo.hpp"

using namespace std;
using namespace  boost;
using namespace rapidjson;
using namespace SSDK::Archive;
using namespace SSDK::TypeTraits;

namespace UnitTester
{
        namespace SSDK
        {
             /**
             * @brief The Person class
             *              仅仅是一个测试类,用来测试类对象序列化和反序列化,
             *              模拟一个最简单的类,只有一些内置类型的成员变量
             */
            class Person:public IJsonSerializable
            {
            public:
                Person(){}

                Person(const std::string& name, unsigned age) : m_name(name), m_age(age) {}
                Person(const Person& rhs) : m_name(rhs.m_name), m_age(rhs.m_age) {}
                virtual ~Person(){}

                std::string name(){return this->m_name;}
                void setName(std::string name){this->m_name = name;}
                int age(){return this->m_age;}
                void setAge(int age){ this->m_age = age;}


                bool operator == (const Person& rhs)
                {
                    return (m_name == rhs.m_name)&&
                               ( m_age == rhs.m_age);
                }

                virtual void serializeToJsonObj(Json& parentJson)  override
                {
                    parentJson.writeValue(TYPE_STRING_NAME(m_name),this->m_name.data());
                    parentJson.writeValue(TYPE_STRING_NAME(m_age),this->m_age);
                }

                virtual void deserializeFromJsonValue(rapidjson::Value& parentVal)  override
                {
                    bool isFound{false};
                    this->m_name =  Json::queryString(parentVal,TYPE_STRING_NAME(m_name),isFound);
                    this->m_age =  Json::queryNumber<unsigned int>(parentVal,TYPE_STRING_NAME(m_age),isFound);
                }

            protected:
                std::string m_name;
                unsigned int m_age;
            };

            /**
             * @brief The Student class
             *             子类序列化,需要考虑基类部分
             */
            class Student: public Person
            {
            public:
                Student(){}
                Student(const std::string& name, unsigned int age, int id)
                {
                    this->m_name = name;
                    this->m_age = age;
                    this->m_id = id;
                }
                virtual ~Student(){}

                bool operator == (const Student& rhs)
                {
                    return (m_id == rhs.m_id)&&
                               (m_name == rhs.m_name) &&
                               (m_age== rhs.m_age);
                }

                int id(){return this->m_id;}
                void setID(int id){ this->m_id = id;}

                virtual void serializeToJsonObj(Json& parentJson) override
                {
                      Person::serializeToJsonObj(parentJson);
                      parentJson.writeValue(TYPE_STRING_NAME(m_id),this->m_id);
                }

                virtual void deserializeFromJsonValue(rapidjson::Value& parentVal)override
                {
                    bool isFound{false};
                    this->m_id =Json::queryNumber<int>(parentVal,TYPE_STRING_NAME(m_id),isFound);
                    Person::deserializeFromJsonValue(parentVal);
                }

            private:
                int m_id{0};
            };

            /**
             * @brief The Teacher class
             *              既有父类, 又有嵌入对象的初始化,嵌入对象包括自定义类型对象和自定义类型的数组
             */
            class Teacher:public Person
            {
            public:
                Teacher(){}
                Teacher(const std::string& name, unsigned int age, int id, Student assistant,const vector<Student>& students):m_students(students)
                {
                    this->m_name = name;
                    this->m_age = age;
                    this->m_id = id;
                    this->m_assisant.setAge(assistant.age());
                    this->m_assisant.setName(assistant.name());
                    this->m_assisant.setID(assistant.id());
                }

                 Student assisant(){return this->m_assisant;}

                 bool operator == (const Teacher& rhs)
                {
                    bool isSame{false};
                    isSame = (m_id == rhs.m_id)&&
                            (m_name == rhs.m_name)&&
                            (m_age == rhs.m_age)&&
                            (m_assisant == rhs.m_assisant);

                    if(!isSame)
                    {
                        return false;
                    }
                    else
                    {
                        for(uint i = 0;i<this->m_students.size();++i)
                        {
                            if(this->m_students[i] == rhs.m_students[i])
                            {
                                continue;
                            }
                            else
                            {
                                return false;
                            }
                        }
                    }

                    return true;
                }
                 virtual void serializeToJsonObj(Json& parentJson) override
                 {
                     Person::serializeToJsonObj(parentJson);//写基类对象
                     parentJson.writeValue(TYPE_STRING_NAME(m_id),this->m_id);//写ID

                     parentJson.writeValue(TYPE_STRING_NAME(m_students));
                     parentJson.startArray();//写数组
                     for(auto iter = this->m_students.begin();iter!=this->m_students.end();++iter)
                     {
                         parentJson.startObject();
                         iter->serializeToJsonObj(parentJson);
                         parentJson.endObject();
                     }
                     parentJson.endArray();

                     parentJson.writeValue(TYPE_STRING_NAME(m_assisant));//作为name必须放在startObject前面
                     parentJson.startObject();//写嵌入式对象
                     this->m_assisant.serializeToJsonObj(parentJson);
                     parentJson.endObject();
                 }

                virtual void deserializeFromJsonValue(rapidjson::Value& parentVal)override
                {
                     //TBC 这部分记得补充路径验证

                     bool isFound{false};
                     this->m_id = Json::queryNumber<double>(parentVal,TYPE_STRING_NAME(m_id),isFound);//读ID
                     Person::deserializeFromJsonValue(this->m_json.doc());//读基类对象

                     //读数组
                     auto& arrayVal = this->m_json.queryArray(TYPE_STRING_NAME(m_students),isFound);
                     if(isFound)
                     {
                         //注意:对于下面这部分操作, 由于对于数组获得的Value可能是任意类型, 所以直接获取到Value然后取值
                         int cnt = arrayVal.Size();
                         for(int i = 0;i<cnt;++i)
                         {
                             Student student;
                             student.deserializeFromJsonValue(arrayVal[i]);
                            this->m_students.push_back(student);
                         }
                     }

                     //读嵌入对象
                     auto& assistantVal = this->m_json.queryValue(TYPE_STRING_NAME(m_assisant),isFound);
                     if(isFound)
                     {
                         this->m_assisant.deserializeFromJsonValue(assistantVal);
                     }
                }

            private:
                double m_id{0};
                std::vector<Student> m_students;
                Student m_assisant;
            };

            /**
             * @brief 测试SSDK中的Archive/json类
             */
            class TestJson: public QObject
            {
                Q_OBJECT

            private slots:
                void initTestCase()
                {

                }

                /**
                  * @brief testloadFromFileAndWriteToFile
                  *
                  * 测试Json下面2个方法
                  *         1.loadFromFile
                  *         2.writeToFile
                  *         3.(parseFromString) 不需要单独测试，因为readFromFile内部就调用了parseFromString函数
                  *
                  * 测试数据(来自与RapidJson的官方测试数据):
                  *          1.glossary.json
                  *          2.menu.json
                  *          3.widget.json
                  *
                  * 测试逻辑：
                  *        1.先要读取一个Json文件到内存，调用(readFromFile)函数，
                  *        2.写入到另一个文件，调用(writeToFile)函数，
                  *        3.如果读取源json文件的字符串和读取新写的json文件的字符串完全一样，那么代表两个函数测试通过
                  */
                void testLoadFromFileAndWriteToFile()
                {
                    /*srcjson1, srcJson2, srcJson3 代表读取源路径获取的json对象*/

                    Json srcJson1(m_jsonDataPath+"glossary.json",false);
                    Json srcJson2(m_jsonDataPath+"menu.json",false);
                    Json srcJson3(m_jsonDataPath+"widget.json",false);


                    /*wPath1, wPath2, wPath3 代表写入的新路径, */
                    auto  wPath1 = m_jsonDataPath+"glossary1.json";
                    auto  wPath2 = m_jsonDataPath+"menu1.json";
                    auto  wPath3 = m_jsonDataPath+ "widget1.json";

                    srcJson1.writeToFile(wPath1);
                    srcJson2.writeToFile(wPath2);
                    srcJson3.writeToFile(wPath3);

                    Json destJson1(wPath1,false);
                    Json destJson2(wPath2,false);
                    Json destJson3(wPath3,false);

                    /*判断字符串串是否相等*/
                    QVERIFY(std::string(srcJson1.toString()) == std::string(destJson1.toString()));
                    QVERIFY(std::string(srcJson2.toString())== std::string(destJson2.toString()));
                    QVERIFY(std::string(srcJson3.toString()) == std::string(destJson3.toString()));
                }

                /**
                  * @brief testQueryObject
                  *
                  * 测试Json下面函数
                  *      1.parseFromString
                  *      2.query
                  *
                  * 测试数据(来自与RapidJson的官方测试数据)
                  *      1. " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } "(最简单的例子)
                  *      2. glossary.json(包含了嵌入对象)
                  *
                  * 测试逻辑：
                  *      1.创建Json对象
                  *      2.从字符串中取出各个成员然后对比
                  *      3.如果成员的值完全和字符串中创建的值一样，那么测试通过
                  */
                void testQueryObject()
                {
                    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                    //基础数据测试

                    string jsonSrcStr(" { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ");
                    Json json(jsonSrcStr,true);

                    auto helloVal =  json.queryString("hello");
                    QVERIFY(string(helloVal)==string("world"));

                    auto tVal = json.queryNumber<bool>("t");
                    QVERIFY(tVal==true);

                    auto fVal = json.queryNumber<bool>("f");
                    QVERIFY(fVal==false);

                    auto iVal = json.queryNumber<int>("i");
                    QVERIFY(iVal==123);

                    double dVal = json.queryNumber<double>("pi");
                    QVERIFY(dVal == 3.1416);

                    auto nVal = json.queryString("n");
                    QVERIFY(nVal == nullptr);

                    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

                    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                    //测试对子对象的查询

                    Json json1(m_jsonDataPath+"glossary.json",false);
                     auto acronymVal =  json1.queryString("GlossSee");
                     QVERIFY(acronymVal== string("markup"));

                     //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                }

                /**
                   * @brief testQueryArray
                   *
                   * 测试Json以下函数
                   *        1.const rapidjson::Value& queryArray(const char* key, bool& isFound);
                   *                这个public重载函数有3个,但是由于其它2个函数仅仅是参数key的类型不一样, 内部也是调用了这个,所以只测试这个就可以了
                   *
                   *        2.  template<typename T>
                   *               void queryArray(const char* key, std::vector<T>& vector);
                   *
                   * 测试数据:
                   *      glossary.json
                   *      menu.json
                   *
                   * 测试逻辑:
                   *        1.测试读取单一简单类型(Number, String和nullptr)的数组
                   *        2.测试嵌套在对象中的数组,而不是根节点
                   *        3.测试复杂对象的数组,即数组成员的类型可以不一样, 在函数中做简单的调用演示
                   */
                void testQueryArray()
                {
                    Json json(m_jsonDataPath+"glossary.json",false);

                    //GlossSeeAlso不在根目录下,同时所有成员都是string类型
                    vector<string> sVector;
                    json.queryArray("GlossSeeAlso",sVector);
                    QVERIFY(
                                sVector[0] == string("GML")&&
                                sVector[1] == string("XML")
                            );

                    Json json1(m_jsonDataPath+"menu.json",false);
                    //注意:一定要用引用接受Value
                    bool isFound;
                    auto& val = json1.queryArray("items",isFound );
                    auto idVal = (char*)val[1]["id"].GetString();
                    auto labVal =  (char*)val[1]["label"].GetString();
                    QVERIFY(
                                string(idVal) == string("OpenNew")&&
                                string(labVal) == string("Open New")
                            );
                }

                /**
                   * @brief testModifyNumberAndString
                   *
                   *  测试函数
                   *      modifyNumber
                   *      modifyString
                   *
                   *  测试数据(来自与RapidJson的官方测试数据)
                   *    " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } "
                   *
                   * 测试逻辑:
                   *      1.从字符串中读取json
                   *      2.使用对应的modify函数修改json的成员
                   *      3.读取修改后的json的成员，如果读取后的值和修改的值一样，测试通过
                   *      4.测试原来的null的数据是否可以设置的string
                   */
                void testModifyNumberAndString()
                {
                    string jsonSrcStr(" { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ");
                    Json json(jsonSrcStr,true);

                    // 修改string
                    json.modifyString("hello", "rime");
                    auto helloVal = json.queryString("hello");
                    QVERIFY(string(helloVal)== string("rime"));

                    //修改null为string
                    json.modifyString("n", "ming");
                    auto nVal = json.queryString("n");
                    QVERIFY(nVal== string("ming"));

                    //修改bool
                    json.modifyNumber("t", false);
                    auto tVal = json.queryNumber<bool>("t");
                    QVERIFY(tVal== false);

                    json.modifyNumber("f", true);
                    auto fVal = json.queryNumber<bool>("f");
                    QVERIFY(fVal== true);

                    //修改int
                    json.modifyNumber("i", 456);
                    auto iVal = json.queryNumber<int>("i");
                    QVERIFY(iVal== 456);

                    //修改double
                    json.modifyNumber("pi", 123.12);
                    auto dVal = json.queryNumber<double>("pi");
                    QVERIFY(dVal== 123.12);
                }

                /**
                   * @brief testModifyArray
                   *
                   *  测试函数
                   *      1.pushBackToArray
                   *      2.popBackFromArray
                   *      3.clearArray
                   *      4.modifyElementOfArrayBasedOnIndex
                   *
                   *  测试数据(来自与RapidJson的官方测试数据)
                   *      1." { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } "
                   *          用于Array的成员为简单类型
                   *      2.menu.json
                   *          用于Array的成员为复杂类型
                   *
                   * 测试逻辑:
                   *      1.从字符串中读取json
                   *      2.修改指定位置的值, 然后再读取看是否成功. 这里包含了Array的成员为简单类型和复杂类型2中情况
                   *      3.往数组中插入一条记录,再读取最后一条记录, 看插入是否成功
                   *      5.从数组中移除一条记录,查读取最后一条记录,看移除是否成功
                   *      4.测试原来的null的数据是否可以设置的string
                   */
                void testModifyArray()
                {
                    string jsonSrcStr(" { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ");
                    Json json(jsonSrcStr,true);

                    int aVal;
                    bool isFound = false;
                    bool isSuccessful = false;

                    //对于简单类型,修改指定位置的值
                    json.modifyNumberElementOfArrayBasedOnIndex("a",1,9);
                    aVal =  json.queryEmbededArrayBasedOnIndex<int>("a",1);
                    QVERIFY(aVal== 9);

                    //插入一条记录
                    isSuccessful = json.pushNumberBackToArray("a",5);
                    aVal =  json.queryLastElementOfEmbededArray<int>("a");
                     QVERIFY(aVal== 5 );

                     //移除一条记录
                     isSuccessful = json. popBackFromArray("a");
                      QVERIFY(isSuccessful);
                     aVal = json.queryLastElementOfEmbededArray<int>("a");
//                     QVERIFY(isFound);
                     QVERIFY( aVal == 4);

                     //清空数组
                     isSuccessful = json.clearArray("a");
                     QVERIFY(isSuccessful);
                     int cnt = json.getArrayCount("a");
                     QVERIFY(cnt== 0);

                    //对于复杂对象,得到Array手动修改流程
                    Json json1(m_jsonDataPath+"menu.json",false);
                    auto& array1 = json1.queryArray("items",isFound);
                    array1[1]["id"].SetString("rime",4);
                    QVERIFY(string(array1[1]["id"].GetString())== string("rime")&&isFound);

                    auto& array2 = json1.queryArray("items",isFound);
                    auto resStr =string(array2[1]["id"].GetString());
                    QVERIFY(resStr== string("rime")&& isFound);
                }

                /**
                   * @brief testModifyObject
                       *
                       *  测试函数
                       *     addValueToObject
                       *     addNumberToObject
                       *     addValueToObject
                       *     addStringToObject
                       *     removeMemberFromObject
                       *
                       *  测试数据(来自与RapidJson的官方测试数据)
                       *        glossary.json
                       *
                       * 测试逻辑:
                       *      1.从字符串中读取json
                       *      2.增加指定Value,然后读取该Value,再进行验证
                       *      3.删除指定Value,然后读取该Value,如果读取不成功算测试通过
                       */
                void testModifyObject()
                {
                    Json json(m_jsonDataPath+"glossary.json",false);

                    //增加一个Value对象
                    Value val(9);
                    json.addValueToObject("GlossDiv","rime",val);
                    auto rimeVal = json.queryNumber<int>("rime");
                    QVERIFY(rimeVal == 9);

                    //测试增加一个Number对象
                    //注意,json可以接受同一层级出现2个一模一样的value, 但是最好不要这样做,因为这样在查询的时候会出错,因为这
                    //2个一样的Value可能会拥有不同的类型, 这对类型判断会带来异常
                     json.addNumberToObject("glossary","rime",0.628);
                     auto dVal = json.queryNumber<double>("rime");
                     QVERIFY(dVal ==0.628);

                     //增加一个String对象
                     json.addStringToObject("GlossEntry","rime","N213B");
                     auto sVal = json.queryString("GlossEntry","rime");
                     QVERIFY(sVal ==std::string("N213B"));
                }

                /**
                 * @brief testSerializeAndDeserialize
                 *             测试对象以Json方式的序列化和反序列化
                 *
                 * 测试类:
                 *          IJsonSerializable
                 *          Json
                 *
                 * 测试函数:
                 *          serializeToJsonValue
                 *          serializeToJsonFile
                 *          deserializeFromJsonValue
                 *          deserializeFromFile
                 *          writeValue
                 *
                 * 测试逻辑:
                 *          1.最简单的类,只包含了内置类型成员的序列化和反序列化
                 *          2.子类, 需要序列化基类部分和子类部分
                 *          2.复杂的类,包含了自定义类型的嵌入对象, 需要处理关于这种对象私有成员的序列化
                 */
                void testSerializeAndDeserialize()
                {
                    //1.对于简单类,只包含了内置类型成员的序列化和反序列化
                    Person rime("rime",30);
                    auto path = m_jsonDataPath.toStdString()+string("person.json");
                    rime.serializeToJsonFile(path);

                    Person rime1;
                    rime1.deserializeFromFile(path);
                    QVERIFY(rime == rime1);

                    //2.对于包含了自定义类型的嵌入对象, 需要处理关于这种对象私有成员的序列化
                    Student ming("ming",20,2);
                    path = m_jsonDataPath.toStdString()+string("student.json");
                    ming.serializeToJsonFile(path);

                    Student ming1;
                    ming1.deserializeFromFile(path);
                    QVERIFY(ming == ming1);

                    //3.对于最复杂的对象, 有继承关系,有嵌入对象的类型的序列化
                    vector<Student> students;
                    Student wang("wang",22,3);
                    students.push_back(ming);
                    students.push_back(wang);

                    Teacher xu("xu", 34, 1,wang,students);
                    path = m_jsonDataPath.toStdString()+string("teacher.json");
                    xu.serializeToJsonFile(path);

                    Teacher xu1;
                    xu1.deserializeFromFile(path);
                    QVERIFY(xu == xu1);
                }

                /**
                 * @brief testWritePerformance
                 *             测试Json写的效率
                 *
                 *  测试数据
                 *           模拟设计的30W, 20列数据, 数据类型和Sqlite及parquet效率测试的一样
                 *
                 *  测试结果
                 *   rime PC:   i7  16G  1070 ubuntu
                 *              Debug: 3.44 s
                 *              Release:0.67 s
                 *              165.4M
                 *
                 */
                void testWritePerformance()
                {
                    auto path = m_jsonDataPath.toStdString()+string("array.json");
                    FileInfo fileInfo(path);
                    if(fileInfo.exists(path))
                    {
                        fileInfo.remove();
                    }

                    QBENCHMARK
                    {
                        //>>>-------------------------------------------------------------------------------------------------------------------------------------
                        //1.创建数据结构(30W行, 20列)


                        Json json;
                        int rowCnt =1; /*300000;*///平时, 为了方便测试, 这里的数据量改为200
                        json.startArray();
                        for(int i = 0;i<rowCnt;++i)
                        {
                            json.startObject();

                            json.writeValue("id", i);
                            json.writeValue("KPIID", i+1 );
                            json.writeValue("CODE", i +2);
                            json.writeValue("V1", i+3 );
                            json.writeValue("V2", i +4);
                            json.writeValue("V3", i *3.14159);
                            json.writeValue("V4", "it is a test");
                            json.writeValue("V5", i *1.10);
                            json.writeValue("V6", i *1.11);
                            json.writeValue("V7", i *1.12);
                            json.writeValue("V8", i *1.13);
                            json.writeValue("V9", i *1.14);
                            json.writeValue("V10", i *1.15);
                            json.writeValue("V11", i *1.16);
                            json.writeValue("V12", i *1.17);
                            json.writeValue("V13", i *1.18);
                            json.writeValue("V14", i *1.19);
                            json.writeValue("V15", i *1.20);
                            json.writeValue("V16", i *1.21);
                            json.writeValue("V17", i *1.22);

                            json.endObject();
                        }
                        json.endArray();

                        json.writeToFile(path);
                    }
                }

                /**
                 * @brief testReadPerformance
                 *             测试Json读的效率
                 *
                 * 测试数据
                 *           模拟设计的30W, 20列数据, 数据类型和Sqlite及parquet效率测试的一样
                 *
                 * 测试结果
                 *   rime PC:   i7  16G  1070 ubuntu
                 *              Debug: 8.80 s
                 *              Release:1.17 s
                 */
                void testReadPerformance()
                {
                    auto path = m_jsonDataPath.toStdString()+string("array.json");
                    Json json;
//                    QBENCHMARK
                    {
                        json.loadFromFile(path);
                    }

                    int rowCnt = json.getArrayCount();
                    for(int i = 0; i< rowCnt;++i)
                    {
                        QVERIFY(json.doc()[i]["id"].GetInt() == i);
                        QVERIFY(json.doc()[i]["KPIID"].GetInt() == i+1);
                        QVERIFY(json.doc()[i]["CODE"].GetInt() == i+2);
                        QVERIFY(json.doc()[i]["V1"].GetInt() == i+3);
                        QVERIFY(json.doc()[i]["V2"].GetInt() == i+4);
                        QVERIFY( abs(json.doc()[i]["V3"].GetDouble() - i *3.14159) < 0.00001);
                        QVERIFY(std::string(json.doc()[i]["V4"].GetString()) == string("it is a test"));
                        QVERIFY(abs(json.doc()[i]["V5"].GetDouble() -  i *1.10) < 0.001);
                        QVERIFY(abs(json.doc()[i]["V6"].GetDouble() -  i *1.11) <0.001);
                        QVERIFY(abs(json.doc()[i]["V7"].GetDouble() -  i *1.12)<0.001);
                        QVERIFY(abs(json.doc()[i]["V8"].GetDouble() -  i *1.13)<0.001);
                        QVERIFY(abs(json.doc()[i]["V9"].GetDouble() -  i *1.14)<0.001);
                        QVERIFY(abs(json.doc()[i]["V10"].GetDouble() -  i *1.15)<0.001);
                        QVERIFY(abs(json.doc()[i]["V11"].GetDouble() -  i *1.16)<0.001);
                        QVERIFY(abs(json.doc()[i]["V12"].GetDouble() -  i *1.17)<0.001);
                        QVERIFY(abs(json.doc()[i]["V13"].GetDouble() -  i *1.18)<0.001);
                        QVERIFY(abs(json.doc()[i]["V14"].GetDouble() -  i *1.19)<0.001);
                        QVERIFY(abs(json.doc()[i]["V15"].GetDouble() -  i *1.20)<0.001);
                        QVERIFY(abs(json.doc()[i]["V16"].GetDouble() -  i *1.21)<0.001);
                        QVERIFY(abs(json.doc()[i]["V17"].GetDouble() -  i *1.22)<0.001);
                    }
                }

                void cleanupTestCase()
                {

                }

            private:
                      //测试数据路径
                      QString m_jsonDataPath{dataPath+"Json/"};
            };//End of TestJson

            DECLARE_TEST(TestJson)
        }//End of namespace SDK
}//End of namespace UnitTester

#endif // TESTJSON_H
