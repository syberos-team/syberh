import QtQuick 2.0

MouseArea {
    // To avoid conflicting with ListView.model when inside ListView context.
    property QtObject selectorModel: model
    anchors.fill: parent
    onClicked: selectorModel.reject()

    Rectangle {
        clip: true
        width: 600
        height: Math.min(listView.contentItem.height + listView.anchors.topMargin + listView.anchors.bottomMargin
                         , Math.max(selectorModel.elementRect.y, parent.height - selectorModel.elementRect.y - selectorModel.elementRect.height))
        x: (selectorModel.elementRect.x + 600 > parent.width) ? parent.width - 600 : selectorModel.elementRect.x
        y: (selectorModel.elementRect.y + selectorModel.elementRect.height + height < parent.height ) || (selectorModel.elementRect.y - height < 0)
           ? selectorModel.elementRect.y + selectorModel.elementRect.height
           : selectorModel.elementRect.y - height;
        radius: 5
        color: "gainsboro"
        opacity: 0.8

        ListView {
            id: listView
            anchors.fill: parent
            anchors.margins: 10
            spacing: 5
            model: selectorModel.items

            delegate: Rectangle {
                color: model.selected ? "gold" : "silver"
                height: 50
                width: parent.width

                Text {
                    anchors.centerIn: parent
                    text: model.text
                    color: model.enabled ? "black" : "gainsboro"
                }

                MouseArea {
                    anchors.fill: parent
                    enabled: model.enabled
                    onClicked: selectorModel.accept(model.index)
                }
            }

            section.property: "group"
            section.delegate: Rectangle {
                height: 30
                width: parent.width
                color: "silver"
                Text {
                    anchors.centerIn: parent
                    text: section
                    font.bold: true
                }
            }
        }
    }
}
