#pragma once
#include <vector>
class Province
{
public:
    /* Basic constructor. Not all provinces have ID inside so it's necessary to get it from filename (sadly) */
    Province(int, std::vector<std::string>* inside);
    ~Province();
    int getID() { return id; }
    int addLine(std::string lineToAdd, std::string afterThatLine);
    int changeLine(std::string lineToAdd, std::string lineTochange);
    std::vector<std::string> getInside() { return *inside; }

private:
    using vecIt = std::vector<std::string>::iterator;
    vecIt getLine(std::string line, bool & notFound);

    int id;
    std::vector<std::string> * inside;
    
};

