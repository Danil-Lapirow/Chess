#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#define PADDING 20
#define BUTTON_WIDTH 60
#define BUTTON_HEIGHT 60
#define SPACING 0

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resetField();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleClick()
{
    auto btn = dynamic_cast<QPushButton *>(sender());
    AbstractFigure *figure = nullptr;
    int id = 0;
    for (id = 0; id < 64; ++id) {
        if (field[id]->btn == btn){
            figure = field[id];
            break;
        }
    }

    if(selected == nullptr){
        if(!figure->isBlack == isBlackTurn)
            return;
        if(!figure->canMove)
            return;
        selected = figure;
        selectedId = id;
        figure->changeSelected(true);
//        if (selected->isPawn)
//            availableCoords = dynamic_cast<PawnFigure *>(selected)->getMoves(selectedId, field);
//        else
            availableCoords = selected->getMoves(selectedId, field);
        for (auto coord : *availableCoords) {
            field[coord]->mark_movable(true);
        }

    }else if (selected == figure){
        selected->changeSelected(false);
        selected = nullptr;
        for (auto coord : *availableCoords) {
            field[coord]->mark_movable(false);
        }
        delete availableCoords;

    }else{
        for (auto coord : *availableCoords) {
            if(coord == id){

                selected->changeSelected(false);
                for (auto _coord : *availableCoords) {
                    field[_coord]->mark_movable(false);
                }
                delete availableCoords;
                delete field[coord];

                if(selected->isKing && (selectedId%8 - coord%8 == 2 || selectedId%8 - coord%8 == -2)){
                    if(selectedId%8 < coord%8){
                        delete field[coord-1];
                        field[coord] = selected;
                        field[coord-1] = field[selectedId + 3];

                        field[selectedId] = new EmptyFigure(ui->widget);
                        field[selectedId]->btn->show();
                        connect(field[selectedId]->btn, SIGNAL(clicked()), this, SLOT(handleClick()));

                        field[selectedId + 3] = new EmptyFigure(ui->widget);
                        field[selectedId + 3]->btn->show();
                        connect(field[selectedId + 3]->btn, SIGNAL(clicked()), this, SLOT(handleClick()));
                    }else{
                        delete field[coord+1];
                        field[coord] = selected;
                        field[coord+1] = field[selectedId - 4];

                        field[selectedId] = new EmptyFigure(ui->widget);
                        field[selectedId]->btn->show();
                        connect(field[selectedId]->btn, SIGNAL(clicked()), this, SLOT(handleClick()));

                        field[selectedId - 4] = new EmptyFigure(ui->widget);
                        field[selectedId - 4]->btn->show();
                        connect(field[selectedId + 3]->btn, SIGNAL(clicked()), this, SLOT(handleClick()));
                    }
                }
                else{
                    field[coord] = selected;
                    selected->moved = true;
                    field[selectedId] = new EmptyFigure(ui->widget);
                    field[selectedId]->btn->show();
                    connect(field[selectedId]->btn, SIGNAL(clicked()), this, SLOT(handleClick()));
                }
                selected = nullptr;

                isBlackTurn = !isBlackTurn;

                render();

                checkWin();
                break;
            }
        }
    }

}

void MainWindow::resetField(){
//    delete field;
    for (int i = 0; i < 64; ++i) {
        if(field[i] == nullptr)
            delete field[i];
        AbstractFigure *figure;
        if (i >= 8 && i < 16)
            figure = new PawnFigure(false, ui->widget);

        else if (i >= 64-16 && i < 64-8)
            figure = new PawnFigure(true, ui->widget);

        else if(i == 0 || i == 7)
            figure = new RookFigure(false, ui->widget);

        else if(i == 63-7 || i == 63)
            figure = new RookFigure(true, ui->widget);

        else if(i == 1 || i == 6)
            figure = new KnightFigure(false, ui->widget);

        else if(i == 63-6 || i == 62)
            figure = new KnightFigure(true, ui->widget);

        else if(i == 2 || i == 5)
            figure = new BhopFigure(false, ui->widget);

        else if(i == 63-5 || i == 61)
            figure = new BhopFigure(true, ui->widget);

        else if(i == 3)
            figure = new QueenFigure(false, ui->widget);

        else if(i == 63-4)
            figure = new QueenFigure(true, ui->widget);

        else if(i == 4)
            figure = new KingFigure(false, ui->widget);

        else if(i == 63-3)
            figure = new KingFigure(true, ui->widget);

        else
            figure = new EmptyFigure(ui->widget);

        figure->btn->setGeometry(PADDING + i%8 * (SPACING + BUTTON_WIDTH), PADDING + i/8 * (SPACING + BUTTON_HEIGHT), BUTTON_WIDTH, BUTTON_HEIGHT);
        field[i] = figure;
        connect(figure->btn, SIGNAL(clicked()), this, SLOT(handleClick()));
    }
}

void MainWindow::render()
{
    for (int i = 0; i < 64; ++i)
        field[i]->btn->setGeometry(PADDING + i%8 * (SPACING + BUTTON_WIDTH), PADDING + i/8 * (SPACING + BUTTON_HEIGHT), BUTTON_WIDTH, BUTTON_HEIGHT);
}

void MainWindow::checkWin()
{
    int count = 0;
    if(isBlackTurn){
        for (int i = 0; i < 64; ++i){
            if(field[i]->isBlack && field[i]->canMove){
                count += field[i]->getMoves(i, field)->size();
                if(count > 0)
                    break;
            }
        }

        whiteWin = count == 0;
    }

    else{
        for (int i = 0; i < 64; ++i){
            if(!field[i]->isBlack && field[i]->canMove){
                auto tmp = field[i]->getMoves(i, field);
                count += tmp->size();
                if(count > 0)
                    break;
            }
        }

        blackWin = count == 0;
    }

    if(whiteWin || blackWin){
        for (int i = 0; i < 64; ++i){
            delete field[i];
        }
        ui->label->setText(whiteWin ? "white won" : "black won");
    }
}

//void MainWindow::on_pushButton_clicked()
//{

//}
