import QtQuick 2.0
import QtQuick.Controls 1.0

Image {
    id: canvas_set;
    height: 400;
    width: 500;
    source: "qrc:///res/canvas"
    // Будет получать фокус ввода
    focus: true;

    Column {

        id: col;
        anchors.top: parent.top;
        anchors.margins: 4;
        spacing: 4;
        anchors.left: parent.left;

        Text {
            id: captionText;
            height: 35;
            width: parent.width;
            text: qsTr("НАСТРОЙКИ ТИПОВ");
            font.family: "Helvetica";
            font.pointSize: 21;
            style: Text.Sunken;
            color: "blue";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        Text {
            id: typeCaption;
            height: 20;
            text: qsTr("Выбор типов");
            width: 150;
        }

        Row {
            id: r;
            //anchors.margins: 4;
            //anchors.top: parent.top;
            //anchors.left: parent.left;
            spacing: 4;

            ComboBox {
                id: cb;
                enabled: !(isNew.checked);
                width: 150;
            }

            CheckBox {
                checked: true;
                id: isNew;
                width: 150;
                text: qsTr("Ввести новый тип данных");
            }

        }

        Row {
            //anchors.top:
            spacing: 4;
            id: rt;

            Text {
                id: newType;
                text: qsTr("Сокращение");
                width: 150;
            }

            TextEditWidget {
                id: twt;
                width: 150;
                text: qsTr("");
            }
        }

        Row {
            //anchors.top:
            spacing: 4;
            id: rn;

            Text {
                id: newName;
                text: qsTr("Наименование");
                width: 150;
            }

            TextEditWidget {
                id: twn;
                width: 150;
                text: qsTr("");
            }
        }

        Row {
            //anchors.top:
            spacing: 4;
            id: rowC;

            Text {
                id: newCoord;
                text: qsTr("Координаты точки стояния");
                width: 150;
            }

            TextEditWidget {
                id: twla;
                width: 150;
                text: qsTr("");
            }

            TextEditWidget {
                id: twlo;
                width: 150;
                text: qsTr("");
            }
        }

        Row {
            //anchors.top:
            spacing: 4;
            id: rd;

            Text {
                id: newDesc;
                text: qsTr("Текстовое описание");
                width: 150;
            }

            TextArea {
                id: tad;
                width: 304;
                height: 150;
                text: qsTr("");
                wrapMode: Text.WordWrap;
                Keys.onPressed:
                {
                    if (event.key === Qt.Key_Tab)
                    {
                        insert(cursorPosition, "\t");
                        event.accepted = true;
                    }
                }
            }

        }

    }

    Connections {
        target: windowSetsType;
        onNewState: generalf(e);
    }

    function generalf(e)
    {
        switch (e)
        {

            case 1:
                captionText.text = qsTr("НАСТРОЙКИ ТИПОВ СТАНЦИЙ");
                typeCaption.text = qsTr("Выбор типов станций");
                rowC.enabled = false;
            break;

            case 2:
                captionText.text = qsTr("НАСТРОЙКИ МЕСТ ПОЛЁТОВ");
                typeCaption.text = qsTr("Выбор мест полётов");
                rowC.enabled = false;
            break;

            case 3:
                captionText.text = qsTr("НАСТРОЙКИ ТОЧЕК СТОЯНИЯ");
                typeCaption.text = qsTr("Выбор точек стояния");
                rowC.enabled = true;
            break;

            default:
                captionText.text = qsTr("НАСТРОЙКИ ТИПОВ");
                typeCaption.text = qsTr("Выбор типов");
                rowC.enabled = false;
            break;

        }

        return;
    }
}
