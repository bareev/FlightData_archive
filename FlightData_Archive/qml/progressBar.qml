import QtQuick 2.0
import QtQuick.Controls 1.0

Image {
    width: 200;
    height: 100;
    source: "qrc:///res/canvas";
    id: canvas;

    Column {
        id:col;
        spacing: 4;
        anchors.margins: 4;
        anchors.top: canvas.top;
        anchors.left: canvas.left;

        Text {
            id: txt;
            width: canvas.width - 15;
            text: qsTr("Копирование базы данных...");
            height: 20;
        }
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


    Connections {
        target: initialW;
        onSaveCopyText: whoIs(e);
    }

    function whoIs(e)
    {
        var s = (e?qsTr("Копирование базы данных на локальный компьютер"):qsTr("Сохранение базы данных в сеть"));
        txt.text = s;
    }
}
