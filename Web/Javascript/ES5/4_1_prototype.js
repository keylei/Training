function log(msg) {
    console.log(msg);
}

function Person() {
    Person.prototype.logPerson = function () {
        log("person");
    }
    Person.prototype.logPrototype = function () {
        log("It‘s Person function");
    }
    this.logTest = function () {
        log("just a test in Person directly. not prototype way!");
    }
    this.name = "peter";
}

Person.logAsObj = function () {
    log("Person as Object to log!");
}//作为对象，且不是prototype是不会被继承的

Person.prototype.age = 27;

function Teacher() {
    this.logTeacher = function () {
        log("teacher");
    }
    //以下代码卸载该函数内会报错
    // Teacher.prototype = new Person();
    // Teacher.prototype.logPrototype = function () {
    //     log("prototype");
    // }
}

//必须先对prototype赋值继承Person，否则prototype新增属性函数都会无效
Teacher.prototype = new Person(); //该方式还能够把prototype里面非prototype属性继承下来(也就是创建对象中的this.xx)
Teacher.prototype.logPrototype = function () {
    log("it's teacher function");
} //这里相当于实现对Person的logPrototype的覆盖（相当于覆盖了虚函数）

Teacher.prototype.logTeacher = function () {
    log("it's prototype method of logTeacher");
} //这个函数无效 因为Teacher函数内this开头的有和它同名函数，所以优先调用函数内自己的函数对象而不是prototype属性

var teacher = new Teacher();
teacher.logTeacher();
teacher.logPrototype();
teacher.logPerson(); //这是继承的prototype属性，通过F12查找定义
teacher.logTest(); //这是继承Person创建对象的普通属性（函数）
console.log(teacher.name); //这是继承Person穿件对象的普通属性（直接变量）
console.log(teacher.age);

// teacher.logAsObj(); //如果logAsObj不是作为创造对象函数中的方式，而是采用Person.logAsObj（作为对象且不是prototype），那么它将不会得到集成，下面一行也是不会成功的
// Teacher.logAsObj();

//补充说明：如果要函数多层继承，建议还是尽量把函数作为对象，优先使用其prototype属性，而不是将创建对象函数中this.func继承