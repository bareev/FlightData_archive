import QtQuick 2.0
import QtQuick.Controls 1.0

Image {
    // Идентификатор, по нему будет происходить
    // обращение к свойствам этого элемента
    id: canvas;

    height: 496;
    width: 819;

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
        anchors.topMargin: 4;
        spacing: 4;
        id: gridFilter;

        Column {
            id: columnChB;
            Text {
                text: qsTr("Выберите фильтры отображения");
                id: txtF;
                font.family: "Helvetica";
                font.pointSize: 12;
                style: Text.Sunken;
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

        }
    }

    TableView {

        y: 150;
        width: canvas.width - 8;
        height: canvas.height - 194;
        anchors.topMargin: 4;
        anchors.left: rowText.left;
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



}



