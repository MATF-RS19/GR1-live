#ifndef FORMMAIN_H_
#define FORMMAIN_H_

#include <QFrame>
#include <QPushButton>
#include <QLabel>

class FormMain: public QFrame {
    Q_OBJECT

public:
    FormMain();

public Q_SLOTS:
    void calculatePi();
    void calculatedPi(double value);

private:
    QPushButton * buttonStart;
    QLabel * labelValue;
};

#endif // FORMMAIN_H_

