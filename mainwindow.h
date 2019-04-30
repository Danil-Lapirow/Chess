#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "figures.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleClick();

private:
    void resetField();
    void render();
    void checkWin();
    AbstractFigure *field[64];
    AbstractFigure *selected = nullptr;
    std::vector<int> *availableCoords;
    int selectedId = 0;
    bool isBlackTurn = false;
    bool whiteWin = false, blackWin = false;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
