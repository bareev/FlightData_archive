import QtQuick 2.0
import QtQuick.Controls 1.0

Image {
    id: canvas_set;
    height: 390;
    width: 680;
    source: "qrc:///res/canvas"
    // Будет получать фокус ввода
    focus: true;
    Text {
        anchors.margins: 4;
        anchors.top: parent.top;
        anchors.centerIn: parent.Center;

        id: captionText;
        height: 35;
        width: parent.width;
        property string vars: "-";
        text: qsTr("ОПИСАНИЕ " + vars + " ФАЙЛОВ");
        font.family: "Helvetica";
        font.pointSize: 21;
        style: Text.Sunken;
        color: "blue";
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    ScrollView {

        id: scroll;
        height: parent.height - 50;
        width: parent.width;
        anchors.top: captionText.bottom;

        ListView {
            id: listView1;
            // Размещаем его в оставшейся части окна приложения
            spacing: 48;
            anchors.top: parent.top;
            anchors.left: parent.left;
            anchors.margins: 4;
            height: scroll.height + listView1.spacing;
            delegate: comp;
            // Сама модель, в которой будут содержаться все элементы
            model: ListModel {
                id: listModel_i; // задаём ей id для обращения
            }

        }
    }

    Row {

        anchors.right: parent.right;
        anchors.rightMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        spacing: 4;

        WindowButtonText {
            id: okSets;
            text: qsTr("Нет действия");
            function callback()
            {
                tableModelDesc.closeSets();
            }
        }

        WindowButtonText {
            id: exitSets;
            text: qsTr("Отмена");
            function callback()
            {
                tableModelDesc.closeSets();
            }
        }

        Connections {
            target: tableModelDesc;
            onParamTextChanged: txtFunc(ft);
        }


    }

    function txtFunc(ft)
    {
        okSets.enabled = true;
        if (ft === 1)
            okSets.text = qsTr("Записать");
        else if (ft === 2)
            okSets.text = qsTr("Обновить");
        else
            okSets.enabled = false;
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
                    text: qsTr("Описание файла ") + filename;
                    width: parent.width;
                }
            }
        }
    }

    Connections {
        id: c1;
        target: tableModelDesc;
        onAddNewRow: newItems(s);
    }

    Connections {
        id: c2;
        target: tableModelDesc;
        onIochange: changeText(p);
    }

    function newItems(qlist)
    {
        listModel_i.clear();
        for (var i = 0; i < qlist.length; i++)
        {
            listModel_i.append({filename: qsTr(qlist[i])});
        }
    }

    function changeText(p)
    {
        if (p === 0)
            captionText.vars = qsTr("ВХОДНЫХ");
        else if (p === 1)
            captionText.vars = qsTr("ВЫХОДНЫХ");
        else
            captionText.vars = "-";
    }


}
