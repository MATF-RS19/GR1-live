#include <iostream>

#define QT_USE_FAST_OPERATOR_PLUS
#define QT_USE_QSTRINGBUILDER
#include <QString>
#include <QDebug>

int main()
{
    QString row{"A"};
    QString number{"1"};

    // A1
    auto result1 = row + number;

    number = "2";

    // A2
    auto result2 = row + number;

    qDebug() << result1;
    qDebug() << result2;

    return 0;
}

