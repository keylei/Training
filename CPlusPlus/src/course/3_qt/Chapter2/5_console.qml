import QtQuick 2.7
import QtQuick.Controls 2.0


ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    Button{
        text: "console";
        onClicked:{

            console.log("I\' m minor, ☺ ");
            console.log("I\'m 16");

            var array = new Array(10,12,8,"Anna");
            console.debug("print array:", array);

            //    在QML中，推荐使用console.assert()，当使用console.assert在表达式不成立时并不会终止
            //    程序，而是会打印出错误的代码位置。
            var x = 12
            console.assert(x == 12, "This will pass");
            console.assert(x > 12, "This will fail");

            // console.time(tag)启动定时器，字符串类型tag是必需的
            // console.timeEnd(tag)停止计时器，在控制台输出某个标签对应的耗时信息
            console.time("wholeFunction");
            console.time("firstPart");

            // first part
            console.timeEnd("firstPart");
            // second part
            console.timeEnd("wholeFunction");
        }
    }
}
