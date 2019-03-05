import QtQuick 2.0

Image {
    // Идентификатор, по нему будет происходить
    // обращение к свойствам этого элемента
    id: canvas_set;

    height: 416;
    width: 720;

    source: "qrc:///res/canvas"

    // Будет получать фокус ввода
    focus: true;

    Column {

        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.fill: parent;
        anchors.topMargin: 4;
        anchors.leftMargin: 4;

        // Отступ между элементами
        spacing: 4;

        Text {
            id: captionText;
            height: 35;
            width: parent.width;
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
            width: parent.width;
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
            spacing: 4;
            id: inputDir;

            Rectangle
            {

                id: textInputRow;
                height: 18;
                width: canvas_set.width - 32;
                color: "white";
                TextInput {
                    id: absDirInput;
                    visible: true;
                    height: 18;
                    width: canvas_set.width - 32;
                    font.family: "Helvetica";
                    font.pointSize: 10;
                    color: "black";
                    horizontalAlignment: Text.AlignLeft;
                    cursorVisible: false; //@todo - курсор в начале строки, чтобы текст выравнивался по краю
                    Connections {
                        target: windowSets
                        onTextChanged: {absDirInput.text = qsTr(s)}
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

        //файл базы данных
        Text {
            id: dbPath;
            height: 35;
            width: parent.width;
            text: qsTr("Файл базы данных:");
            font.family: "Arial Narrow"
            font.pointSize: 14;
            color: "black";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignBottom;

        }
        Row {

            anchors.left: parent.left;
            anchors.leftMargin: 4;
            anchors.rightMargin: 4;
            spacing: 4;
            id: dbRow;


            Rectangle
            {

                id: dbPathRow;
                height: 18;
                width: canvas_set.width - 32;
                color: "white";
                TextInput {
                    id: absDbInput;
                    visible: true;
                    height: 18;
                    width: canvas_set.width - 32;
                    font.family: "Helvetica";
                    font.pointSize: 10;
                    color: "black";
                    horizontalAlignment: Text.AlignLeft;
                    cursorVisible: false; //@todo - курсор в начале строки, чтобы текст выравнивался по краю
                    Connections {
                        target: windowSets
                        onTextChangedpath: {absDbInput.text = qsTr(s)}
                    }

                }

            }
            WindowButton {
                height: 20;
                width: 20;
                id: openFileDialogDB;
                source: "qrc:///res/openDir";
                function callback()
                {
                    windowSets.openDirDB();
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

        WindowButtonText {
            id: applySets;
            text: "Применить";
            function callback()
            {
                windowSets.saveSettings(absDirInput.text, absDbInput.text);
            }
        }

        WindowButtonText {
            id: okSets;
            text: "OK";
            function callback()
            {
                windowSets.closeSets();
            }
        }

        WindowButtonText {
            id: exitSets;
            text: "Отмена";
            function callback()
            {
                windowSets.closeSets();
            }
        }


    }

}
