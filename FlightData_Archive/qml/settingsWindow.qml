import QtQuick 2.1
import QtQuick.Dialogs 1.0

Image {
    // Идентификатор, по нему будет происходить
    // обращение к свойствам этого элемента
    id: canvas_set;

    height: 416;
    width: 720;

    source: "qrc:///res/canvas";

    // Будет получать фокус ввода
    focus: true;

    //открытие файла базы данных
    FileDialogDef {
        id: fileDialog;
        title: qsTr("Выберите файл базы данных");
        nameFilters: qsTr("Файл базы данных (*.db)");
        onNamefchanged: {
            if (fileDialog.nameF.length > 0)
                absDbInput.text = qsTr(fileDialog.nameF);
        }
    }

    //открытие директории хранения архивных данных
    FileDialogDef {
        id: fileDialogFolder;
        selectFolder: true;
        title: qsTr("Выберите директорию хранения данных");
        nameFilters: qsTr("Директории хранения данных");
        onNamefchanged: {
            if (fileDialogFolder.nameF.length > 0)
                absDirInput.text = qsTr(fileDialogFolder.nameF);
        }
    }

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
            height: 15;
            width: parent.width;
            text: qsTr("Директория хранения данных:");
            font.family: "Helvetica";
            font.pointSize: 9;
            color: "black";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignBottom;

        }

        Row {

            anchors.left: parent.left;
            spacing: 4;
            id: inputDir;

            TextEditWidget
            {
                width: canvas_set.width - 32;
                id: absDirInput;
                Connections {
                    target: windowSets
                    onTextChanged: {absDirInput.text = qsTr(s)}
                }

            }

            WindowButton {
                height: 20;
                width: 20;
                id: openFileDialog;
                source: "qrc:///res/openDir";
                function callback()
                {    
                    fileDialogFolder.setVisible(true);
                }
            }

        }

        //файл базы данных
        Text {
            id: dbPath;
            height: 15;
            width: parent.width;
            text: qsTr("Файл базы данных:");
            font.family: "Arial Narrow"
            font.pointSize: 9;
            color: "black";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignBottom;

        }
        Row {

            anchors.left: parent.left;
            spacing: 4;
            id: dbRow;

            TextEditWidget
            {
                width: canvas_set.width - 32;
                id: absDbInput;
                Connections {
                    target: windowSets
                    onTextChangedpath: {absDbInput.text = qsTr(s)}
                }

            }

            WindowButton {
                height: 20;
                width: 20;
                id: openFileDialogDB;
                source: "qrc:///res/openDir";
                function callback()
                {
                    fileDialog.setVisible(true);
                }
            }

        }

        //Тип базы данных
        Text {
            id: dbType;
            height: 15;
            width: parent.width;
            text: qsTr("Тип базы данных:");
            font.family: "Arial Narrow"
            font.pointSize: 9;
            color: "black";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignBottom;
        }
        TextEditWidget
        {
            width: canvas_set.width - 32;
            id: dbTypeInput;
            //Connections {
            //    target: windowSets
                //onTextChangedpath: {absDbInput.text = qsTr(s)}
            //}
        }

        //Пользователь базы данных
        Text {
            id: dbUser;
            height: 15;
            width: parent.width;
            text: qsTr("Пользователь базы данных:");
            font.family: "Arial Narrow"
            font.pointSize: 9;
            color: "black";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignBottom;
        }
        TextEditWidget
        {
            width: canvas_set.width - 32;
            id: dbUserInput;
            //Connections {
            //    target: windowSets
                //onTextChangedpath: {absDbInput.text = qsTr(s)}
            //}
        }

        //Пароль базы данных
        Text {
            id: dbPass;
            height: 20;
            width: parent.width;
            text: qsTr("Пароль базы данных:");
            font.family: "Arial Narrow"
            font.pointSize: 9;
            color: "black";
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignBottom;
        }
        TextEditWidget
        {
            width: canvas_set.width - 32;
            id: dbPassInput;
            //Connections {
            //    target: windowSets
                //onTextChangedpath: {absDbInput.text = qsTr(s)}
            //}
        }

        Row {
            id: buttonsPl;
            spacing: 4;
            //anchors.left: absDbInput.left;
            //anchors.top: absDbInput.bottom;
            //anchors.topMargin: 4;
            //anchors.leftMargin: 4;

            WindowButtonText {
                id: types;
                text: qsTr("Редактор\nтипов станции");
                function callback() {
                    windowSets.openButtonSets(1)
            }
            }

            WindowButtonText {
                id: places;
                text: qsTr("Редактор\nмест полётов");
                function callback() {
                    windowSets.openButtonSets(2)
            }
            }

            WindowButtonText {
                id: coords;
                text: qsTr("Редактор\nточек стояния");
                function callback() {
                    windowSets.openButtonSets(3)
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
            text: qsTr("Применить");
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
            text: qsTr("Отмена");
            function callback()
            {
                windowSets.closeSets();
            }
        }


    }

    Connections {
        target: windowSets;
        onWinEnabled: canvas_set.enabled = e;
    }

}
