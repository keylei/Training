import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import an.qt.CModel 1.0

ApplicationWindow
{
    visible: true;
    width: 800;
    height: 800;

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

    ListView{
        id: lstVw;
        anchors.fill: parent;
        spacing: 4;
        delegate: videoDelegate;

        //这里引用的VideoListModel其实是来自与C++了
        model: VideoListModel { source: "./videos.xml"; }
        focus: true;
        highlight: Rectangle{
            width: parent.width;
            color: "lightblue";
        }
    }
}

