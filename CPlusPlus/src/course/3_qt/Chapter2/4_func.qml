import QtQuick 2.7
import QtQuick.Controls 2.0


ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    //注意:对于函数的命名使用驼峰命名法，小写字母开头，单词直接不加下划线，
    //对于方法中形参的命名同样遵守这一原则。
    function add(num1, num2){
        var result = num1 + num2;
        console.log(num1, "+", num2, "=", result);
        return result;
    }

    Button{
        text: "add";
        onClicked:{
            var ret = add(100,34);
            console.log(ret);
        }
    }
}
