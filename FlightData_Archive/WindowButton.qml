import QtQuick 2.0

Image {

    // Идентификатор элемента
    id: button;

    height: 35;
source: "cancel.png"
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

    states:[
        State
        {
          // Произвольное название
          name: "hovered";
          // Указание на то, когда элемент переходит в это состояние
          // в данном случае когда нажата левая кнопка мыши
          when: mouseArea.pressed;
          // Какие свойства будут изменяться в этом состоянии
          // в данном случае это будет прозрачность
          PropertyChanges { target: button; opacity: 0.5;}
        },
        State
        {
          name: "normal"
          // В это состояние элемент будет переходить
          // когда левая кнопка мыши не нажата
          when: mouseArea.pressed === false;
          PropertyChanges { target: button; opacity: 1; }
        }
    ]


    Behavior on opacity
    {
        // Анимация с шагом в 100 миллисекунд
        // Раз в 100 миллисекунд прозрачность будет изменяться
        // на 0,1
        NumberAnimation { duration: 100 }
    }
}
