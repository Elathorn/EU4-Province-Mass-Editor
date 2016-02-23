#include "ExecuteCommand.h"
#include "parameters.h"
#include <iostream>

using namespace std;

namespace executeCommand
{
    vector<string> overwriteCommandsVec = { "owner", "controller", "culture", "religion", "hre", "base_tax", "base_production",
        "base_manpower", "trade_goods", "capital", "is_city", "estate" };
    vector<string> addCommandsVec = { "add_core" };
#define EXIT_CMD "exit"
#define HELP_CMD "help"
#define PROV_IDS_END 0
#define VALUES_END "NULL"

    bool checkOverwrite(const std::string& command)
    {
        for (auto it : addCommandsVec)
            if (command.compare(it) == 0)
                return false;
        return true;
    }

    void execute(const std::string& command, std::vector<std::string>& values, 
        std::vector<int>* provinces, bool overwriteCommand)
    {
        bool overwrite = checkOverwrite(command);
        vector<string>* locationsVec = fileListing::getListOfFiles(provinces);
        for (auto it : *locationsVec)
        {
            Province * prov = ProvinceLoader::loadProvince(it);
            if (prov != nullptr)
            {
                //Changing files (at that moment only versions loaded to RAM)
                if (overwrite)
                {
                    prov->changeLine(command + " = " + values[0], command); //changing line
                }
                else
                {
                    for (unsigned int i = 0; i < values.size(); i++)
                        prov->addLine(command + " = " + values[i], command); //adding new line for each tag
                }
                //Saving to files
                bool effect = ProvinceLoader::saveProvinces(locationsVec, prov);
            }
            //else
        }
        delete locationsVec;
    }

    void printHelp()
    {
        cout << "Overwrite line command list:" << endl;
        for (auto it : overwriteCommandsVec)
            cout << "\t" << it << endl;
        cout << "Adding new line command list:" << endl;
        for (auto it : addCommandsVec)
            cout << "\t" << it << endl;
        cout << "Usage: [command] [value(s)] " << VALUES_END << " [province IDs] " << PROV_IDS_END << endl;
        cout << "E.g. add_core TUR MAM " << VALUES_END << "  11 12 " << PROV_IDS_END << endl;
        cout << "This command will add core for TUR and MAM in province 11 and 12" << endl;
        cout << "E.g. culture swedish " << VALUES_END << "  55 56 " << PROV_IDS_END << endl;
        cout << "This will change culture for Swedish in province 55 and 56" << endl;
        cout <<  VALUES_END << " and " << PROV_IDS_END << " are necessary, lack of it or wrong usage may result in" << endl;
        cout << "unexpected behavior." << endl;
        cout << "WARNING! Using commands unrecorded in file will result in inserting new lines " << endl;
        cout << "before 5th line. If file is shorter than 5 lines, it will add new lines at end " << endl;
        cout << "of file." << endl << endl;
    }

    /* Checking if command given by user is defined in program */
    bool checkCorrectCommand(string command)
    {
        for (auto it : overwriteCommandsVec)
            if (it == command)
                return true;
        for (auto it : addCommandsVec)
            if (it == command)
                return true;
        return false;
    }

    vector<int> * getProvincesFromUser()
    {
        vector<int> * userInput = new vector<int>;
        int in = -1;
        while (in != PROV_IDS_END)
        {
            cin >> in;
            if (in < 0)
                cout << endl << "Invalid input, province ID value can't be lower than zero." << endl;
            else if (in != PROV_IDS_END) //we don't want to push "it's end" symbol to vector
                userInput->push_back(in);
        }
        return userInput;
    }

    vector<string>  getValuesFromUser()
    {
        vector<string> userInput;
        string str = "";
        while (str != VALUES_END)
        {
            cin >> str;
            if (str != VALUES_END) //we don't want to push "it's end" symbol to vector
                userInput.push_back(str);
        }
        return userInput;
    }

    void createCommand(std::string command)
    {
        if (command == EXIT_CMD)
            return;
        if (command == HELP_CMD)
        {
            printHelp();
            return;
        }
        if (checkCorrectCommand(command))
        {
            vector<string> values = getValuesFromUser(); 
            vector<int> * provs = getProvincesFromUser();
            execute(command, values, provs, checkOverwrite(command));
            cout << "Command executed." << endl;
        }
        else
            cout << "Invalid command. Type \"help\" for help." << endl;
    }
}