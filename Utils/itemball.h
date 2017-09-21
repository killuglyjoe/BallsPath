#ifndef ITEMBALL_H
#define ITEMBALL_H

#include "point.h"

class ItemBall
{
public:
    ItemBall(const ItemBall &other);
    ItemBall(const Point &point);

    ItemBall(const int &x = 0,
             const int &y = 0);

    ~ItemBall();

    bool operator == (const ItemBall &other) const;
    bool operator != (const ItemBall &other) const;

    Point pos() const;
    void setPos(const Point &pos);

    bool isValid() const;

    bool isVisible() const;
    void setVisible(bool isVisible);

private:
    bool    m_isVisible; //e.g. transparent
    Point   m_pos;
};

#endif // ITEMBALL_H
