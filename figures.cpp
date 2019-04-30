#include "figures.h"

std::vector<int> *AbstractFigure::getMoves(int id, AbstractFigure *field[64], bool canAttack){
    auto result = new std::vector<int>();

    for(auto &movePack : relativeMoves){
        for(auto move : movePack ){
            if (id%8 + move.first > 7 || id%8 + move.first < 0)
                break;
            if (id/8 + move.second > 7 || id/8 + move.second < 0)
                break;

            int coord = move.second * 8 + move.first + id;
            bool attack = false;
            if(coord > 63 || coord < 0)
                break;

            if(field[coord]->isBlack == isBlack && field[coord]->canMove)
                break;

            if(field[coord]->isBlack != isBlack && field[coord]->canMove){
                if(canAttack)
                    attack = true;
                else
                    break;
            }
            //

            auto saved = field[coord];
            field[coord] = this;
            field[id] = new EmptyFigure();
            bool ok = true;

            for (int i = 0; i < 64; ++i)
                if (field[i]->isBlack != isBlack && field[i]->canMove)
                    if(field[i]->canKillKing(i, field)){
                        ok = false;
                        break;
                    }


            field[coord] = saved;
            delete field[id];
            field[id] = this;

            //

            if(ok)
                result->push_back(coord);

            if(attack)
                break;
        }
    }

    return result;
}

bool AbstractFigure::canKillKing(int id, AbstractFigure *field[64])
{
    for(auto &movePack : relativeMoves){
        for(auto move : movePack ){
            if (id%8 + move.first > 7 || id%8 + move.first < 0)
                break;
            if (id/8 + move.second > 7 || id/8 + move.second < 0)
                break;

            int coord = move.second * 8 + move.first + id;
            bool attack = false;
            if(coord > 63 || coord < 0)
                break;

            if(field[coord]->isBlack == isBlack && field[coord]->canMove)
                break;

            if(field[coord]->isBlack != isBlack && field[coord]->canMove)
                attack = true;

            if(attack){
                if(field[coord]->isKing)
                    return true;
                else
                    break;
            }
        }
    }

    return false;
}

void AbstractFigure::setUp()
{
    btn->setIcon(QIcon(ICON_PATHS[iconId].c_str()));
    btn->setIconSize(QSize(50, 50));
}

void AbstractFigure::mark_movable(bool status)
{
    if(status)
        btn->setStyleSheet("border-style: outset;"
                           "border-width: 2px;"
                           "border-color: red;");
    else
        btn->setStyleSheet("");
}

void AbstractFigure::changeSelected(bool status)
{
    if(status)
        btn->setStyleSheet("border-style: outset;"
                           "border-width: 2px;"
                           "border-color: blue;");
    else
        btn->setStyleSheet("");
}

AbstractFigure::~AbstractFigure()
{
    delete btn;
}


void EmptyFigure::mark_movable(bool status)
{
    if(status)
        btn->setStyleSheet("border-style: outset;"
                           "border-width: 2px;"
                           "border-color: green;");
    else
        btn->setStyleSheet("");
}

EmptyFigure::EmptyFigure(QWidget* parent)
{
    canMove = false;
    btn = new QPushButton(QString(""), parent);
}

std::vector<int> *PawnFigure::getMoves(int id, AbstractFigure *field[64], bool canAttack)
{
    if (moved && relativeMoves[0].size() != 1)
        relativeMoves[0].pop_back();

    auto res = this->AbstractFigure::getMoves(id, field, false);

    for(auto &movePack : relativeAttackMoves){
        for(auto move : movePack ){
            if (id%8 + move.first > 7 || id%8 + move.first < 0)
                break;
            if (id/8 + move.second > 7 || id/8 + move.second < 0)
                break;

            int coord = move.second * 8 + move.first + id;
            bool attack = false;
            if(coord > 63 || coord < 0)
                break;

            if(field[coord]->isBlack == isBlack && field[coord]->canMove)
                break;

            if(field[coord]->isBlack != isBlack && field[coord]->canMove)
                attack = true;
            else
                break;
            //

            auto saved = field[coord];
            field[coord] = this;
            field[id] = new EmptyFigure();
            bool ok = true;

            for (int i = 0; i < 64; ++i)
                if (field[i]->isBlack != isBlack && field[i]->canMove)
                    if(field[i]->canKillKing(i, field)){
                        ok = false;
                        break;
                    }


            field[coord] = saved;
            delete field[id];
            field[id] = this;

            //

            if(ok)
                res->push_back(coord);

            if(attack)
                break;
        }
    }

    return res;
}

PawnFigure::PawnFigure(bool _isBlack, QWidget *parent)
{
    isBlack = _isBlack;
//    isPawn = true;

    relativeMoves = std::vector<std::vector<std::pair<int, int>>>();
    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({0 , 1 * (isBlack ? -1 : 1)}),
                                                             std::pair<int, int>({0 , 2 * (isBlack ? -1 : 1)})});

    relativeAttackMoves = std::vector<std::vector<std::pair<int, int>>>();
    relativeAttackMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({-1, 1 * (isBlack ? -1 : 1)})});
    relativeAttackMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({ 1, 1 * (isBlack ? -1 : 1)})});

    iconId = 7 - isBlack;
    btn = new QPushButton("", parent);
    setUp();
}

KnightFigure::KnightFigure(bool _isBlack, QWidget *parent)
{
    relativeMoves = std::vector<std::vector<std::pair<int, int>>>();

    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({-1,-2})});
    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({-1,2})});
    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({1,-2})});
    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({1,2})});
    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({-2,1})});
    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({2,1})});
    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({-2,-1})});
    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({2,-1})});


    isBlack = _isBlack;
    iconId = 5 - isBlack;
    btn = new QPushButton("", parent);
    setUp();
}

KingFigure::KingFigure(bool _isBlack, QWidget *parent)
{

    relativeMoves = std::vector<std::vector<std::pair<int, int>>>();

    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({-1,-1})});
    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({-1, 0})});
    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({-1, 1})});
    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({ 1,-1})});
    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({ 1, 0})});
    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({ 1, 1})});
    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({ 0,-1})});
    relativeMoves.push_back(std::vector<std::pair<int, int>>{std::pair<int, int>({ 0, 1})});

    isBlack = _isBlack;
    isKing = true;
    iconId = 3 - isBlack;
    btn = new QPushButton("", parent);
    setUp();
}

QueenFigure::QueenFigure(bool _isBlack, QWidget *parent)
{
    relativeMoves = std::vector<std::vector<std::pair<int, int>>>();
    relativeMoves.push_back(std::vector<std::pair<int, int>>());
    relativeMoves.push_back(std::vector<std::pair<int, int>>());
    relativeMoves.push_back(std::vector<std::pair<int, int>>());
    relativeMoves.push_back(std::vector<std::pair<int, int>>());
    relativeMoves.push_back(std::vector<std::pair<int, int>>());
    relativeMoves.push_back(std::vector<std::pair<int, int>>());
    relativeMoves.push_back(std::vector<std::pair<int, int>>());
    relativeMoves.push_back(std::vector<std::pair<int, int>>());
    for(int y = 1; y < 8; ++y){
        relativeMoves[0].push_back({0, y});
        relativeMoves[1].push_back({0, -y});
        relativeMoves[2].push_back({y, 0});
        relativeMoves[3].push_back({-y, 0});
        relativeMoves[4].push_back({y, y});
        relativeMoves[5].push_back({y, -y});
        relativeMoves[6].push_back({-y, y});
        relativeMoves[7].push_back({-y, -y});
    }

    isBlack = _isBlack;
    iconId = 9 - isBlack;
    btn = new QPushButton("", parent);
    setUp();
}

BhopFigure::BhopFigure(bool _isBlack, QWidget *parent)
{
    relativeMoves = std::vector<std::vector<std::pair<int, int>>>();
    relativeMoves.push_back(std::vector<std::pair<int, int>>());
    relativeMoves.push_back(std::vector<std::pair<int, int>>());
    relativeMoves.push_back(std::vector<std::pair<int, int>>());
    relativeMoves.push_back(std::vector<std::pair<int, int>>());
    for(int y = 1; y < 8; ++y){
        relativeMoves[0].push_back({y, y});
        relativeMoves[1].push_back({y, -y});
        relativeMoves[2].push_back({-y, y});
        relativeMoves[3].push_back({-y, -y});
    }

    isBlack = _isBlack;
    iconId = 1 - isBlack;
    btn = new QPushButton("", parent);
    setUp();
}

RookFigure::RookFigure(bool _isBlack, QWidget *parent)
{
    relativeMoves = std::vector<std::vector<std::pair<int, int>>>();
    relativeMoves.push_back(std::vector<std::pair<int, int>>());
    relativeMoves.push_back(std::vector<std::pair<int, int>>());
    relativeMoves.push_back(std::vector<std::pair<int, int>>());
    relativeMoves.push_back(std::vector<std::pair<int, int>>());
    for(int y = 1; y < 8; ++y){
        relativeMoves[0].push_back({0, y});
        relativeMoves[1].push_back({0, -y});
        relativeMoves[2].push_back({y, 0});
        relativeMoves[3].push_back({-y, 0});
    }

    isBlack = _isBlack;
    iconId = 11 - isBlack;
    btn = new QPushButton("", parent);
    setUp();
}
