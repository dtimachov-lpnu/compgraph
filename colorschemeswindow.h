#ifndef COLORSCHEMESWINDOW_H
#define COLORSCHEMESWINDOW_H

#include <QMainWindow>

namespace Ui {
class ColorSchemesWindow;
}

class ColorSchemesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ColorSchemesWindow(QWidget *parent = nullptr);
    ~ColorSchemesWindow();

private slots:
    void on_hueSlider_sliderMoved(int position);

    void on_saturationSlider_sliderMoved(int position);

    void on_valueSlider_sliderMoved(int position);

    void on_cyanSlider_sliderMoved(int position);

    void on_magentaSlider_sliderMoved(int position);

    void on_yellowSlider_sliderMoved(int position);

    void on_blackSlider_sliderMoved(int position);

    void on_hueSlider_sliderReleased();

    void on_saturationSlider_sliderReleased();

    void on_valueSlider_sliderReleased();

    void on_cyanSlider_sliderReleased();

    void on_magentaSlider_sliderReleased();

    void on_yellowSlider_sliderReleased();

    void on_blackSlider_sliderReleased();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    void updateSliders(QString fetch = "");

private:
    Ui::ColorSchemesWindow *ui;
    QColor *bgColor;
};

#endif // COLORSCHEMESWINDOW_H
