#include "PiCalcThread.h"
#include <QTime>

void PiCalcThread::run()
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

    emit calculated(4 * hits / count);
//    Q_EMIT calculated(4 * hits / count);
}
