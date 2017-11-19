对于json序列化反序列化对象具体的例子在见单元测试的testjson.hpp中

对象按照复杂程度分为3类:
1. 最简单的类, 只包含了内置基础类型的成员
2. 简单的继承关系的类,继承与一个基类,同时包含子类特有的成员,这些成员是内置基础类型
3. 复杂的继承关系的类,继承与一个基类,同时包含子类特有的成员,这些成员可以是自定义类型的嵌入对象,或者是标准库容器或者数组

--------------------------------------------------------------------------------------

# 第一部分：最简单的类

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
                int age(){return this->m_age;}

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
            
            

测试代码:
                   
                   
             //1.对于简单类,只包含了内置类型成员的序列化和反序列化
            Person rime("rime",30);
            auto path = m_jsonDataPath.toStdString()+string("person.json");
            rime.serializeToJsonFile(path);

            Person rime1;
            rime1.deserializeFromFile(path);
            QVERIFY(rime == rime1);

--------------------------------------------------------------------------------------
# 第二部分：简单的继承关系的类
继承与一个基类,同时包含子类特有的成员,这些成员是内置基础类型
            
            
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
            
测试代码:

    Student ming("ming",20,2);
    path = m_jsonDataPath.toStdString()+string("student.json");
    ming.serializeToJsonFile(path);
    
    Student ming1;
    ming1.deserializeFromFile(path);
    QVERIFY(ming == ming1);
                    
                    
--------------------------------------------------------------------------------------

# 第三部分：复杂的继承关系的类

继承与一个基类,同时包含子类特有的成员,这些成员可以是自定义类型的嵌入对象,或者是标准库容器或者数组
           
           
           
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
                        for(int i = 0;i<this->m_students.size();++i)
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
                     this->m_id = Json::queryNumber<int>(parentVal,TYPE_STRING_NAME(m_id),isFound);//读ID
                     Person::deserializeFromJsonValue(this->m_json.doc());//读基类对象

                     //读数组
                     auto& arrayVal = this->m_json.queryArray(TYPE_STRING_NAME(m_students),isFound);
                     if(isFound)
                     {
                         //注意:对于下面这部分操作, 由于对于数组获得的Value可能是任意类型, 所以直接获取到Value然后取值
                         int cnt = arrayVal.GetSize();
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
            
测试代码:
                   
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
            
  
