import QtQuick 2.6
import QtQuick.Controls 2.0 as Controls
import QtQuick.Layouts 1.2

Controls.Button {
    property string label: "text"
    property bool useWidth: false

    Layout.fillWidth: true
    Layout.fillHeight: true
    contentItem: ButtonText {
        text: label
    }
}
