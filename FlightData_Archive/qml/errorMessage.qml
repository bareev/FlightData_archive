import QtQuick 2.0
import QtQuick.Dialogs 1.2

MessageDialog {
    id: messageDialogCritical;
    icon: StandardIcon.Critical;
    title: qsTr("Ошибка");
    text: "";
    onAccepted: {
        Qt.quit();
    }
    Component.onCompleted: visible = true;
}
