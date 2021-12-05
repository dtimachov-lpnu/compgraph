#ifndef AFFINETRANSFORMWINDOW_H
#define AFFINETRANSFORMWINDOW_H

#include <QMainWindow>
#include <QPolygon>
#include <QGraphicsPolygonItem>

namespace Ui {
class AffineTransformWindow;
}

class AffineTransformWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AffineTransformWindow(QWidget *parent = nullptr);
    ~AffineTransformWindow();

public slots:
    void setCurrentPolygon(QPolygon *polygon);

private slots:
    void on_pushButton_clicked();

private:
    void displayPolygon();
    void startMovement();

private:
    Ui::AffineTransformWindow *ui;
    QPolygon *currentPoly;
    QGraphicsPolygonItem *currentPolyItem;
};

#endif // AFFINETRANSFORMWINDOW_H
