import QtQuick 1.1


Image {
    // Идентификатор, по нему будет происходить
    // обращение к свойствам этого элемента
    id: canvas;

    height: 466;
    width: 819;

    source: "qrc:///res/canvas";

    // Изменять размер под размеры
    // родительского элемента
    anchors.fill: parent;

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

    Item {
        id: cell;
        Text {
            anchors.centerIn: parent
            text: "styleData.value"
        }
    }

    GridView {

        delegate: cell;
        model: tableModel;

    }


}



