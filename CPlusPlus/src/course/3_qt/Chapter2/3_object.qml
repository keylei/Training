import QtQuick 2.7
import QtQuick.Controls 2.0


ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    property var rime: new Object();
    property var array: new Array();
    property int  age: 10;

    function replacer(key, value){
        switch(key){
        case "name":
            return "Zhang San";
        }
        return value;
    }

    Rectangle{
        id: root;
        Component.onCompleted: {

            //>>>----------------------------------------------------------------------------------------------------------
            //1. Object
            console.log("Object----------------------------------------------------------------");
            var obj = new Object();
            console.log( obj.toString() ); //返回对象的字符串标示
            console.log( obj.constructor); //指向对象的构造函数
            console.log( root.hasOwnProperty("width"));//判断对象是否有某个属性
            console.log( Item.isPrototypeOf(root) );//判断对象是否为另一个对象的原型
            console.log( root.propertyIsEnumerable("children"));//判断给定的属性是否可以用for...in语句进行枚举
            console.log( root.toString() );
            console.log( root.valueOf());//返回最适合该对象的原始值

            //对象的属性可以动态的增删，非常有趣
            obj.name = "rime";
            obj.year = 4;

            //动态增加方法
            obj.printInfo = function printInfo(){
                console.log("name:", obj.name, "year:", obj.year);
            }
            obj.printInfo();

            //通过数组下标访问属性和方法
            console.log(obj["name"]);
            obj["printInfo"]();

            //使用for...in 枚举对象属性
            for( var prop in obj )
            {
                console.log(prop, ",", obj[prop]);
            }

            //对象的字面量表示
            var person = {
                "name":"rime",
                "year":4
            }

            //>>>----------------------------------------------------------------------------------------------------------
            //2. String
            console.log("String----------------------------------------------------------------");
            var str = new String("I am a coder");
            console.log(str);
            console.log(str.length);
            console.log(str[0]);//通过索引访问单个字符串
            console.log(str.charAt(1));
            console.log(str.charCodeAt(1));

            //关于子字符串和正则后续在添加 TBC Vincent

            //>>>----------------------------------------------------------------------------------------------------------
            //3.Array
            console.log("Array----------------------------------------------------------------");
            var a = new Array();
            var b = new Array(10);
            var c = new Array(10,6,3,21,22,30,8);
            console.log(a);
            console.log(b);
            console.log(c);

            console.log("修改元素");
            var d = new Array(10,6,3,21,22,30,"zhangsan");
            console.log("array length:", d.length);
            console.log("2nd element:", d[1]);
            console.log("7th:", d[6]);
            d[6] = "ZhangSanFeng";
            d[7] = "XieXun";
            d.push(250);//末尾插入一个/多个元素
            d.unshift(1);//向数组开始添加一个元素并返回数组的长度
            console.log("--------------------------");
            console.log(d.join(" "));//把所有元素组合成一个字符串，字符串之间用指定的分隔符填充
            console.log(d.shift());
            console.log(d);
            d.reverse();//颠倒数组的顺序
            console.log(d);
            console.log(d.pop());//删除并返回数组的最后一个元素
            console.log(d.sort());//对数组内的元素排序并返回圆数组的引用
            console.log(d.pop());
            console.log(d.pop());
            console.log(d.sort());

            console.log("--------------------------");
            var arr = new Array("I", "like", "Qt", "Quick");
            var subArr = arr.slice(2,4);//把2,4索引之间的元素组成一个新的数组
            console.log(subArr.join(" "));
            var newArr = arr.concat( "!", subArr );
            console.log( newArr.join(" ") );
            newArr[0] = "Do you";
            newArr.splice(4,3,"?","Yes","!");
            console.log(newArr.join(" "));

            console.log("--------------------------");
            arr = [2,3,4,"?","Quick"] //使用字面量表示数组
            console.log(arr.length,arr[2]);

            //>>>----------------------------------------------------------------------------------------------------------
            //4.Math
            console.log("Color----------------------------------------------------------------");
            var pi = Math.PI;
            var textColor = Qt.rgba(Math.random(), Math.random(), Math.random());
            console.log(textColor.r);
            console.log(textColor.g);
            console.log(textColor.b);
            console.log(textColor.a);

            //>>>----------------------------------------------------------------------------------------------------------
            //5.Global
            //内置对象指不需要实例化就可以使用的本地对象，ES5定义了三个内置对象:Global,Math和JSON

            //Global 对象接管了没有不属于任何对象的属性和函数
            console.log("Global----------------------------------------------------------------");
            console.log(isNaN(1));
            var obj;
            console.log(isNaN(obj));
            console.log(isFinite(1/0));
            console.log(parseInt("2.1"));

            var uri = "http://dict.youdao.com/w/parse/#keyfrom=dict2.top"
            //encodeuri用处处理完成的uri
            var encodeUri = encodeURI(uri);
            //encodeURIComponent用于处理URI的一个片段
            var encodedComponent = encodeURIComponent(uri);

            //encodeURI 不对URI的特殊字符进行编码，如冒号，前斜杠，问号等
            //encodeURIComponent 对所有的非标准字符进行编码
            console.log(encodeUri);
            console.log(encodedComponent);

            var decodeUri = decodeURI(encodeUri);
            var decodeComponent = decodeURIComponent(encodedComponent);
            console.log(decodeUri);
            console.log(decodeComponent);

            //eval执行一段ES脚本，但是参数只能是原始字符串
            var s = "8+7";
            console.log(eval(s));
            var s2 = new String("9+10");
            console.log(eval(s2));

            //>>>----------------------------------------------------------------------------------------------------------
            //6.JSON对象
            console.log("JSON----------------------------------------------------------------");
            array[0] = "version";
            array[1] = 2.3;
            console.log(JSON.stringify(array));//数组转为json字符串

            //stringify object
            rime.name = "rime";
            rime.mobile = "13888888888";
            rime.age = 20;
            rime.country = "China";

            console.log(JSON.stringify(rime));//对象转为json字符串
            console.log(JSON.stringify(rime, null, 4));//
            console.log(JSON.stringify(rime, ["name", "mobile"], "  "));
            console.log(JSON.stringify(rime, replacer));

            //use toJSON
            rime.toJSON = function(key){
                var replacement = new Object();
                for(var p in this){
                    if (typeof (this[p]) === 'string'){
                        replacement[p] = this[p].toUpperCase();
                    }else{
                        replacement[p] = this[p];
                    }
                }
                return replacement;
            }
            console.log(JSON.stringify(rime));

            //>>>----------------------------------------------------------------------------------------------------------
            //7.Date
            console.log("Date----------------------------------------------------------------");
            var day0 = new Date();//表示当前时间
            console.log(day0.toString());
            console.log(day0.getFullYear(), "-", day0.getMonth(), "-", day0.getDate());

            //为什么输出是22号  周四 10月 22 06:24:00 2009 GMT+0800//这种构造方式天数会多一天
            var day1 = new Date("2009-10-21T22:24:00");
            //为什么输出是11月    周六 11月 21 00:00:00 2009 GMT+0800
            var day2 = new Date(2009, 12, 21);//这种和下面这种构造方式月份总是会多一个月，如果是12月就是1月份
            var day3 = new Date(2009, 10, 21, 22, 24, 0);
            console.log(day0);
            console.log(day1);
            console.log(day2);
            console.log(day3);
        }
    }
}
