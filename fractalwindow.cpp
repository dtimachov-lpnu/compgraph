#include "fractalwindow.h"
#include "ui_fractalwindow.h"
#include <complex>
#include <QFileDialog>

namespace
{
    QRgb pixelDisplayValue(double value, const QVector<QColor> &colors)
    {
        if (value < colors.size())
            return colors[value].rgb();

        const auto a = 0.1;
        const auto r = 255 * (0.5 * sin(a * value) + 0.5);
        const auto g = 255 * (0.5 * sin(a * value + 2.094) + 0.5);
        const auto b = 255 * (0.5 * sin(a * value + 4.188) + 0.5);

        return qRgb(r, g, b);
    }

    void screenToWorld(const QPair<double, double>& n, QPair<double, double>& v, double scaleX, double scaleY)
    {
        v.first = (double)(n.first) / scaleX;
        v.second = (double)(n.second) / scaleY;
    }
}

FractalWindow::FractalWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FractalWindow)
{
    ui->setupUi(this);
}

FractalWindow::~FractalWindow()
{
    delete ui;
}

void FractalWindow::createFractal()
{
    QPair<double, double> pix_tl = { 0, 0 };
    QPair<double, double> pix_br = { 428, 916 };
    QPair<double, double> frac_tl = { -2.0, -2.0 };
    QPair<double, double> frac_br = { 2.0, 2.0 };
    const size_t iterations = 16;
    QVector<QColor> req_colors = { QColor(ui->comboBox->currentText()), QColor(ui->comboBox_2->currentText()) };

    double scaleX = 1;
    double scaleY = 1;
    for (size_t i = 0; i < ui->horizontalSlider->value() + 1; i++)
    {
        scaleX *= 1.1;
        scaleY *= 1.1;
    }

    screenToWorld(pix_tl, frac_tl, scaleX, scaleY);
    screenToWorld(pix_br, frac_br, scaleX, scaleY);

    double x_scale = (frac_br.first - frac_tl.first) / (double(pix_br.first) - double(pix_tl.first));
    double y_scale = (frac_br.second - frac_tl.second) / (double(pix_br.second) - double(pix_tl.second));

    for (int y = pix_tl.second; y < pix_br.second; y++)
    {
        for (int x = pix_tl.first; x < pix_br.first; x++)
        {
            std::complex<double> c(x * x_scale + frac_tl.first, y * y_scale + frac_tl.second);
            std::complex<double> z(0, 0);

            int n = 0;
            while (abs(z) < 2.0 && n < iterations)
            {
                if (abs(tan(z * z)) == 0)
                    z = c;
                else
                    z = 1. / tan(z * z) + c;

                n++;
            }

            image->setPixel(x, y, pixelDisplayValue(n, req_colors));
        }
    }
}

void FractalWindow::on_pushButton_2_clicked()
{
    auto color = QColorDialog::getColor();
    colors.append(color);

    ui->comboBox->addItem(color.name());
    ui->comboBox_2->addItem(color.name());
}


void FractalWindow::on_pushButton_3_clicked()
{
    ui->graphicsView->raise();
    ui->horizontalSlider->raise();
    ui->pushButton_4->raise();

    image = new QImage(428, 916, QImage::Format::Format_RGB444);
    ui->graphicsView->setSceneRect(0, 0, 428, 916);

    createFractal();

    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 428, 916);
    scene->addPixmap(QPixmap::fromImage(*image));

    ui->graphicsView->setScene(scene);
}


void FractalWindow::on_horizontalSlider_sliderMoved(int position)
{

}


void FractalWindow::on_horizontalSlider_valueChanged(int value)
{
    image = new QImage(428, 916, QImage::Format::Format_RGB444);
    ui->graphicsView->setSceneRect(0, 0, 428, 916);

    createFractal();

    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 428, 916);
    scene->addPixmap(QPixmap::fromImage(*image));

    ui->graphicsView->setScene(scene);
}


void FractalWindow::on_pushButton_4_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this);
    if (this->image)
    {
        this->image->save(filename);
    }
}

