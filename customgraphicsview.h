#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>

class CustomGraphicsView : public QGraphicsView
{
Q_OBJECT
public:
explicit CustomGraphicsView(QWidget *parent = 0);

signals:
    void sendAvailablePolygon(QPolygon * poly);

public slots:
    void mousePressEvent(QMouseEvent * e);

private:
    QVector<QPoint> pointsClicked;
};

#endif // CUSTOMGRAPHICSVIEW_H
