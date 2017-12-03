import QtQuick 2.7

//Page1Form是一种QML子集，推荐使用Design mode，这种格式直接使用Design mode可视化的编辑， 也可以使用文本编辑， 但是有很多
//特性不支持
Page1Form {
    button1.onClicked: {
        console.log("Button Pressed. Entered text: " + textField1.text);
    }
}

