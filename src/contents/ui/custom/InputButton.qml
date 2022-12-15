import QtQuick 2.6

EButton {
    onPressed: {
        inputField.text += label
    }
}
