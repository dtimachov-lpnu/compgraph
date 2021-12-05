#include "affinetransformwindow.h"
#include "ui_affinetransformwindow.h"

#include <QTime>
#include <QRandomGenerator>
#include <QFileDialog>

namespace
{
    void delay(int ms)
    {
        QTime dieTime= QTime::currentTime().addMSecs(ms);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

AffineTransformWindow::AffineTransformWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AffineTransformWindow)
{
    ui->setupUi(this);
    auto *scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setSceneRect(0, 0, width(), height());

    QWidget::connect(ui->graphicsView, SIGNAL(sendAvailablePolygon(QPolygon*)), this, SLOT(setCurrentPolygon(QPolygon*)));
}

AffineTransformWindow::~AffineTransformWindow()
{
    delete ui;
}

void AffineTransformWindow::setCurrentPolygon(QPolygon *polygon)
{
    this->currentPoly = polygon;
    displayPolygon();
    startMovement();
}

void AffineTransformWindow::displayPolygon()
{
    QRandomGenerator *randomGen = new QRandomGenerator(time(NULL));

    QColor randomColor = QColor(
                randomGen->bounded(255),
                randomGen->bounded(255),
                randomGen->bounded(255)
                );

    QGraphicsScene *scene = ui->graphicsView->scene();
    QGraphicsPolygonItem *resultPolygon = scene->addPolygon(*currentPoly, QPen(randomColor), QBrush(randomColor));

    this->currentPolyItem = resultPolygon;
}

void AffineTransformWindow::startMovement()
{
    auto total_dx = 0;
    auto total_dy = 200;

    auto dx = 0;
    auto dy = 1;

    auto n_iter = total_dy / dy;
    auto final_scale = 2.0f;
    auto scale_step = (final_scale - 1.0f) / n_iter;

    auto fps = 24;
    auto delay_msec = 1000.0f / fps;

    for (size_t a = 0; a < total_dy; a += dy)
    {
        this->currentPolyItem->moveBy(dx, dy);
        this->currentPolyItem->setScale(this->currentPolyItem->scale() + scale_step);
        delay(delay_msec);
    }

    for (size_t a = 0; a < total_dy; a += dy)
    {
        this->currentPolyItem->moveBy(dx, -dy);
        this->currentPolyItem->setScale(this->currentPolyItem->scale() - scale_step);
        delay(delay_msec);
    }
}

void AffineTransformWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this);

    auto scene = ui->graphicsView->scene();
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
    image.fill(Qt::transparent);

    QPainter painter(&image);
    scene->render(&painter);

    image.save(filename);
}

