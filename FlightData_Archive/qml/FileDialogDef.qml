import QtQuick 2.1
import QtQuick.Dialogs 1.0

FileDialog {
    id: fileDialog1;
    title: qsTr("Выберите файл базы данных");
    nameFilters: qsTr("*.db");
    property string nameF: qsTr("");
    signal namefchanged(var nm);
    selectFolder: false;
    onAccepted: {
        if (fileUrl.toString().length > 0)
        {
            nameF = qsTr(fileUrl.toString().substring(8));
            namefchanged(nameF);
        }
        setVisible(false);
    }
    onRejected: {
        nameF = qsTr("");
        namefchanged(nameF);
        setVisible(false);
    }
    Component.onCompleted: visible = false;
}
