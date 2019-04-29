#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resetField();
    for (int i = 0; i < 64; ++i) {
        ui->field->addWidget(field[i]);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetField(){
    for (int i = 0; i < 64; ++i) {
        auto figure = new EmptyFigure("");
        figure->resize(10,10);
        field[i] = figure;
    }
}

void MainWindow::on_pushButton_clicked()
{
    auto figure = dynamic_cast<AbstractFigure *>(sender());

}
