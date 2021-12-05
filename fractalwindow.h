#ifndef FRACTALWINDOW_H
#define FRACTALWINDOW_H

#include <QMainWindow>
#include "QColorDialog"
#include "QVector"

namespace Ui {
class FractalWindow;
}

class FractalWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FractalWindow(QWidget *parent = nullptr);
    ~FractalWindow();

    void createFractal();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_4_clicked();

private:
    Ui::FractalWindow *ui;
    QVector<QColor> colors;
    QImage *image;
};

#endif // FRACTALWINDOW_H
