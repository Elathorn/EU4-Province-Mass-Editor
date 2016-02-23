#include "Province.h"
using namespace std;



Province::Province(int ID, vector<string>* _inside)
    : id(ID), inside(_inside)
{
}


Province::~Province()
{
}

int Province::addLine(std::string lineToAdd, std::string afterThatLine)
{
    bool notFound;
    Province::vecIt it = getLine(afterThatLine, notFound); //searching for line
    getLine(lineToAdd, notFound); //checking if there is already line like that
    if (notFound) //if it's not
        inside->insert(it, lineToAdd); //inserting after
    return 0;
}

int Province::changeLine(std::string lineToAdd, std::string lineTochange)
{
    bool notFound;
    Province::vecIt it = getLine(lineTochange, notFound); //searching for line
    if (notFound)
        inside->insert(it, lineToAdd); //so we won't override sth we shouldn't overwrite
    else 
        *it = lineToAdd; //change it for new line
    return 0;
}

Province::vecIt Province::getLine(string line, bool & notFound)
{
    notFound = false;
    Province::vecIt it = inside->begin();
    for (it; it != inside->end(); it++)
    {
        if (it->compare(0, line.length(), line) == 0)
            return it;
    }
    it = inside->begin();
    for (int i = 0; i < 4; i++)
        it++;
    notFound = true;
    return it;
}
