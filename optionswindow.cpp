#include "optionswindow.h"
#include "ui_optionswindow.h"
#include "fractalwindow.h"
#include "colorschemeswindow.h"
#include "affinetransformwindow.h"

OptionsWindow::OptionsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OptionsWindow)
{
    ui->setupUi(this);
}

OptionsWindow::~OptionsWindow()
{
    delete ui;
}

void OptionsWindow::on_pushButton_clicked()
{
    auto fractalWindow = new FractalWindow();
    fractalWindow->show();
    this->close();
}


void OptionsWindow::on_pushButton_2_clicked()
{
    auto csWindow = new ColorSchemesWindow();
    csWindow->show();
    this->close();
}


void OptionsWindow::on_pushButton_3_clicked()
{
    auto atWindow = new AffineTransformWindow();
    atWindow->show();
    this->close();
}

