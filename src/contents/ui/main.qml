// Includes relevant modules used by the QML
import QtQuick 2.6
import QtQuick.Controls 2.0 as Controls
import QtQuick.Layouts 1.2
import org.kde.kirigami 2.19 as Kirigami

// Base element, provides basic features needed for all kirigami applications
Kirigami.ApplicationWindow {
    // ID provides unique identifier to reference this element
    id: root
    width: 325
    height: 650

    // Window title
    // i18nc is useful for adding context for translators, also lets strings be changed for different languages
    title: i18nc("@title:window", "Hello World")

    // Initial page to be loaded on app load
    pageStack.initialPage: Kirigami.Page {

        //        Controls.Label {
        //            // Center label horizontally and vertically within parent element
        //            anchors.centerIn: parent
        //            text: i18n("Hello World!")
        //        }
        GridLayout {
            anchors.fill: parent
            columns: 4
            Controls.TextField {
                id: inputField
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.columnSpan: 4
                implicitHeight: 100
            }

            //  ^  /  *  -
            //-
            //  7  8  9
            //-          +
            //  4  5  6
            //-
            //  1  2  3
            //-          =
            //    0   .
            InputButton {
                label: "^"
            }
            InputButton {
                label: "/"
            }
            InputButton {
                label: "*"
            }
            InputButton {
                label: "-"
            }
            InputButton {
                label: "7"
            }
            InputButton {
                label: "8"
            }
            InputButton {
                label: "9"
            }
            InputButton {
                label: "+"
                Layout.rowSpan: 2
                useWidth: true
                Layout.columnSpan: 1
            }
            InputButton {
                label: "4"
            }
            InputButton {
                label: "5"
            }
            InputButton {
                label: "6"
            }
            InputButton {
                label: "1"
            }
            InputButton {
                label: "2"
            }
            InputButton {
                label: "3"
            }

            CalcButton {
                label: "="
                Layout.rowSpan: 2
                useWidth: true
                Layout.columnSpan: 1
            }
            InputButton {
                label: "0"
                Layout.columnSpan: 2
            }
            InputButton {
                label: "."
            }
        }
    }
}
