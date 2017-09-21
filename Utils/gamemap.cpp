#include "gamemap.h"

#include "string.h"
#include <queue>
#include <stack>

GameMap::GameMap(const size_t &rows, const size_t &cols, const Point &initialBallPos, const std::vector<Point> &initialPos) :
    m_isValidGame(false),
    m_rows(rows),
    m_columns(cols)
{
    m_gameItems.reserve(m_rows*m_columns);


    for(size_t row = 0; row < m_rows; ++row)
    {
        for(size_t col = 0; col < m_columns; ++col)
        {
            ItemBall *item(new ItemBall(col, row));
//            std::cout <<item->pos()<< std::endl;
            m_gameItems.push_back(item);
        }
    }

    // Initial always first and always visible
    ItemBall *item(getItem(initialBallPos));
    if(item)
        item->setVisible(true);

//    std::cout <<"==============================="<< std::endl;
    // init board
    for(size_t i = 0; i < initialPos.size(); ++i)
    {
//        std::cout <<initialPos[i]<< std::endl;
        ItemBall *item(getItem(initialPos[i]));
        if(item)
        {
//            std::cout << "item" << item->pos() << std::endl;
            item->setVisible(true);
        }
    }

}

GameMap::~GameMap()
{
    for(size_t i = 0; i < m_gameItems.size(); i++)
        delete m_gameItems[i];

    m_gameItems.clear();
}

std::list<GameMap::moveDirection> GameMap::moveItem(const Point &from, const Point &to)
{
    std::list<moveDirection>  dirList;
    ItemBall *item(getItem(from));

    if(item)
    {
        dirList = findPath(from, to);
    }

    char map[m_rows][m_columns];
    memset(&map, '_', sizeof(char)* m_rows*m_columns);

    for(std::vector <ItemBall*>::const_iterator it = m_gameItems.begin() ; it != m_gameItems.end(); ++it)
    {
        ItemBall *ball(*it);
        if(ball->isVisible())
            map[ball->pos().y()][ball->pos().x()] = 'o';
    }

    map[from.y()][from.x()] = 'X';
    map[to.y()][to.x()] = 'F';

    std::cout << "Game board view "<< std::endl;

    for(size_t row = 0; row < m_rows; ++row)
    {
        for(size_t col = 0; col < m_columns; ++col)
        {
            std::cout << map[row][col] << " ";
        }
        std::cout << std::endl;
    }

    return dirList;
}
/**
 * @brief Check if item can block moving
 * @param itemPos
 * @return
 */
ItemBall *GameMap::getItemVisible(const Point &itemPos)
{
    for(std::vector <ItemBall*>::const_iterator it = m_gameItems.begin() ; it != m_gameItems.end(); ++it)
        if((*it)->isVisible())
            if((*it)->pos() == itemPos)
                return *it;

    return nullptr;
}


bool GameMap::isPointContainsInBoard(const Point &checkPosition)
{
    Point firstPoint(0, 0);                 //top left point of game map board
    Point lastPoint(m_columns, m_rows);     //bottom right point of game map board

    return (checkPosition.x() >= firstPoint.x() && (checkPosition.y() >= firstPoint.y()) && (checkPosition < lastPoint) );
}
/**
 * @brief manipulate over item in cell
 * @param itemPos
 * @return
 */
ItemBall *GameMap::getItem(const Point &itemPos)
{
    for(std::vector <ItemBall*>::const_iterator it = m_gameItems.begin() ; it != m_gameItems.end(); ++it)
        if((*it)->pos() == itemPos)
            return *it;

    return nullptr;
}
/**
 * @brief Check can point can be a next point for move to
 * @param checkedPoint
 * @return
 */
bool GameMap::canMoveTo(const Point &checkedPoint)
{
    bool ret = isPointContainsInBoard(checkedPoint) && !getItemVisible(checkedPoint);
    return ret;
}
/**
 * @brief Path finding
 * @param from
 * @param in
 * @return
 */
std::list<GameMap::moveDirection> GameMap::findPath(const Point &from, const Point &in)
{

    checkPoint v[m_columns][m_rows];

    Point k, l;
    std::queue<Point> q;
    std::stack<GameMap::checkPoint> path;
    std::list<moveDirection> directionList;

    for (size_t i=0;i<m_columns;i++)
        for(size_t j=0;j<m_rows;j++)
            v[i][j].mark = 0;

    v[from.x()][from.y()].mark=1;
    q.push(from);

    moveDirection direction(none);

    while (!q.empty())
    {
        k=q.front();

        for (int i=0; i<4; i++)
        {
            l=k;
            switch(i)
            {
                case 0:
                    l.setX(l.x() - 1);
                    break;

                case 1:
                    l.setX(l.x() + 1);
                    break;

                case 2:
                    l.setY(l.y() - 1);
                    break;

                case 3:
                    l.setY(l.y() + 1);
                    break;
            }

            if (canMoveTo(l) && !v[l.x()][l.y()].mark)
            {
                direction = moveDirection(i);
                v[l.x()][l.y()].mark=1;
                v[l.x()][l.y()].pred=k;
                v[l.x()][l.y()].dir=direction;

                q.push(l);
                if (l==in)
                {
                    do
                    {
                        path.push(v[l.x()][l.y()]);
                        l = v[l.x()][l.y()].pred;
                    }
                    while (l!=from);
                    {
                        while(!path.empty()) {
                            directionList.push_back(path.top().dir);
                            path.pop();
                        }
                        return directionList;
                    }
                }
            }
        }
        q.pop();
    }

    return directionList;
}
