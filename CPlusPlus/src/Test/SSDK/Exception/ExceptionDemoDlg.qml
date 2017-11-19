import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0

ApplicationWindow {
    id:wndMain;
    visible: true;
    width: 1000;
    height: 1000;
    objectName: exceptionDemoDlg.objectName;

    Item{
        id:rectMain;
        width: wndMain.width;
        height: wndMain.height;
        objectName: "rectMain";

        Button{
            id:btnSDKException;
            text:qsTr("SDK Exception");
            objectName: "SDK";

            onClicked: {
                exceptionDemoDlg.showSDKException();
            }
        }

        Button{
            id:btnJobException;
            text:"Job Exception";
            x:150;
            y:0;
            objectName: "JOB";

            onClicked: {
                exceptionDemoDlg.showJobException();
            }
        }

        Button{
            x:300;
            y:0;
            text:"Hw Exception";

            onClicked: {
                exceptionDemoDlg.showHwException();
            }
        }

        Button{
            x:450;
            y:0;
            text:"Static Function Exception";

            onClicked: {
                exceptionDemoDlg.showStaticFunctionException();
            }
        }

        Button{
            id:btnChange;
            text:"Change Theme";
            x:300;
            y:300;

            onClicked: {
                if(wndMain.Material.theme === Material.Light)
                    wndMain.Material.theme = Material.Dark;
                else
                    wndMain.Material.theme = Material.Light;
            }
        }
    }
}
