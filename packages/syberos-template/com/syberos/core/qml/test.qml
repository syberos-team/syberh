import QtQuick 2.0


Rectangle {
    color: "blue"
    width: 100; height: 100
    Rectangle {
        color: "green"
        width: 25; height: 25
    }
    Rectangle {
        color: "red"
        x: 25; y:25; width: 25; height:25
        scale: 1.6  //放大1.6倍显示
        transform: Rotation {origin.x: 30; origin.y: 30
            axis{x: 0; y: 1; z: 0}
            angle: 72
        }
    }
}
