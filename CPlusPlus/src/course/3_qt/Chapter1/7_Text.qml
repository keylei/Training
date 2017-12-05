import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow {
    width:650;
    height:800;
    visible: true;

    Rectangle{
        Text{
            id: txtNormal;
            anchors.left: parent.left;
            anchors.leftMargin: 20;
            anchors.top: parent.top;
            anchors.topMargin: 20;
            font.pointSize: 24;
            text: "Normal Text";
        }

        Text{
            id: txtRaise;
            anchors.left: txtNormal.left;
            anchors.top: txtNormal.bottom;
            anchors.topMargin: 20;
            font.pointSize: 24;
            style: Text.Raised;
            styleColor: "#AAAAAA";
            text: "Raise Text";
        }

        Text{
            id: txtOutline;
            anchors.left: txtRaise.left;
            anchors.top: txtRaise.bottom;
            anchors.topMargin: 20;
            font.pointSize: 24;
            style: Text.Outline;
            styleColor: "red";
            text: "Outline Text";
        }

        Text{
            id: txtSunken;
            anchors.left: txtOutline.left;
            anchors.top: txtOutline.bottom;
            anchors.topMargin: 20;
            font.pointSize: 24;
            style: Text.Sunken;
            styleColor: "#A00000";
            text: "Sunken Text";
        }

        Text{
            id: txtwrapMode;
            anchors.left: txtSunken.left;
            anchors.top: txtSunken.bottom;
            anchors.topMargin: 20;
            width: 400;
            styleColor: "#A00000";
//            wrapMode: Text.Wrap; //如果没有 这一行，文本会超出Text的边界
            text: "The conferences will feature specialized keynote talks, paper presentations, poster presentations,industrial talks, and project demonstrations. Previous conferences include Future Technologies Conference (FTC) in San Francisco, Intelligent Systems Conference (IntelliSys) in London and Computing Conference in London. See videos at youtube.com/SAIConference";
        }
    }


}
