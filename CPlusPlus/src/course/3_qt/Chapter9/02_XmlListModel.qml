import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
//要使用XmlListModel，需要导入相应的模块
import QtQuick.XmlListModel 2.0

ApplicationWindow
{
    visible: true;
    width: 800;
    height: 800;

    //XmlListModel用于从XML数据中创建一个只读的model，它可以作为各种View的数据源
    //XmlListModel
    Component{
        id: compVideoModel;
        XmlListModel{
            id: xmlModel;
            //指定一个xml格式文件的路径
            source: "videos.xml";
            //一个XPath表达式，一个相对于XmlListModel的query属性的路径
            //指定待体局的数据类型，这是通过一个表达式末尾添加一个/type()
            //来实现的
            query: "/videos/video";

            //使用xmlRole来定义一个数据的一个role，如果一个数据有多个role，则可以通过
            //多个xmlRole对象来定义
            XmlRole{ name: "name"; query: "@name/string()" ;}
            XmlRole{ name: "date"; query: "@date/string()" ;}
            XmlRole{ name: "img"; query: "poster/@img/string()" ;}
            XmlRole{ name: "director_tag"; query: "attr[1]/@tag/string()" ;}
            XmlRole{ name: "director"; query: "attr[1]/string()" ;}
            XmlRole{ name: "actor_tag"; query: "attr[2]/@tag/string()" ;}
            XmlRole{ name: "actor"; query: "attr[2]/string()" ;}
            XmlRole{ name: "rating"; query: "attr[3]/number()" ;}
            XmlRole{ name: "desc"; query: "attr[4]/string()" ;}
            XmlRole{ name: "playtime"; query: "playtimes/number()" ;}
        }
    }//End of XmlListModel

    //Delegate
    Component{
        id: videoDelegate;
        Item{
            id: itemWrapper;
            width: parent.width;
            height: 150;
            MouseArea{
                anchors.fill: parent;
                onClicked: {
                    itemWrapper.ListView.view.currentIndex = index;
                }
            }

            Image{
                    id: imgPoster;
                    anchors.left: parent.left;
                    anchors.top: parent.top;
                    source: img;
                    width: 80;
                    height: 120;
                    fillMode: Image.PreserveAspectFit;
            }

            ColumnLayout{
                anchors.left: imgPoster.right;
                anchors.leftMargin: 4;
                anchors.right: itemWrapper.right;
                anchors.top: imgPoster.top;
                height: parent.height;
                spacing: 2;

                //name rating playtime
                Text{
                    Layout.fillWidth: true;
                    text: "<b>" + name + "</b>" + rating + "," + playtime + ")";
                    color: itemWrapper.ListView.isCurrentItem ? "blue" : "black";
                    font.pixelSize: 18;
                    elide: Text.ElideRight;
                }

                //date
                Text{
                    Layout.fillWidth: true;
                    text: date;
                    color: itemWrapper.ListView.isCurrentItem ? "blue" : "black";
                    font.pixelSize: 18;
                    elide: Text.ElideRight;
                }

                //director_tag/director
                Text{
                    Layout.fillWidth: true;
                    text: director_tag + ": <font color=\"#0000aa\">"+ director + "</font>";
                    color: itemWrapper.ListView.isCurrentItem ? "blue" : "black";
                    font.pixelSize: 18;
                    elide: Text.ElideRight;
                }

                //actor_tag/actor
                Text{
                    Layout.fillWidth: true;
                    text: actor_tag + ": <font color=\"#0000aa\">"+ actor + "</font>";
                    color: itemWrapper.ListView.isCurrentItem ? "blue" : "black";
                    font.pixelSize: 18;
                    elide: Text.ElideRight;
                }

                //desc
                Text{
                    Layout.fillWidth: true;
                    text: desc;
                    Layout.fillHeight: true;
                    color: itemWrapper.ListView.isCurrentItem ? "blue" : "black";
                    font.pixelSize: 16;
                    wrapMode: Text.Wrap;
                    maximumLineCount: 2;
                    elide: Text.ElideRight;
                }
            }
        }
    }

    //ListView
    ListView{
        id: lstVw;
        anchors.fill: parent;
        spacing: 4;
        delegate: videoDelegate;
        model: compVideoModel.createObject(lstVw);
        focus: true;
        highlight: Rectangle{
            width: parent.width;
            color: "lightblue";
        }
    }
}

