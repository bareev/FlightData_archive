import QtQuick 2.0
import QtQuick.Controls 1.0

Image {
    id: canvas_set;
    height: 416;
    width: 720;
    source: "qrc:///res/canvas"
    // Будет получать фокус ввода
    focus: true;

    ScrollView {

        id: scroll;
        height: parent.height;
        width: parent.width;

        ListView {
            id: listView1;
            // Размещаем его в оставшейся части окна приложения
            spacing: 48;
            anchors.top: parent.top;
            anchors.left: parent.left;
            anchors.margins: 4;
            height: scroll.height + 100;
            delegate: comp;
            // Сама модель, в которой будут содержаться все элементы
            model: ListModel {
                id: listModel_i; // задаём ей id для обращения
            }

        }
    }

    Component {
        id: comp;
        Item {
            id: item1;

            Column {
                id: item;
                width: scroll.width - 30;
                spacing: 1;
                Text {
                    id: txt1;
                    text: filename;
                    font.family: "Helvetica";
                    font.pointSize: 9;
                    width: parent.width;
                }
                TextEditWidget {
                    id: txtEdit1;
                    text: qsTr("Описание файла ") + yparam;
                    width: parent.width;
                }
            }
        }
    }

    Connections {
        target: tableModelDesc;
        onAddNewRow: newItems(s);
    }

    function newItems(qlist)
    {
        listModel_i.clear();
        for (var i = 0; i < qlist.length; i++)
        {
            listModel_i.append({filename: qsTr(qlist[i])});
        }
    }

}
