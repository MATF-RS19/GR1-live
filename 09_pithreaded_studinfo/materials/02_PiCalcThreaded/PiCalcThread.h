#ifndef PICALC_THREAD_H_
#define PICALC_THREAD_H_

#include <QThread>

class PiCalcThread: public QThread {
    Q_OBJECT

public:
    void run();

Q_SIGNALS:
    void calculated(double value);


};

#endif // PICALC_THREAD_H_
