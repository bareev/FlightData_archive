import QtQuick 2.0
import QtQuick.Controls 1.0

Image {
    id: addNew;
    height: 416;
    width: 720;
    source: "qrc:///res/canvas";
    focus: true;

    Text {
        id: captionTextAdd;
        height: 35;
        width: addNew.width;
        text: qsTr("ДОБАВИТЬ НОВУЮ ЗАПИСЬ ПОЛЁТНЫХ ДАННЫХ");
        font.family: "Helvetica";
        font.pointSize: 21;
        style: Text.Sunken;
        color: "blue";
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;

    }

    Grid {
        id: gr;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.rightMargin: 4;
        anchors.top: captionTextAdd.bottom;
        anchors.topMargin: 4;
        spacing: 15;

        Column {

            spacing: 4;
            id: columns;
            anchors.left: parent.left;
            anchors.leftMargin: 4;
            anchors.top: parent.top;
            anchors.topMargin: 4;

            Row {
                spacing: 4;
                id: row1;
                anchors.left: parent.left;
                anchors.leftMargin: 4;

                Text {
                    id: dateAndTime;
                    text: qsTr("Дата и время полётов");
                    font.family: "Helvetica";
                    font.pointSize: 10;

                }

                TextEditWidget {

                    id: timestart;
                    width: 130;
                    inputMethodHints: Qt.ImhDigitsOnly;
                    inputMask: "9999-99-99 99:99:99";
                    text: Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss");
                    validator: RegExpValidator { regExp: /^\d\d\d\d-(0?[1-9]|1[0-2])-(0?[1-9]|[12][0-9]|3[01]) (00|[0-9]|1[0-9]|2[0-3]):([0-9]|[0-5][0-9]):([0-9]|[0-5][0-9])$ /; }

                }

            }

            Row {
                spacing: 4;
                id: row2;
                anchors.left: parent.left;
                anchors.leftMargin: 4;

                Text {
                    id: type;
                    text: qsTr("Тип станции                 ");
                    font.family: "Helvetica";
                    font.pointSize: 10;

                }

                ComboBox {
                    id: typecb;
                    width: 130;
                }

            }

            Row {
                spacing: 4;
                id: row3;
                anchors.left: parent.left;
                anchors.leftMargin: 4;

                Text {
                    id: place;
                    text: qsTr("Место полётов            ");
                    font.family: "Helvetica";
                    font.pointSize: 10;

                }

                ComboBox {
                    id: placecb;
                    width: 130;
                }

            }

            Row {
                spacing: 4;
                id: row4;
                anchors.left: parent.left;
                anchors.leftMargin: 4;

                Text {
                    id: coord;
                    text: qsTr("Точка стояния             ");
                    font.family: "Helvetica";
                    font.pointSize: 10;

                }

                ComboBox {
                    id: coordCB;
                    width: 130;
                }

            }

            Row {
                spacing: 4;
                id: row5;
                anchors.left: parent.left;
                anchors.leftMargin: 4;

                Text {
                    id: inputFiles;
                    text: qsTr("Исходные файлы             ");
                    font.family: "Helvetica";
                    font.pointSize: 10;

                }

                TextEditWidget {
                    id: inputFilesT;
                    width: 130;
                }

            }

            Row {
                spacing: 4;
                id: row6;
                anchors.left: parent.left;
                anchors.leftMargin: 4;

                Text {
                    id: outputFiles;
                    text: qsTr("Выходные файлы             ");
                    font.family: "Helvetica";
                    font.pointSize: 10;

                }

                TextEditWidget {
                    id: outputFilesT;
                    width: 130;
                }

            }

            Row {
                spacing: 4;
                id: row7;
                anchors.left: parent.left;
                anchors.leftMargin: 4;

                Text {
                    id: txt;
                    text: qsTr("Текстовое описание   ");
                    font.family: "Helvetica";
                    font.pointSize: 10;

                }

                TextArea
                {
                    id: textArea
                    width: 260;
                    height: 130;
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
    }

}
