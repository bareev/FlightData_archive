import QtQuick 1.1

Image {
    // Идентификатор, по нему будет происходить
    // обращение к свойствам этого элемента
    id: canvas_set;

    height: 233;
    width: 410;

    source: "qrc:///res/canvas";

    // Изменять размер под размеры
    // родительского элемента
    anchors.fill: parent;

    // Будет получать фокус ввода
    focus: true;

    Column {

        // Правый край элемента выравнивается
        // по правому краю родительского элемента
        anchors.top: parent.top;
        // Отступ справа, 4 пикселя
        anchors.leftMargin: 4;
        // Верхний край эелемента выравнивается
        // по верхнему краю родительского элемента
        anchors.left: parent.left;
        // Отступ сверху, 4 пикселя
        anchors.topMargin: 4;

        // Отступ между элементами
        spacing: 4;

        Text {
            id: captionText;
            height: 35;
            width: canvas_set.width;
            text: qsTr("ПАНЕЛЬ НАСТРОЕК");
            font.family: "Helvetica";
            font.pointSize: 21;
            style: Text.Sunken;
            color: "blue";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        Text {
            id: absDir;
            height: 35;
            width: canvas_set.width;
            text: qsTr("Директория хранения данных:");
            font.family: "Helvetica";
            font.pointSize: 14;
            color: "black";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignBottom;

        }

        Row {

            anchors.left: parent.left;
            anchors.leftMargin: 4;
            anchors.rightMargin: 4;
            anchors.top: absDir.bottom;
            anchors.topMargin: 4;
            spacing: 4;
            id: inputDir;

            Rectangle
            {

                id: textInputRow;
                height: 18;
                width: canvas_set.width - 32;
                color: "white";
                TextInput {
                    objectName: "absDirInput";
                    id: absDirInput;
                    visible: true;
                    height: 18;
                    width: canvas_set.width - 32;
                    font.family: "Helvetica";
                    font.pointSize: 10;
                    color: "black";
                    horizontalAlignment: Text.AlignLeft;
                    cursorVisible: true;
                    Connections {
                        target: windowSets;
                        onTextChanged: {absDirInput.text = s}
                        }

                }

            }
            WindowButton {
                height: 20;
                width: 20;
                id: openFileDialog;
                source: "qrc:///res/openDir";
                function callback()
                {
                    windowSets.openDir();
                }
            }

        }

    }

    Row {

        anchors.right: parent.right;
        anchors.rightMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        spacing: 4;

        WindowButton {
            // Кнопка закрытия окна
            height: 30;
            width: 86;
            id: applySets;
            source: "qrc:///res/apply";
            function callback()
            {
                windowSets.closeSets();
            }
        }

        WindowButton {
            // Кнопка закрытия окна
            height: 30;
            width: 86;
            id: okSets;
            source: "qrc:///res/ok";
            function callback()
            {
                windowSets.closeSets();
            }
        }

        WindowButton {
            // Кнопка закрытия окна
            height: 30;
            width: 86;
            id: exitSets;
            source: "qrc:///res/cancel";
            function callback()
            {
                windowSets.closeSets();
            }
        }


    }

}
