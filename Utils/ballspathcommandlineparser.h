#ifndef BALLSPATHCOMMANDLINEPARSER_H
#define BALLSPATHCOMMANDLINEPARSER_H

#include <vector>

#include "point.h"

/**
 * @brief Simple command line parser
 * row count
 * column count
 * starting point (x, y)
 * destination point (x, y)
 * initail map :
 * o000
 * 0o00
 * ....
 * where o is initial point
 */
class BallsPathCommandLineParser
{
public:
    BallsPathCommandLineParser(int argc, char *argv[]);

    size_t rowCount() const;
    size_t columnCount() const;

    Point pointStart() const;
    Point pointDest() const;

    bool isErrorReadInputArgs() const;

    std::vector<Point> initialPoints() const;

protected:
    bool parsePoint(const std::string &pointStr, Point *point);

    void parseInputFile(std::ifstream &inputFile);

    void throwError(const std::string &errorMessage);

private:
    bool m_isErrorReadInputArgs;

    size_t m_rowCount;
    size_t m_columnCount;

    Point m_pointStart;
    Point m_pointDest;

    std::vector<Point> m_initialPoints;
};

#endif // BALLSPATHCOMMANDLINEPARSER_H
