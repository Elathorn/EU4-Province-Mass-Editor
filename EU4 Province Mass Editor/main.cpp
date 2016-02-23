#include "fileListing.h"
#include "ProvinceLoader.h"
#include "ExecuteCommand.h"
#include "parameters.h"

#include <iostream>
#include <string>
using namespace std;

int main()
{
    cout << "Version: " << VERSION_INFO << endl << AUTHOR_INFO << endl << COPYRIGHTS_INFO << endl << WELCOME_INFO << endl << endl;
    string cmd = parameters::getFilesLocation(); //used for initalizing location of provinces
    while (cmd != "exit")
    {
        cin >> cmd;
        executeCommand::createCommand(cmd);
    }
    return 0;
}