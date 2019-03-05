import QtQuick 2.0
import QtQuick.Controls 1.0

Button {
    width: 80;
    height: 40;
    id: button;
    text: "button";
    // Область, обрабатывающая "мышиные" сообщения
    MouseArea
    {
        // Действует в пределах всего
        // элемента Image
        anchors.fill: parent;

        id: mouseArea;

        // При нажатии вызвать метод callback
        onClicked: callback();
    }
}
