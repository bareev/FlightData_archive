import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

Image {

    enabled: false;
    // Идентификатор, по нему будет происходить
    // обращение к свойствам этого элемента
    id: canvas;

    height: 501;
    width: 875;

    source: "qrc:///res/canvas";

    // Будет получать фокус ввода
    focus: true;

    Row {
        // Правый край элемента выравнивается
        // по правому краю родительского элемента
        anchors.right: parent.right;
        // Отступ справа, 4 пикселя
        anchors.rightMargin: 4;
        // Верхний край эелемента выравнивается
        // по верхнему краю родительского элемента
        anchors.top: parent.top;
        // Отступ сверху, 4 пикселя
        anchors.topMargin: 4;

        // Отступ между элементами
        spacing: 4;

        id: rowText;

        Text {
            id: captionText;
            height: 35;
            width: canvas.width - 120;
            text: qsTr("ИНСТРУМЕНТ ХРАНЕНИЯ ПОЛЁТНЫХ ДАННЫХ");
            font.family: "Helvetica";
            font.pointSize: 21;
            style: Text.Sunken;
            color: "blue";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;

        }

        WindowButton {
            // Кнопка сохранения
            id: saveButton;
            source: "qrc:///res/save";
            enabled: false;
            function callback()
            {
                window.saveDB();
            }
        }

        WindowButton {
            // Кнопка вызова настроек
            id: settButton;
            source: "qrc:///res/settings";
            function callback()
            {
                window.showSets();
            }
        }

        WindowButton {
            // Кнопка вызова справки
            id: helpButton;
            source: "qrc:///res/help";
            function callback()
            {
                //window.quit();
            }
        }

        WindowButton {
            // Кнопка закрытия окна
            id: exit;
            source: "qrc:///res/exit";
            function callback()
            {
                window.quit();
            }
        }
    }

    Grid {
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.rightMargin: 4;
        anchors.top: rowText.bottom;
        anchors.topMargin: 15;
        id: gridFilter;
        spacing: 15;

        Column {
            id: columnChB;
            spacing: 4;
            Text {
                text: qsTr("Выберите фильтры отображения");
                id: txtF;
                font.family: "Helvetica";
                font.pointSize: 10;
                font.bold: true;
            }

            CheckBox {
                text: qsTr("По времени");
                id: timeFilter;
                checked: false;
            }

            CheckBox {
                text: qsTr("По типу станции");
                id: typeFilter;
                checked: false;
            }

            CheckBox {
                text: qsTr("По месту испытаний");
                id: placeFilter;
                checked: false;
            }

            CheckBox {
                text: qsTr("По координатам");
                id: coordFilter;
                checked: false;
            }

        }
        Column {
            id: columnParams;
            spacing: 1;
            Text {
                text: qsTr("Параметры фильтров отображения");
                id: txtP;
                font.family: "Helvetica";
                font.pointSize: 10;
                font.bold: true;
            }

            Row
            {
                anchors.left: parent.left;
                id: rowTime;
                spacing: 4;

                TextEditWidget {
                    id: timestart;
                    width: 130;
                    inputMethodHints: Qt.ImhDigitsOnly;
                    inputMask: "9999-99-99 99:99:99";
                    text: Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss");
                    validator: RegExpValidator { regExp: /^\d\d\d\d-(0?[1-9]|1[0-2])-(0?[1-9]|[12][0-9]|3[01]) (00|[0-9]|1[0-9]|2[0-3]):([0-9]|[0-5][0-9]):([0-9]|[0-5][0-9])$ /; }
                }
                TextEditWidget {
                    id: timeend;
                    width: 130;
                    inputMethodHints: Qt.ImhDigitsOnly;
                    inputMask: "9999-99-99 99:99:99";
                    text: Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss");
                    validator: RegExpValidator { regExp: /^\d\d\d\d-(0?[1-9]|1[0-2])-(0?[1-9]|[12][0-9]|3[01]) (00|[0-9]|1[0-9]|2[0-3]):([0-9]|[0-5][0-9]):([0-9]|[0-5][0-9])$ /; }
                }
            }

            ComboBox {
                id: type;
                width: 130;
                model: myModelType;
            }

            ComboBox {
                id: place;
                width: 130;
                onCurrentTextChanged: window.onCurrentTextChanged(place.currentText, 0);
                model: myModelPlace;
            }

            ComboBox {
                id: coords;
                width: 130;
                model: myModelCoords;
            }

            ListModel {
                id: myModelType;
            }
            ListModel {
                id: myModelPlace;
            }
            ListModel {
                id: myModelCoords;
            }

        }

        Column {
            id: columnButton;
            spacing: 1;
            Text {
                text: qsTr("Применить фильтры отображения");
                id: txtBtn;
                font.family: "Helvetica";
                font.pointSize: 10;
                font.bold: true;
            }
            WindowButtonText {
                text: qsTr("Фильтровать");
                id: buttonFilter;
                function callback()
                {
                }
            }
        }

    }


    TableView {

        y: 160;
        width: canvas.width - 8;
        height: canvas.height - 201;
        anchors.topMargin: 4;
        anchors.left: canvas.left;
        anchors.leftMargin: 4;
        anchors.rightMargin: 4;
        anchors.bottomMargin: 4;

        //@todo - убрать лишний столбец справа

        TableViewColumn {
            role: "date";    // Эти роли совпадают с названиями ролей в C++ модели
            title: qsTr("Дата и время");
        }

        TableViewColumn {
            role: "type";    // Эти роли совпадают с названиями ролей в C++ модели
            title: qsTr("Тип станции");
        }

        TableViewColumn {
            role: "placeStr";  // Эти роли совпадают с названиями ролей в C++ модели
            title: qsTr("Место полётов");
        }

        TableViewColumn {
            role: "description"; // Эти роли совпадают с названиями ролей в C++ модели
            title: qsTr("Описание");
        }

        // Устанавливаем модель в TableView
        model: table;
    }

    Row {
        anchors.right: parent.right;
        anchors.rightMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.topMargin: 4;
        spacing: 4;

        id: rowButtons;

        WindowButtonText {
            text: qsTr("Добавить");
            id: buttonAdd;
            function callback()
            {
                window.showAdd();
            }
        }

        WindowButtonText {
            text: qsTr("Запаковать");
            id: buttonArchive;
            function callback()
            {
            }
        }

        WindowButtonText {
            text: qsTr("Распаковать");
            id: buttonUnPack;
            function callback()
            {
            }
        }
    }

    Connections {
        target: window;
        onRlsInfoRead: infoCh(s, t, w);
    }

    function infoCh(s, t, w)
    {
        if (w !== 0)
            return;

        var i = 0;
        switch (t)
        {
        case 1:
            myModelType.clear();
            for (i = 0; i < s.length; i++)
            {
                myModelType.append({"text":s[i]});
            }
            break;
        case 2:
            myModelPlace.clear();
            for (i = 0; i < s.length; i++)
            {
                myModelPlace.append({"text":s[i]});
            }
            break;
        case 3:
            myModelCoords.clear();
            for (i = 0; i < s.length; i++)
            {
                myModelCoords.append({"text":s[i]});
            }
            break;
        default:
            break;

        }
    }

    Connections {
        target: window;
        onSetEnabled: canvas.enabled = e;
    }

    Connections {
        target: window;
        onSaveEnabled: saveButton.enabled = e;
    }


}



