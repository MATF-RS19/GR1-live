#include "FormMain.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTime>
#include "PiCalcThread.h"

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

void FormMain::calculatePi()
{
    labelValue->setText("Calculating...");

    PiCalcThread * thread = new PiCalcThread();

    connect(thread, SIGNAL(calculated(double)),
            this, SLOT(calculatedPi(double)),
            Qt::QueuedConnection
            );
    connect(thread, SIGNAL(calculated(double)),
            thread, SLOT(deleteLater()),
            Qt::QueuedConnection
            );

    thread->start();
}

void FormMain::calculatedPi(double value)
{
    labelValue->setText(QString::number(value));
}
