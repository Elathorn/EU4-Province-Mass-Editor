#include "parameters.h"
#include <fstream>
#include <iostream>
using namespace std;

#define LOCATION_FILE_NAME ".\\EU4_provinces_location.txt"

namespace parameters
{
    bool gotLocation = false;
    std::string filesLocation = ".\\tmp\\";

    void getLocationFromFile()
    {
        ifstream in;
        in.open(LOCATION_FILE_NAME);
        if (!in)
        {
            cout << "Can't open files location: " << LOCATION_FILE_NAME << endl;
            cout << "Program won't work as it should" << endl;
            return;
        }
        string loc;
        getline(in, loc);
        filesLocation = loc;
        gotLocation = true;
        in.close();
    }

    std::string getFilesLocation()
    {
        if (!gotLocation)
            getLocationFromFile();
        return filesLocation;
    }
}