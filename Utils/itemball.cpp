#include "itemball.h"

//static int count(-1);

ItemBall::ItemBall(const ItemBall &other) :
    ItemBall(other.pos())
{
}

ItemBall::ItemBall(const Point &point) :
    m_isVisible(false),
    m_pos(point)
{
//    count++;
}

ItemBall::ItemBall(const int &x, const int &y) :
    m_isVisible(false),
    m_pos(Point(x, y))
{
//    count++;
}

ItemBall::~ItemBall()
{
//    std::cout << "~ItemBall " << count << std::endl;
//    count--;
}

bool ItemBall::operator ==(const ItemBall &other) const
{
    return (pos() == other.pos());
}

bool ItemBall::operator !=(const ItemBall &other) const
{
    return (pos() != other.pos());
}

Point ItemBall::pos() const
{
    return m_pos;
}

void ItemBall::setPos(const Point &pos)
{
    m_pos = pos;
}

bool ItemBall::isValid() const
{
    return ( (pos().x() > 0) && (pos().y() > 0) );
}

bool ItemBall::isVisible() const
{
    return m_isVisible;
}

void ItemBall::setVisible(bool isVisible)
{
    m_isVisible = isVisible;
}
