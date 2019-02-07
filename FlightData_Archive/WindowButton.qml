import QtQuick 1.1

Image {

    // Идентификатор элемента
    id: button;

    height: 35;
    width: 35;

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
