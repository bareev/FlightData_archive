import QtQuick 2.0
import QtQuick.Controls 1.0

Image {
    width: 100;
    height: 50;
    source: "qrc:///res/canvas";
    id: canvas;

    Column {
        id:col;
        spacing: 4;
        anchors.margins: 4;
        anchors.top: parent.top;
        anchors.left: parent.left;

        Text {
            id: txt;
            width: canvas.width - 15;
            text: qsTr("Копирование базы данных...");
            height: 20;
        }

        /*ProgressBar {
            id: pb;
            width: canvas.width - 15;
            height: 20;
            value: 0;

            /*Connections {
                target: initialW;
                onGetbytes: pb.value = b;
            }*/
        //}
    }
}
