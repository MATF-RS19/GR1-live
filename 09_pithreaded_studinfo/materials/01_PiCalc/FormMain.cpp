#include "FormMain.h"

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTime>

FormMain::FormMain()
    : QFrame()
{

    buttonStart = new QPushButton("Izracunaj Pi", this);
    labelValue = new QLabel("...", this);

    QVBoxLayout * layout = new QVBoxLayout();

    setLayout(layout);
    resize(300, 100);

    layout->addWidget(buttonStart);
    layout->addWidget(labelValue);

    layout->addWidget(new QLineEdit(this));

    connect(buttonStart, SIGNAL(clicked()),
            this, SLOT(calculatePi()));
}

double calculatePiValue()
{
    // Racunamo pribliznu vrednost broja Pi tako sto
    // uzimamo nasumicne tacke iz kvadrata [0,1] x [0,1]
    // i proveravamo da li su udaljeni od (0,0) manje od 1

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    double hits = 0, count = 0;

    while (hits < 100000000) {
        double x = (qrand() % 512) / 512.0;
        double y = (qrand() % 512) / 512.0;

        count += 1;
        if (x * x + y * y <= 1) {
            hits += 1;
        }
    }

    return 4 * hits / count;
}

void FormMain::calculatePi()
{
    labelValue->setText("Calculating...");

    labelValue->setText(QString::number(calculatePiValue()));
}
