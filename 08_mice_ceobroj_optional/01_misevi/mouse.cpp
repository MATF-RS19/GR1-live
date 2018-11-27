#include "mouse.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <math.h>

static const double PI = 3.14159265358979323846264338327950288419717;
static const double TWO_PI = 2.0 * PI;

// Funkcija koja normalizuje ugao da bude u intervalu
// od nula do 2 * Pi
static qreal normalizeAngle(qreal angle)
{
    while (angle < 0) {
        angle += TWO_PI;
    }

    while (angle > TWO_PI) {
        angle -= TWO_PI;
    }

    return angle;
}

// Konstruktor
Mouse::Mouse()
  : angle(0), speed(0), mouseEyeDirection(0),
    color(qrand() % 256, qrand() % 256, qrand() % 256)
{
    // setRotation je nasledjen of QGraphicsItem klase.
    // Postavlja rotaciju naseg misa u njegovom lokalnom koordinatnom prostoru.
    setRotation(qrand() % (360 * 16));
}

// Funkcija koja vraca pravouganik u kome garantujemo da se mis
// nalazi (to jest, da ni jedan deo misa ne izlazi van)
// QGraphicsView ovo koristi kako bi proverio da li QGraphicsItem
// zahteva ponovno crtanje.
QRectF Mouse::boundingRect() const
{
    qreal adjust = -0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

// Funkcija koja vraca preciznije granice misa - radi detekcije kolizije
QPainterPath Mouse::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}

void Mouse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    // Crtamo telo
    painter->setBrush(color);
    painter->drawEllipse(-10, -20, 20, 40);

    if (QStyleOptionGraphicsItem::
            levelOfDetailFromTransform(
                painter->worldTransform()
            ) >= .75) {

        // Crtamo oci
        painter->setBrush(Qt::white);
        painter->drawEllipse(-10, -17, 8, 8);
        painter->drawEllipse(2, -17, 8, 8);

        // Crtamo nos
        painter->setBrush(Qt::black);
        painter->drawEllipse(QRectF(-2, -22, 4, 4));

        // Crtamo zenice
        painter->drawEllipse(QRectF(-8.0 + mouseEyeDirection, -17, 4, 4));
        painter->drawEllipse(QRectF(4.0 + mouseEyeDirection, -17, 4, 4));

        // Crtamo usi
        // Ukoliko se mis sudara sa nekim drugim objektom (u nasem slucaju - drugim misem)
        // usi mi bojimo u crveno, a inace bojimo u normalnu tamno zutu boju.
        painter->setBrush(scene()->collidingItems(this).isEmpty()
                ? Qt::darkYellow : Qt::red);
        painter->drawEllipse(-17, -12, 16, 16);
        painter->drawEllipse(1, -12, 16, 16);

        // Crtamo rep
        QPainterPath path(QPointF(0, 20));
        path.cubicTo(-5, 22, -5, 22, 0, 25);
        path.cubicTo(5, 27, 5, 32, 0, 30);
        path.cubicTo(-5, 32, -5, 42, 0, 35);
        painter->setBrush(Qt::NoBrush);
        painter->drawPath(path);
    }
}

// QGraphicsScene poziva advance nad svakim QGraphicsItem-om kada
// se odluci da predje na sledeci frame.
void Mouse::advance(int step)
{
    // advance se poziva dva puta
    // step=0 -> informise o tome da ce da se desi advance (korisno da se item-i spreme za advance)
    // step=1 -> pravi advance
    if (!step)
        return;

    // Linija od centra misa do centra scene
    const QLineF lineToCenter(QPointF(0, 0),
            mapFromScene(0, 0));

    // Ako se previse odaljavamo od centra, bolje da se
    // vracamo nazad
    if (lineToCenter.length() > 150) {
        qreal angleToCenter = acos(lineToCenter.dx() / lineToCenter.length());
        if (lineToCenter.dy() < 0)
            angleToCenter = TWO_PI - angleToCenter;
        angleToCenter = normalizeAngle((PI - angleToCenter) + PI / 2);

        if (angleToCenter < PI && angleToCenter > PI / 4) {
            // Rotiramo na levo
            angle += (angle < -PI / 2) ? 0.25 : -0.25;
        } else if (angleToCenter >= PI && angleToCenter < (PI + PI / 2 + PI / 4)) {
            // Rotiramo na desno
            angle += (angle < PI / 2) ? 0.25 : -0.25;
        }
    } else if (sin(angle) < 0) {
        angle += 0.25;
    } else if (sin(angle) > 0) {
        angle -= 0.25;
    }

    // Trazimo miseve koji su nam u vidokrugu
    const auto dangerMice =
        scene()->items(
            QPolygonF(
                { mapToScene(0, 0)
                , mapToScene(-30, -50)
                , mapToScene(30, -50)}
            ));

    for (auto item: dangerMice) {
        if (item == this) {
            continue;
        }

        QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));

        qreal angleToMouse = acos(lineToMouse.dx() / lineToMouse.length());
        if (lineToMouse.dy() < 0)
            angleToMouse = TWO_PI - angleToMouse;
        angleToMouse = normalizeAngle((PI - angleToMouse) + PI / 2);

        if (angleToMouse >= 0 && angleToMouse < PI / 2) {
            // Rotiramo na levo
            angle += 0.5;
        } else if (angleToMouse <= TWO_PI && angleToMouse > (TWO_PI - PI / 2)) {
            // Rotiramo na desno
            angle -= 0.5;
        }
    }

    // Haoticno kretanje
    if (dangerMice.size() > 1 && (qrand() % 10) == 0) {
        if (qrand() % 1)
            angle += (qrand() % 100) / 500.0;
        else
            angle -= (qrand() % 100) / 500.0;
    }

    speed += (-50 + qrand() % 100) / 100.0;

    qreal dx = sin(angle) * 10;
    mouseEyeDirection = (qAbs(dx / 5) < 1) ? 0 : dx / 5;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(3 + sin(speed) * 3)));
}

void Mouse::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    // Prosledjujemo dogadjaj roditeljskoj klasi
    QGraphicsItem::mousePressEvent(event);

    // Uklanjamo misa iz scene
    // scene()->removeItem(this);

    // Kompletno unistavamo misa
    delete this;
}
