import QtQuick 2.0
import QtQuick.Controls 1.0

Image {
    id: addNew;
    height: 370;
    width: 430;
    source: "qrc:///res/canvas";
    focus: true;

    Text {
        id: captionTextAdd;
        height: 35;
        width: addNew.width;
        text: qsTr("НОВАЯ ЗАПИСЬ");
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

            Text {
                id: dateAndTime;
                text: qsTr("Дата и время полётов");
                font.family: "Helvetica";
                font.pointSize: 10;
                height: 20;

            }

            Text {
                id: type;
                text: qsTr("Тип станции");
                font.family: "Helvetica";
                font.pointSize: 10;
                height: 20;

            }

            Text {
                id: place;
                text: qsTr("Место полётов");
                font.family: "Helvetica";
                font.pointSize: 10;
                height: 20;

            }

            Text {
                id: coord;
                text: qsTr("Точка стояния");
                font.family: "Helvetica";
                font.pointSize: 10;
                height: 20;

            }

            Text {
                id: inputFiles;
                text: qsTr("Исходные файлы");
                font.family: "Helvetica";
                font.pointSize: 10;
                height: 20;

            }

            Text {
                id: outputFiles;
                text: qsTr("Выходные файлы");
                font.family: "Helvetica";
                font.pointSize: 10;
                height: 20;

            }

            Text {
                id: txt;
                text: qsTr("Текстовое описание");
                font.family: "Helvetica";
                font.pointSize: 10;
                height: 20;

            }

        }

        Column {

            spacing: 4;
            id: columnEdit;

            TextEditWidget {
                id: timestart;
                width: 130;
                inputMethodHints: Qt.ImhDigitsOnly;
                inputMask: "9999-99-99 99:99:99";
                text: Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss");
                validator: RegExpValidator { regExp: /^\d\d\d\d-(0?[1-9]|1[0-2])-(0?[1-9]|[12][0-9]|3[01]) (00|[0-9]|1[0-9]|2[0-3]):([0-9]|[0-5][0-9]):([0-9]|[0-5][0-9])$ /; }
            }

            ComboBox {
                id: typecb;
                width: 130;
                model: ListModel {
                    id: cb_1;
                }
            }

            ComboBox {
                id: placecb;
                width: 130;
                model: ListModel {
                    id: cb_2;
                }
                onCurrentTextChanged: windowAdd.loadNewCB(placecb.currentText);
            }

            ComboBox {
                id: coordCB;
                width: 130;
                model: ListModel {
                    id: cb_3;
                }
            }

            TextEditWidget {
                id: inputFilesT;
                width: 130;
            }

            TextEditWidget {
                id: outputFilesT;
                width: 130;
            }

            TextArea
            {
                id: textArea
                width: 260;
                height: 130;
                wrapMode: Text.WordWrap;
                text: "";

//                Keys.onPressed:
//                {
//                    if (event.key === Qt.Key_Tab)
//                    {
//                        insert(cursorPosition, "\t");
//                        event.accepted = true;
//                    }
//                    else if ((event.key === Qt.Key_Backspace) && (textArea.text.length === 0))
//                    {
//                        event.accepted = false;
//                    }
//                }
            }

            Connections {
                target: windowAdd;
                onSigNewRecs: infoCh(s, t);
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
                var res = windowAdd.waitForWritetoDB(timestart.text, typecb.currentText, placecb.currentText, coordCB.currentText, inputFilesT.text, outputFilesT.text, textArea.text);
                if (res === 0)
                {
                    windowAdd.closeSets();

                    var stroka = [inputFilesT.text, outputFilesT.text];
                    for (var k = 0; k < 2; k++)
                    {
                        windowAdd.showDescription(k, stroka[k].split(";"));
                    }
                }
                else
                {
                    ///@warning  - параметры
                }
            }
        }

        WindowButtonText {
            id: exitSets;
            text: qsTr("Отмена");
            function callback()
            {
                windowAdd.closeSets();
            }
        }

        Connections {
            target: windowAdd;
            onParamTextChanged: txtFunc(ft);
        }

        Connections {
            target: windowAdd;
            onWinEnabled: addNew.enabled = e;
        }


    }

    function txtFunc(ft)
    {
        okSets.enabled = true;
        if (ft === 1)
        {
            captionTextAdd.text = qsTr("НОВАЯ ЗАПИСЬ");
            okSets.text = qsTr("Записать");
        }
        else if (ft === 2)
        {
            captionTextAdd.text = qsTr("ОБНОВИТЬ ЗАПИСЬ");
            okSets.text = qsTr("Обновить");
        }
        else
            okSets.enabled = false;
    }

    function infoCh(s, t)
    {
        var i = 0;
        switch (t)
        {
        case 1:
            cb_1.clear();
            for (i = 0; i < s.length; i++)
            {
                cb_1.append({"text":s[i]});
            }
            break;
        case 2:
            cb_2.clear();
            for (i = 0; i < s.length; i++)
            {
                cb_2.append({"text":s[i]});
            }
            break;
        case 3:
            cb_3.clear();
            for (i = 0; i < s.length; i++)
            {
                cb_3.append({"text":s[i]});
            }
            break;
        default:
            break;

        }
    }
}
