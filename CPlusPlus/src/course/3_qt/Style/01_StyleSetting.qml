import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.1
import QtQuick.Controls.Universal 2.1
import Qt.labs.settings 1.0

import an.qt.StyleSetting 1.0

import "../pages";


ApplicationWindow
{
    id: wndMain;
    objectName: "wndMain";
    visible: true;
    width: 1200;
    height: 800;

    StyleSetting{
        id: styleSetting;

        property color accentColor1;
        property color primaryColor1;
        property color foregroundColor1;
        property color backgroundColor1;

        property color accentColor2;
        property color primaryColor2;
        property color foregroundColor2;
        property color backgroundColor2;

        function updateStyle(){
            wndMain.Material.accent = styleSetting.getThemeColor(styleSetting.themeIndex, StyleSetting.ACCENT);
            wndMain.Material.primary = styleSetting.getThemeColor(styleSetting.themeIndex, StyleSetting.PRIMARY);
            wndMain.Material.foreground = styleSetting.getThemeColor(styleSetting.themeIndex, StyleSetting.FORGROUND);
            wndMain.Material.background = styleSetting.getThemeColor(styleSetting.themeIndex, StyleSetting.BACKGROUND);
        }

        Component.onCompleted: {

            //必须把系统的Materil不同Theme的颜色缓存下来，一遍在自定义改了颜色后能够恢复
            var origTheme =  wndMain.Material.theme;
            wndMain.Material.theme = Material.Light;

            styleSetting.setThemeColor(0, StyleSetting.ACCENT, wndMain.Material.accent );
            styleSetting.setThemeColor(0, StyleSetting.PRIMARY, wndMain.Material.primary );
            styleSetting.setThemeColor(0, StyleSetting.FORGROUND, wndMain.Material.foreground );
            styleSetting.setThemeColor(0, StyleSetting.BACKGROUND, wndMain.Material.background );

            wndMain.Material.theme = Material.Dark;

            styleSetting.setThemeColor(1, StyleSetting.ACCENT, wndMain.Material.accent );
            styleSetting.setThemeColor(1, StyleSetting.PRIMARY, wndMain.Material.primary );
            styleSetting.setThemeColor(1, StyleSetting.FORGROUND, wndMain.Material.foreground );
            styleSetting.setThemeColor(1, StyleSetting.BACKGROUND, wndMain.Material.background );

            //这一步很重要，虽然看上去很累赘，但没有这一步会导致主题一直是Dark，暂时还不知道为什么
            wndMain.Material.theme = origTheme;

            styleBox.model = styleSetting.themeList;
            styleBox.currentIndex = styleSetting.themeIndex;
            updateStyle();
        }
    }

    Shortcut {
        sequences: ["Esc", "Back"]
        enabled: stackView.depth > 1
        onActivated: {
            stackView.pop()
            listView.currentIndex = -1
        }
    }

    Shortcut {
        sequence: "Menu"
        onActivated: optionsMenu.open()
    }

    //标示界面的标题栏(上)
    header: ToolBar {
        Material.foreground: "white"

        RowLayout {
            spacing: 20
            anchors.fill: parent

            //左边的按钮
            ToolButton {
                icon.name: stackView.depth > 1 ? "back" : "drawer"
                onClicked: {
                    if (stackView.depth > 1) {
                        stackView.pop()
                        listView.currentIndex = -1
                    } else {
                        drawer.open()
                    }
                }
            }

            //最中间的标题
            Label {
                id: titleLabel
                text: listView.currentItem ? listView.currentItem.text : "Scijet"
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            //右边的按钮
            ToolButton {
                icon.name: "menu"
                onClicked: optionsMenu.open()

                //选项菜单
                Menu {
                    id: optionsMenu;
                    x: parent.width - width;//保证出现在界面的最右端
                    transformOrigin: Menu.TopRight

                    MenuItem {
                        text: "Settings"
                        onTriggered: settingsDialog.open()
                    }
                    MenuItem {
                        text: "About"
                        onTriggered: aboutDialog.open()
                    }
                }
            }
        }
    }

    //设置界面
    Settings {
        id: settings
        property string style: "Default"
    }

    Dialog {
        id: settingsDialog
        x: Math.round((wndMain.width - width) / 2)
        y: Math.round(wndMain.height / 6)
        width: Math.round(Math.min(wndMain.width, wndMain.height) / 3 * 2)
        modal: true
        focus: true
        title: "Settings"

        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            //            settings.style = styleBox.displayText
            styleSetting.themeIndex = styleBox.currentIndex;
            styleSetting.updateStyle();
        }
        onRejected: {
            styleBox.currentIndex = styleBox.styleIndex
            //            settingsDialog.close();
//            wndMain.Material.theme = Material.Light;
        }

        contentItem: ColumnLayout {
            id: settingsColumn
            spacing: 20

            RowLayout {
                spacing: 10

                Label {
                    text: "Style:"
                }

                ComboBox {
                    id: styleBox;

                    property int styleIndex: -1

                    Component.onCompleted: {
//                        changeStyle(styleBox.displayText);
//                        styleBox.model = styleSetting.themeList;
////                        styleBox.currentIndex = styleSetting.themeIndex;
//                        styleSetting.changeStyle(styleBox.displayText);
                    }
                    Layout.fillWidth: true;
                }
            }

            Label {
                text: "Restart required"
                color: "#e41e25"
                opacity: styleBox.currentIndex !== styleBox.styleIndex ? 1.0 : 0.0
                horizontalAlignment: Label.AlignHCenter
                verticalAlignment: Label.AlignVCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }

    Dialog {
        id: aboutDialog
        modal: true
        focus: true
        title: "About"
        x: (wndMain.width - width) / 2
        y: wndMain.height / 6
        width: Math.min(wndMain.width, wndMain.height) / 3 * 2
        contentHeight: aboutColumn.height

        Column {
            id: aboutColumn
            spacing: 20

            Label {
                width: aboutDialog.availableWidth
                text: "The Qt Quick Controls 2 module delivers the next generation user interface controls based on Qt Quick."
                wrapMode: Label.Wrap
                font.pixelSize: 12
            }

            Label {
                width: aboutDialog.availableWidth
                text: "In comparison to the desktop-oriented Qt Quick Controls 1, Qt Quick Controls 2 "
                      + "are an order of magnitude simpler, lighter and faster, and are primarily targeted "
                      + "towards embedded and mobile platforms."
                wrapMode: Label.Wrap
                font.pixelSize: 12
            }
        }
    }

    //侧边栏
    Drawer {
        id: drawer
        width: Math.min(wndMain.width, wndMain.height) / 3 * 2
        height: wndMain.height
        interactive: stackView.depth === 1

        ListView {
            id: listView

            focus: true
            currentIndex: -1
            anchors.fill: parent

            delegate: ItemDelegate {
                width: parent.width
                text: model.title
                highlighted: ListView.isCurrentItem
                onClicked: {
                    listView.currentIndex = index
                    stackView.push(model.source)
                    drawer.close()
                }
            }

            model: ListModel {
                ListElement { title: "BusyIndicator"; source: "../pages/BusyIndicatorPage.qml" }
                ListElement { title: "Button"; source: "../pages/ButtonPage.qml" }
                ListElement { title: "CheckBox"; source: "../pages/CheckBoxPage.qml" }
                ListElement { title: "ComboBox"; source: "../pages/ComboBoxPage.qml" }
                ListElement { title: "DelayButton"; source: "../pages/DelayButtonPage.qml" }
                ListElement { title: "Dial"; source: "../pages/DialPage.qml" }
                ListElement { title: "Dialog"; source: "../pages/DialogPage.qml" }
                ListElement { title: "Delegates"; source: "../pages/DelegatePage.qml" }
                ListElement { title: "Frame"; source: "../pages/FramePage.qml" }
                ListElement { title: "GroupBox"; source: "../pages/GroupBoxPage.qml" }
                ListElement { title: "PageIndicator"; source: "../pages/PageIndicatorPage.qml" }
                ListElement { title: "ProgressBar"; source: "../pages/ProgressBarPage.qml" }
                ListElement { title: "RadioButton"; source: "../pages/RadioButtonPage.qml" }
                ListElement { title: "RangeSlider"; source: "../pages/RangeSliderPage.qml" }
                ListElement { title: "ScrollBar"; source: "../pages/ScrollBarPage.qml" }
                ListElement { title: "ScrollIndicator"; source: "../pages/ScrollIndicatorPage.qml" }
                ListElement { title: "Slider"; source: "../pages/SliderPage.qml" }
                ListElement { title: "SpinBox"; source: "../pages/SpinBoxPage.qml" }
                ListElement { title: "StackView"; source: "../pages/StackViewPage.qml" }
                ListElement { title: "SwipeView"; source: "../pages/SwipeViewPage.qml" }
                ListElement { title: "Switch"; source: "../pages/SwitchPage.qml" }
                ListElement { title: "TabBar"; source: "../pages/TabBarPage.qml" }
                ListElement { title: "TextArea"; source: "../pages/TextAreaPage.qml" }
                ListElement { title: "TextField"; source: "../pages/TextFieldPage.qml" }
                ListElement { title: "ToolTip"; source: "../pages/ToolTipPage.qml" }
                ListElement { title: "Tumbler"; source: "../pages/TumblerPage.qml" }
            }

            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: Pane {
            id: pane;

            SwipeView {
                id: swipeView;
                anchors.fill: parent;
                currentIndex: tabBar.currentIndex;

                Repeater {
                    model: 3

                    Pane {
                        width: swipeView.width
                        height: swipeView.height

                        Column {
                            spacing: 40
                            width: parent.width

                            Label {
                                width: parent.width
                                wrapMode: Label.Wrap
                                horizontalAlignment: Qt.AlignHCenter
                                text: tabBar.currentIndex;
                            }

                            Image {
                                source: "../Images/arrows.png"
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                    }
                }
            }

            TabBar{
                id: tabBar;
                width: parent.width;
                anchors.bottom: parent.bottom;
                currentIndex: swipeView.currentIndex;

                TabButton {
                    text: "First"
                }
                TabButton {
                    text: "Second"
                }
                TabButton {
                    text: "Third"
                }
            }
        }
    }
}
