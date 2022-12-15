import QtQuick 2.6

EButton {
    onPressed: {
        var str = inputField.text
        inputField.text = backend.calculate(str)
    }
}
