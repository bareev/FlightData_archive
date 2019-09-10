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
        else if (fileUrls.length > 0)
        {
            nameF = "";
            for (var c = 0; c < fileUrls.length; c++)
            {
                nameF += qsTr(fileUrls[c].toString().substring(8));
                if (c < (fileUrls.length - 1))
                {
                    nameF += ";";
                }
            }
            namefchanged(qsTr(nameF));
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
