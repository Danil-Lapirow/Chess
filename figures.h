#include <QPushButton>
#include <vector>

#ifndef FIGURES_H
#define FIGURES_H

static std::string ICON_PATHS[12] = {
    "/home/teggot/Programs/Chess/icons/bd.png",
    "/home/teggot/Programs/Chess/icons/bl.png",
    "/home/teggot/Programs/Chess/icons/kd.png",
    "/home/teggot/Programs/Chess/icons/kl.png",
    "/home/teggot/Programs/Chess/icons/nd.png",
    "/home/teggot/Programs/Chess/icons/nl.png",
    "/home/teggot/Programs/Chess/icons/pd.png",
    "/home/teggot/Programs/Chess/icons/pl.png",
    "/home/teggot/Programs/Chess/icons/qd.png",
    "/home/teggot/Programs/Chess/icons/ql.png",
    "/home/teggot/Programs/Chess/icons/rd.png",
    "/home/teggot/Programs/Chess/icons/rl.png",
};

class AbstractFigure{

protected:
    int iconId = 0;
    std::vector<std::vector<std::pair<int, int>>> relativeMoves;
    virtual void setUp();
//    AbstractFigure( const QString& text, QWidget* parent = nullptr );

public:
    bool canMove = true;
    bool moved = false;
    bool isBlack = false;
    bool isKing = false;
    bool isRook = false;
    virtual void mark_movable(bool status);
    void changeSelected(bool status);
    virtual std::vector<int> *getMoves(int id, AbstractFigure *field[64], bool canAttack = true);
    virtual bool canKillKing(int id, AbstractFigure *field[64]);
    QPushButton *btn;
    virtual ~AbstractFigure();
};

class EmptyFigure : public AbstractFigure{
public:
    EmptyFigure(QWidget* parent = nullptr);
    void mark_movable(bool status) override;
//    ~EmptyFigure() override
};

class PawnFigure : public AbstractFigure{
    std::vector<std::vector<std::pair<int, int>>> relativeAttackMoves;
public:
    std::vector<int> *getMoves(int id, AbstractFigure *field[64], bool canAttack = true) override;
    PawnFigure(bool isBlack, QWidget* parent = nullptr);
    bool canKillKing(int id, AbstractFigure *field[64]) override;
//    ~EmptyFigure() override
};

class KnightFigure : public AbstractFigure{
public:
    KnightFigure(bool isBlack, QWidget* parent = nullptr);
//    ~EmptyFigure() override
};

class KingFigure : public AbstractFigure{
public:
    KingFigure(bool isBlack, QWidget* parent = nullptr);
    std::vector<int> *getMoves(int id, AbstractFigure *field[64], bool canAttack = true) override;
//    ~EmptyFigure() override
};

class QueenFigure : public AbstractFigure{
public:
    QueenFigure(bool isBlack, QWidget* parent = nullptr);
//    ~EmptyFigure() override
};

class BhopFigure : public AbstractFigure{
public:
    BhopFigure(bool isBlack, QWidget* parent = nullptr);
//    ~EmptyFigure() override
};

class RookFigure : public AbstractFigure{
public:
    RookFigure(bool isBlack, QWidget* parent = nullptr);
//    ~EmptyFigure() override
};

#endif // FIGURES_H
