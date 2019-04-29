import QtQuick 2.0
import QtQuick.Controls 1.0

Image {
    id: canvasInitial;
    width: 270;
    height: 50;
    source: "qrc:///res/canvas";
    focus: true;

    Column {
        id:col;
        spacing: 4;
        anchors.margins: 4;
        anchors.top: canvasInitial.top;
        anchors.left: canvasInitial.left;

        Text {
            id: txt;
            width: canvasInitial.width - 15;
            text: qsTr("Копирование базы данных...");
            height: 20;
        }
    }

    Connections {
        target: initialW;
        onSaveCopyText: whoIs(e);
    }

    Connections {
        target: initialW;
        onWinEnabled: canvasInitial.enabled = e;
    }

    function whoIs(e)
    {
        var s = (e?qsTr("Сохранение базы данных в сеть"):qsTr("Копирование базы данных на локальный компьютер"));
        txt.text = s;
    }
}
