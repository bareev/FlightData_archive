import QtQuick 1.1


Rectangle {
    // Идентификатор, по нему будет происходить
    // обращение к свойствам этого элемента
    id: canvas;

    height: 400;
    width: 600;

    // Цвет фона, черный
    color: "white";

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

        WindowButton {
        // Кнопка закрытия окна
        id: exit;

        source: "exit.png";

        function callback()
        {
            window.quit();
        }
        }
     }
}



