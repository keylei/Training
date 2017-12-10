import QtQuick 2.7
import QtQuick.Controls 2.0


ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    function func()
    {

    }

    Button{
        text:"Start";
        anchors.topMargin: 20;
        anchors.leftMargin: 20;

        onClicked: {

            // 1.ECMAScript有5中原始类型，即Undefined/Null/Boolean/Number/String
            var name="Rime";
            console.log(name);
            console.log(typeof name);
            name[0]="S"; //字符串其每个索引位置是不可修改的
            console.log(name);

            //Undefined当声明的变量没有初始化时
            var rime;
            console.log(typeof rime);
            //当函数没有明确的返回值时，返回值也是undefined
            console.log(typeof func());

            // 可以显式的将一个变量初始化为null
            var lynn=null;
            console.log(lynn === null);

            //Number可以标示32位的整数，也可以表示64的浮点数
            var integer = 10;
            var hexNumber = 0x1f;
            var percent = 0.33;
            var fNumber = 3.14e8;

            //数字类型的最大值为Number.MAX_VALUE, 最小值是NUMBER.MIN_VALUE
            console.log(Number.MAX_VALUE);
            console.log(Number.MIN_VALUE);

            console.log(Number.POSITIVE_INFINITY == 1/0)
            console.log(Number.NEGATIVE_INFINITY == -1/0)

            //判断一个数非数，推荐使用isNaN
            console.log(isNaN(name));
            console.log(isNaN(fNumber));

            //2.类型转化
            //boolean,number, string都有toString方法
            console.log("ToString()---------------------------------------------");
            console.log(integer.toString());
            console.log(name.toString());
            console.log(true.toString());
            console.log(integer.toString(8));

            console.log("Parse--------------------------------------------------");
            console.log(parseInt("2014年"));
            console.log(parseInt("0xC"));
            console.log(parseInt("3.14"));
            console.log(parseInt("green"));
            console.log(parseFloat("3.14159"));
            console.log(parseFloat("1.3.3"));
            console.log(parseFloat("Am I Float"));
            console.log(parseInt("AK47",16)); //想下为什么会是10
            console.log(parseInt("AK47",10));
            console.log(parseInt("010",8));
            console.log(parseInt("010",10));

            console.log("强制类型转换--------------------------------------");
            console.log(Boolean(""));
            console.log(Boolean("Qt"));
            console.log(Boolean(456));
            console.log(Boolean(0));
            console.log(Boolean(null));
            console.log(Boolean(new Array()));

            console.log(Number("250"));
            console.log(Number("1.3"));

            console.log(String(null));
        }
    }
}
