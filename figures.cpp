#include "figures.h"

AbstractFigure::AbstractFigure(const QString& text, QWidget* parent )
    : QPushButton( text, parent )
{

}

EmptyFigure::EmptyFigure(const QString &text, QWidget *parent) : AbstractFigure (text, parent)
{

}

void EmptyFigure::move(int x, int y){

}

