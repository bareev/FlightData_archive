import QtQuick 2.0
import QtQuick.Controls 1.0

Image {
    id: canvas_set;
    height: 372;
    width: 465;
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
            spacing: 4;

            ComboBox {
                id: cb;
                enabled: !(isNew.checked);
                width: 150;
                model: tp;
            }

            CheckBox {
                checked: true;
                id: isNew;
                width: 150;
                text: qsTr("ВВЕСТИ НОВУЮ ЗАПИСЬ");
                onCheckedChanged: windowSetsType.loadFromDB(isNew.checked, cb.currentText);
            }

            ListModel {
                id: tp;
            }

        }

        Row {
            spacing: 4;
            id: rn;

            Text {
                id: newName;
                text: qsTr("Наименование (20 символов)");
                width: 150;
            }

            TextEditWidget {
                id: twn;
                width: 150;
                text: qsTr("");
            }
        }

        Row {
            id: pts;
            spacing: 4;

            Text {
                id: newCoordPl;
                text: qsTr("Местоположение");
                width: 150;
            }

            ComboBox {
                id: ptscb;
                enabled: true;
                width: 150;
                model: pp;
            }

            ListModel {
                id: pp;
            }

        }

        Row {
            //anchors.top:
            spacing: 4;
            id: rowC;
            enabled: true;

            Text {
                id: newCoord;
                text: qsTr("Координаты точки стояния");
                width: 150;
            }

            TextEditWidget {
                id: twla;
                width: 150;
                text: qsTr("");
                validator: DoubleValidator;
            }

            TextEditWidget {
                id: twlo;
                width: 150;
                text: qsTr("");
            }
        }

        Row {
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

    Row {
        anchors.margins: 4;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        spacing: 4;

        WindowButtonText {
            id: apply;
            text: qsTr("Применить");
            function callback()
            {
                var res = windowSetsType.newDBWrite(isNew.checked, cb.currentText, twn.text, ptscb.currentText, twla.text, twlo.text, newDesc.text);
                if (res === 0)
                {
                    windowSetsType.closeSets();
                }
            }
        }

        WindowButtonText {
            id: ok;
            text: qsTr("OK");
            function callback()
            {
                var res = windowSetsType.newDBWrite(isNew.checked, cb.currentText, twn.text, ptscb.currentText, twla.text, twlo.text, newDesc.text);
            }
        }

        WindowButtonText {
            id: cancel;
            text: qsTr("Отмена");
            function callback()
            {
                windowSetsType.closeSets();
            }
        }

        WindowButtonText {
            id: delrec;
            text: "Удалить";
            function callback()
            {
                windowSetsType.closeSets();
            }
            visible: !(isNew.checked);

        }

    }

    Connections {
        target: windowSetsType;
        onSigNewRecs: infoCh(s, t);
    }

    Connections {
        target: windowSetsType;
        onFillCurrentInfo: fillInfo(w, desr, parentPl, lat, lon);
    }

    function fillInfo(w, desr, parentPl, lat, lon)
    {
        tad.text = qsTr(desr);
        twla.text = qsTr("");
        twlo.text = qsTr("");
        ptscb.currentIndex = 0;

        switch (w)
        {
        case 3:
            twla.text = qsTr(lat);
            twlo.text = qsTr(lon);
            var idx = ptscb.find(parentPl);
            if (idx > -1)
            {
                ptscb.currentIndex = idx;
            }
            else
                ptscb.currentIndex = 0;

            break;
        default:
            break;
        }
    }

    function clearAllBeforeFill()
    {
        twn.text = qsTr("");
        tad.text = qsTr("");
        twla.text = qsTr("");
        twlo.text  =qsTr("");
    }

    function infoCh(s, t)
    {
        var i = 0;
        switch (t)
        {
        case 1:
        case 2:
        case 3:
            tp.clear();
            for (i = 0; i < s.length; i++)
            {
                tp.append({"text":s[i]});
            }
            break;
        case 4:
            pp.clear();
            for (i = 0; i < s.length; i++)
            {
                pp.append({"text":s[i]});
            }
            break;
        default:
            break;

        }
    }

    Connections {
        target: windowSetsType;
        onNewState: generalf(e);
    }

    function generalf(e)
    {
        //сначала всё подчистим
        clearAllBeforeFill();
        switch (e)
        {

            case 1:
                captionText.text = qsTr("НАСТРОЙКИ ТИПОВ СТАНЦИЙ");
                typeCaption.text = qsTr("Выбор типов станций");
                rowC.enabled = pts.enabled = false;
            break;

            case 2:
                captionText.text = qsTr("НАСТРОЙКИ МЕСТ ПОЛЁТОВ");
                typeCaption.text = qsTr("Выбор мест полётов");
                rowC.enabled = pts.enabled = false;
            break;

            case 3:
                captionText.text = qsTr("НАСТРОЙКИ ТОЧЕК СТОЯНИЯ");
                typeCaption.text = qsTr("Выбор точек стояния");
                rowC.enabled = pts.enabled = true;
            break;

            default:
                captionText.text = qsTr("НАСТРОЙКИ ТИПОВ");
                typeCaption.text = qsTr("Выбор типов");
                rowC.enabled = pts.enabled = false;
            break;

        }

        return;
    }
}
