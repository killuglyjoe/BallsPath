#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
public:
    Point(const int &x = -1, const int &y = -1);
    Point(const Point &other);

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);


    void operator = (const Point &other);

    bool operator == (const Point &other) const;
    bool operator != (const Point &other) const;

    bool operator < (const Point &other) const;
    bool operator <= (const Point &other) const;

    bool operator > (const Point &other) const;
    bool operator >= (const Point &other) const;


    friend std::ostream & operator << (std::ostream &stream, const Point &p)
    {
        stream << "Point " << p.x() << " " << p.y() << std::endl << std::flush;
        return stream;
    }

private:
    int m_x;
    int m_y;
};

#endif // POINT_H
