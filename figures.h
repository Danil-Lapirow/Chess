#include <QPushButton>
#include <vector>

#ifndef FIGURES_H
#define FIGURES_H

class AbstractFigure : public QPushButton{
    Q_OBJECT

protected:
    int iconId;
    std::vector<int[2]> relativeMoves;
    AbstractFigure( const QString& text, QWidget* parent = nullptr );

public:
    virtual void move(int x, int y){

    }
    virtual ~AbstractFigure(){

    }
};

class EmptyFigure : public AbstractFigure{
public:
    EmptyFigure( const QString& text, QWidget* parent = nullptr );
    void move(int x, int y) override;
    ~EmptyFigure() override
    {

    }
};

#endif // FIGURES_H
