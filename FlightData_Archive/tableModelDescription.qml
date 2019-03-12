import QtQuick 2.0
import QtQuick.Controls 1.0

Image {
    id: canvas_set;
    height: 416;
    width: 720;
    source: "qrc:///res/canvas"
    // Будет получать фокус ввода
    focus: true;

    ListView {
        id: listView1;
        // Размещаем его в оставшейся части окна приложения
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.topMargin: 4;
        anchors.leftMargin: 4;

        delegate: Column {
            id: item
            anchors.left: parent.left;
            anchors.top: parent.top;
            spacing: 4;

            Text {
                id: txt1;
                text: idtext;
                font.family: "Helvetica";
                font.pointSize: 9;
            }

            TextEditWidget {
                id: txtEdit1;
                text: qsTr("Описание файла ... ");
            }
        }

        // Сама модель, в которой будут содержаться все элементы
        model: ListModel {
            id: listModel; // задаём ей id для обращения
        }
    }

    Connections {
        target: tableModelDesc;
        onAddNewRow: newItems(s);
    }


    function newItems(qlist)
    {
        for (i = 0; i < qlist.length(); i++)
        {
            listModel.append({idtext: qsTr(qlist.at(i))});
        }
    }


}
