#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <qqml.h>

class BackEnd : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    QML_ELEMENT

        public:
                 explicit BackEnd(QObject *parent = nullptr);

    //QString userName();
    //void setUserName(const QString &userName);

signals:
    //void userNameChanged();

public slots:
    double calculate(QString expression);

private:
    //QString m_toCalculate;
};

#endif // BACKEND_H
