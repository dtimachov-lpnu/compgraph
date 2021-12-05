#include "customgraphicsview.h"
#include "mainwindow.h"
#include <QPointF>
#include <QDebug>

CustomGraphicsView::CustomGraphicsView(QWidget *parent) :
QGraphicsView(parent)
{
}

void CustomGraphicsView::mousePressEvent(QMouseEvent * e)
{
    pointsClicked.append(e->pos());
    if (pointsClicked.size() % 4 == 0)
    {
        QList<QPoint> lastFour(pointsClicked.end() - 4, pointsClicked.end());

        QPolygon *polygon = new QPolygon(lastFour);

        emit sendAvailablePolygon(polygon);
    }
}
