import QtQuick 2.6
import QtQuick.Layouts 1.2

Text {
    anchors.centerIn: parent
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    font.pixelSize: (parent.useWidth ? parent.width : parent.height) * 0.5
}
