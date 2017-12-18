import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow
{
    visible: true;
    width: 800;
    height: 800;

    //ListView显示一个条目，对应的数据来自于Model，每个条目的外观有Delegate决定
    //Delegate
    Component{
        id: phoneDelegate;
        Item{
            id: itemWrapper;
            width: parent.width;
            height: 30;

            MouseArea {
                anchors.fill: parent;
                //单击更新索引
                onClicked: {
                    //Item都有一个ListView属性
                    itemWrapper.ListView.view.currentIndex = index;
                    mouse.accept = true;
                }

                //双击删除数据
                onDoubleClicked: {
                    //删除一条数据，可以使用ListModel中的remove(int index, int count)方法
                    //如果想清空一个Model，可以直接调用clear方法
                    itemWrapper.ListView.view.model.remove(index);
                    mouse.accept = true;
                }
            }

            RowLayout{
                anchors.left: parent.left;
                anchors.verticalCenter: parent.verticalCenter;
                spacing: 8;
                Text{
                    id: txtCol;
                    text: name;
                    color: itemWrapper.ListView.isCurrentItem ? "red":"black";
                    font.pixelSize: itemWrapper.ListView.isCurrentItem ? 22 : 18;
                    Layout.preferredWidth: 150;
                }

                Text{
                    id: txtCost;
                    text: cost;
                    color: itemWrapper.ListView.isCurrentItem ? "red":"black";
                    font.pixelSize: itemWrapper.ListView.isCurrentItem ? 22 : 18;
                    Layout.preferredWidth: 80;
                }

                Text{
                    text: manufacturer;
                    color: itemWrapper.ListView.isCurrentItem ? "red":"black";
                    font.pixelSize: itemWrapper.ListView.isCurrentItem ? 22 : 18;
                    Layout.fillWidth: true;
                }
            }
        }
    }

    //Header
    Component{
        id: headerVw;
        Item{
            width: parent.width;
            height: 30;
            RowLayout{
                anchors.left: parent.left;
                anchors.verticalCenter: parent.verticalCenter;
                spacing: 8;
                Text{
                    text: "Name";
                    font.bold: true;
                    font.pixelSize: 20;
                    Layout.preferredWidth: 150;
                }

                Text{
                    text: "Cost";
                    font.bold: true;
                    font.pixelSize: 20;
                    Layout.preferredWidth: 80;
                }

                Text{
                    text: "Manufacturer";
                    font.bold: true;
                    font.pixelSize: 20;
                    Layout.fillWidth: true;
                }
            }
        }
    }

    //Footer
    Component{
        id: footerVw;

        Item{
            id: footerRootItem;
            width: parent.width;
            height: 30;

            property alias text: txtFooter.text;

            signal clean();
            signal add();

            Text{
                id: txtFooter;
                width:  parent.width;
                font.italic: true;
                color: "blue";
                height: 30;
                verticalAlignment: Text.AlignVCenter;
            }

            //添加一个清除按钮，清除所有的数据
            Button{
                id: btnClear;
                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;
                text: "Clear";
                onClicked: {
                    footerRootItem.clean();
                }
            }

            //添加一个追加记录按钮
            Button{
                id: btnAddOne;
                anchors.right: btnClear.left;
                anchors.rightMargin: 4;
                anchors.verticalCenter: parent.verticalCenter;
                text: "Add";
                onClicked: {
                    footerRootItem.add();
                }
            }
        }
    }//End of footerVw

    //根据model的role-name来给Item分组
    //Section
    Component{
        id: sectionHeader;
        Rectangle{
            width: parent.width;
            height: childrenRect.height;
            color: "lightsteelblue";
            Text {
                text: section;
                font.bold: true;
                font.pixelSize: 20;
            }
        }
    }//End of sectionHeader

    //ListView
    ListView{
        id: lstVw;
        anchors.fill: parent;
        delegate: phoneDelegate;
        // 设置一个Component，自定义表头，表头就是放在ListView的最开始
        header: headerVw;
        // footer属性指定了ListView的页脚，这个Item会添加到ListView末尾
        footer: footerVw;

        //        这里的model全部在QML中定义，实际上更多时候为了效率全部在C++中定义
        //        ListModel是专门定义数据的
        model: ListModel{
            id: phoneModel;

            //一个ListElement对象就代表一条数据
            ListElement{
                //role-name必须以小写字母开头，role-value必须是简单的常量
                //在Delegate中通过role-name访问
                name: "iPhone 3GS";
                cost: "1000";
                manufacturer: "Apple";
            }

            ListElement{
                name: "iPhone 4";
                cost: "1800";
                manufacturer: "Apple";
            }

            ListElement{
                name: "iPhone 4S";
                cost: "2300";
                manufacturer: "Apple";
            }

            ListElement{
                name: "iPhone 5";
                cost: "4900";
                manufacturer: "Apple";
            }

            ListElement{
                name: "B199";
                cost: "1590";
                manufacturer: "HuaWei";
            }

            ListElement{
                name: "iPhone 3GS";
                cost: "1000";
                manufacturer: "Apple";
            }

            ListElement{
                name: "MI 2s";
                cost: "1999";
                manufacturer: "XiaoMi";
            }

            ListElement{
                name: "GALAXY S5";
                cost: "4699";
                manufacturer: "Samsung";
            }
        }

        focus: true;
        highlight: Rectangle{
            color: "lightblue";
        }

        onCurrentIndexChanged:{
            if( lstVw.currentIndex >=0 ){
                //get方法接受一个int类型的参数，用来获取指定索引位置的数据
                var data = lstVw.model.get(lstVw.currentIndex);
                lstVw.footerItem.text = data.name + " , " + data.cost + " , " + data.manufacturer;
            }
        }

        Component.onCompleted: {
            lstVw.footerItem.clean.connect(lstVw.model.clear);
            lstVw.footerItem.add.connect(lstVw.addOne);
        }

        //添加一条记录
        function addOne(){
            lstVw.model.append({
                                   "name":  "MX3",
                                   "cost":  "1799",
                                   "manufacturer": "MeiZu"
                               })
        }

        //指明分组的依据，以下是按照manufacturer分类
        section.property: "manufacturer";
        //全串匹配
        section.criteria: ViewSection.FullString;
        //指定delegate，决定如何显示每个section
        section.delegate: sectionHeader;
    }//End of ListView
}
