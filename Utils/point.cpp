#include "point.h"

Point::Point(const int &x, const int &y) :
    m_x(x),
    m_y(y)
{

}

Point::Point(const Point &other):
    m_x(other.x()),
    m_y(other.y())
{

}


int Point::x() const
{
    return m_x;
}

void Point::setX(int x)
{
    m_x = x;
}

int Point::y() const
{
    return m_y;
}

void Point::setY(int y)
{
    m_y = y;
}

void Point::operator = (const Point &other)
{
    m_x = other.x();
    m_y = other.y();
}

bool Point::operator == (const Point &other) const
{
    return ( (x() == other.x()) && (y() == other.y()) );
}

bool Point::operator != (const Point &other) const
{
    return ( (x() != other.x()) || (y() != other.y()) );
}

bool Point::operator < (const Point &other) const
{
    return ( (x() < other.x()) && (y() < other.y()) );
}

bool Point::operator <= (const Point &other) const
{
    return ( (x() <= other.x()) && (y() <= other.y()) ) ||  ( (x() < other.x()) && (y() <= other.y()) );
}

bool Point::operator > (const Point &other) const
{
    return ( (x() > other.x()) && (y() > other.y()) );
}

bool Point::operator >= (const Point &other) const
{
    return ( (x() >= other.x()) && (y() > other.y()) ) || ( (x() > other.x()) && (y() >= other.y()) );
}
