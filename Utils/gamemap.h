#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include <list>

#include "itemball.h"


class GameMap
{
public:
    GameMap(const size_t &rows = 0,
            const size_t &cols = 0,
            const Point &initialBallPos = Point(),
            const std::vector<Point> &initialPos = std::vector<Point>());

    ~GameMap();

    struct moveChars
    {
        char up   = 'U';
        char down = 'D';
        char left = 'L';
        char right= 'R';
    };


    enum moveDirection
    {
        left = 0,
        right,
        up,
        down,
        none
    };

    struct checkPoint
    {
        Point   pred;
        int     mark;
        GameMap::moveDirection dir;
    };

    std::list<moveDirection> moveItem(const Point &from, const Point &to);

    ItemBall *getItem(const Point &itemPos) const;
    ItemBall *getItem(const Point &itemPos);

    ItemBall *getItemVisible(const Point &itemPos) const;
    ItemBall *getItemVisible(const Point &itemPos);

protected:
    std::list<moveDirection> findPath(const Point &from, const Point &in);

    bool canMoveTo(const Point &checkedPoint);
    bool isPointContainsInBoard(const Point &checkPosition);

private:
    bool    m_isValidGame;

    size_t  m_rows;
    size_t  m_columns;

    std::vector<ItemBall*> m_gameItems;   // MxN cells board

};

#endif // GAMEMAP_H
