#include "ballspathcommandlineparser.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

static const size_t cRequiredMinimumArgumentsCount(4);
static const char cItemChar('o');

BallsPathCommandLineParser::BallsPathCommandLineParser(int argc, char *argv[]) :
    m_isErrorReadInputArgs(false)

{
    if(2 != argc) {
        throwError("No input arguments specified");
        return;
    }

    std::string inputArgsFilePath(argv[1]);

    if(inputArgsFilePath.empty()) {
        throwError("File with params empty");
        return;
    }

    std::ifstream inputFile(inputArgsFilePath.c_str(), std::ios::in);

    if (!inputFile) {
        throwError("ERROR: couldn't read file" );
        return;
    }

    if(!inputFile.std::ios::good()) {
        throwError("ERROR: bad file");
        return;
    }

    parseInputFile(inputFile);

    inputFile.close();

}

void BallsPathCommandLineParser::parseInputFile(std::ifstream &inputFile)
{
    std::string line("");
    std::vector<std::string> params;

    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);

        if (!(iss))
            break;

//        std::cout << line << std::endl;
        params.push_back(line);
    }

    m_rowCount      = std::stoi(params.at(0));
    m_columnCount   = std::stoi(params.at(1));


    if((cRequiredMinimumArgumentsCount + m_rowCount) != params.size()) {
        throwError("Not enough input arguments");
        return;
    }

    // starting point
    if(!parsePoint(params.at(2), &m_pointStart)) {
        throwError("Failed parse start point");
        return;
    }

    // dest point
    if(!parsePoint(params.at(3), &m_pointDest)) {
        throwError("Failed parse destination point");
        return;
    }

    static const int cRowOfset(4);

    // parse intial map
    for(size_t row = cRowOfset; row < params.size(); ++row)
    {
        std::string initialRowString(params.at(row));
        for(size_t col = 0; col < initialRowString.size(); ++col) {
            if(initialRowString[col] == cItemChar)
                m_initialPoints.push_back(Point(col, row-cRowOfset));
        }
    }
}
/**
 * @brief String with point should be looks like - (x, y)
 * @param pointStr
 * @return
 */
bool BallsPathCommandLineParser::parsePoint(const std::string &pointStr, Point *point)
{
    static const char cDelimiter(',');

    std::string simplifiedStr(pointStr);
    simplifiedStr.erase(std::remove(simplifiedStr.begin(), simplifiedStr.end(), '('), simplifiedStr.end());
    simplifiedStr.erase(std::remove(simplifiedStr.begin(), simplifiedStr.end(), ')'), simplifiedStr.end());

    std::istringstream s(simplifiedStr);

    std::string tmp("");
    std::vector<int> vectorXY;

    while(std::getline(s, tmp, cDelimiter))
    {
         if(!tmp.empty())
         {
//             std::cout << tmp << std::endl;
             char * e;
             errno = 0;
             double val(std::strtod(tmp.c_str(), &e));
             if (*e == '\0' ||  // check we didn't consume the entire string
                 errno == 0 )   // check overflow or underflow
             {
                 vectorXY.push_back(val);
//                 std::cout << val << std::endl;
             }
         }
    }

    if(2 != vectorXY.size())
        return false;

    point->setX(vectorXY.at(0));
    point->setY(vectorXY.at(1));

//    std::cout << *point << std::endl;

    return true;
}
/**
 * @brief Simple debug errors
 * @param errorMessage
 */
void BallsPathCommandLineParser::throwError(const std::string &errorMessage)
{
    std::cout << errorMessage << std::endl;
    m_isErrorReadInputArgs = true;
}

std::vector<Point> BallsPathCommandLineParser::initialPoints() const
{
    return m_initialPoints;
}

bool BallsPathCommandLineParser::isErrorReadInputArgs() const
{
    return m_isErrorReadInputArgs;
}

Point BallsPathCommandLineParser::pointDest() const
{
    return m_pointDest;
}

Point BallsPathCommandLineParser::pointStart() const
{
    return m_pointStart;
}

size_t BallsPathCommandLineParser::columnCount() const
{
    return m_columnCount;
}

size_t BallsPathCommandLineParser::rowCount() const
{
    return m_rowCount;
}
