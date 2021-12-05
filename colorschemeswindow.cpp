#include "colorschemeswindow.h"
#include "ui_colorschemeswindow.h"

#include "QFileDialog"

ColorSchemesWindow::ColorSchemesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ColorSchemesWindow)
{
    ui->setupUi(this);
    bgColor = new QColor(0x66, 0xFF, 0x66);

    updateSliders();
}

ColorSchemesWindow::~ColorSchemesWindow()
{
    delete ui;
}

void ColorSchemesWindow::updateSliders(QString fetch)
{
    if (fetch == "hsv")
        this->bgColor = new QColor(QColor::fromHsv(
                ui->hueSlider->value(),
                ui->saturationSlider->value(),
                ui->valueSlider->value()
                ));
    else if (fetch == "cmyk")
        this->bgColor = new QColor(QColor::fromCmyk(
                ui->cyanSlider->value(),
                ui->magentaSlider->value(),
                ui->yellowSlider->value(),
                ui->blackSlider->value()
                ));

    int h, s, v;
    int c, m, y, k;

    bgColor->getHsv(&h, &s, &v);
    bgColor->getCmyk(&c, &m, &y, &k);

    ui->hueSlider->setValue(h);
    ui->saturationSlider->setValue(s);
    ui->valueSlider->setValue(v);

    ui->cyanSlider->setValue(c);
    ui->magentaSlider->setValue(m);
    ui->yellowSlider->setValue(y);
    ui->blackSlider->setValue(k);

    QPalette palette = ui->bgLabel->palette();
    palette.setColor(ui->bgLabel->backgroundRole(), *bgColor);
    palette.setColor(ui->bgLabel->foregroundRole(), *bgColor);
    ui->bgLabel->setPalette(palette);
    ui->bgLabel->setAutoFillBackground(true);
}

void ColorSchemesWindow::on_hueSlider_sliderMoved(int position)
{}


void ColorSchemesWindow::on_saturationSlider_sliderMoved(int position)
{}


void ColorSchemesWindow::on_valueSlider_sliderMoved(int position)
{}


void ColorSchemesWindow::on_cyanSlider_sliderMoved(int position)
{}


void ColorSchemesWindow::on_magentaSlider_sliderMoved(int position)
{}


void ColorSchemesWindow::on_yellowSlider_sliderMoved(int position)
{}


void ColorSchemesWindow::on_blackSlider_sliderMoved(int position)
{}




void ColorSchemesWindow::on_hueSlider_sliderReleased()
{
    updateSliders("hsv");
}


void ColorSchemesWindow::on_saturationSlider_sliderReleased()
{
    updateSliders("hsv");
}


void ColorSchemesWindow::on_valueSlider_sliderReleased()
{
    updateSliders("hsv");

    QImage image = ui->label_3->pixmap().toImage();

    for (size_t x = 0; x < image.width(); x++)
    {
        for (size_t y = 0; y < image.height(); y++)
        {
             auto color = image.pixelColor(x, y);
             int h, s, v;
             color.getHsv(&h, &s, &v);
             color.setHsv(h, s, ui->valueSlider->value());

             image.setPixelColor(x, y, color);
        }
    }

    QPixmap pixmap = QPixmap::fromImage(image);
    ui->label_3->setPixmap(pixmap);

}


void ColorSchemesWindow::on_cyanSlider_sliderReleased()
{
    updateSliders("cmyk");
}


void ColorSchemesWindow::on_magentaSlider_sliderReleased()
{
    updateSliders("cmyk");
}


void ColorSchemesWindow::on_yellowSlider_sliderReleased()
{
    updateSliders("cmyk");
}


void ColorSchemesWindow::on_blackSlider_sliderReleased()
{
    updateSliders("cmyk");
}


void ColorSchemesWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Filename to open", QDir::homePath(), "Image Files|*.jpg;*.jpeg;*.png;");
    QPixmap pixmap(filename);

    ui->label_3->setPixmap(pixmap);
}


void ColorSchemesWindow::on_pushButton_2_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this);
    this->ui->label_3->pixmap().toImage().save(filename);
}

