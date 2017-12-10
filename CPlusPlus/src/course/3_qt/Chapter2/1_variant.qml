import QtQuick 2.7
import QtQuick.Controls 2.0


ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    Button{
        text:"Start";

        onClicked: {
            //变量声明
            var i = 0;

            //1) 变量命名以小写字母开始，单词之间使用驼峰命名法。
//            var isSuccessful = false;
//            var objectName = "obj";
//            var tempValue = 20.1;

            //2)一个var语句可以定义多个变量，可以是不同的类型,
            //   但是公司禁止这么做,为保证阅读性,请一行只放一个类型
//            var index = 0,name = "}";

            //正确做法:
            //            var index = 0;
            //            var name = "}";

            //3)禁止一个变量在使用中变更类型
//            var index = 0;
//            index =  "}";                    //×
//            index =  10;                    //√

            //4)判断2个变量是否相等要用“===”(3个等号)，“===”表示全等，
            //包括值相等和类型相等
//            var index = 5;
//            index ===5                      //√
//            index ==="5"                    //×

            // 5)判断变量的类型不能用typeof而要使用instanceof。因为typeof对于引用值统一返回object，
            //     这就导致了typeof无法准确判断出引用的类型，而instanceof就没有这样的问题，
            //     它能够返回引用对象真实的类型。
//            var str =new String("Hello World");
//            //×  输出固定为“object”
//            console.log(typeof str);

//            //√  输出为true
//            console.log(str instanceof String);


        }
    }
}
