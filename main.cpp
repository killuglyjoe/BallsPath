#include <iostream>

#include "Utils/ballspathcommandlineparser.h"
#include "Utils/gamemap.h"

int main(int argc, char *argv[])
{
    BallsPathCommandLineParser parser(argc, argv);

    if(!parser.isErrorReadInputArgs()) {
        GameMap game(parser.rowCount(), parser.columnCount(), parser.pointStart(), parser.initialPoints());

        std::list<GameMap::moveDirection> dirList = game.moveItem(parser.pointStart(), parser.pointDest());

        if(dirList.empty())
        {
            std::cout << "there is no path" << std::endl;
            return 0;
        }

        std::cout << "Path steps:" << std::endl;
        for(std::list <GameMap::moveDirection>::const_iterator it = dirList.begin() ; it != dirList.end(); ++it)
        {
            switch (*it) {
            case GameMap::right:
                std::cout << "R ";
                break;
            case GameMap::left:
                std::cout << "L ";
                break;
            case GameMap::up:
                std::cout << "U ";
                break;
            case GameMap::down:
                std::cout << "D ";
                break;
            case GameMap::none:
                break;
            }
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Error parsing input params file" << std::endl;
    }

    return 0;
}
