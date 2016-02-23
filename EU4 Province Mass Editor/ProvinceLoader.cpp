#include "ProvinceLoader.h"

#include <fstream>
#include <iostream>
#include <string>
#include "ProvinceContainer.h"
#include "parameters.h"
using namespace std;

namespace ProvinceLoader
{
    int getProvinceID(const string& location)
    {
        int intEnd = 0;
        while (location[intEnd] >= 48 && location[intEnd] <= 57) //if it's a number
            intEnd++; //we change number where int ends
        string tmp = location;
        tmp.erase(intEnd + 1, tmp.size());
        return stoi(tmp);
        
    }


    Province* loadProvince(const string& location)
    {
        int id = getProvinceID(location);
        Province * prov = ProvinceContainerSingleton::getProvinceContainer()->getProvince(id);
        if (prov != nullptr)
            return prov;
        ifstream in;
        in.open((parameters::getFilesLocation() + location).c_str(), ifstream::in);
        if (!in)
        {
            cout << "Can't open " << location << endl;
            return nullptr;
        }
        string tmpStr;
        vector<string> * inside = new vector<string>;
        while (getline(in, tmpStr)) //loading content of file
            inside->push_back(tmpStr);
        in.close();
        prov = new Province(id, inside);
        ProvinceContainerSingleton::getProvinceContainer()->addProvince(prov); //adding to container for future use
        return prov;
    }

    bool saveProvinces(vector<string>* locationsVec, Province * prov)
    {
        //search for province location we want to save
        std::vector<std::string>::iterator it = locationsVec->begin();
        string locationToSave = "";
        for (it; it != locationsVec->end(); it++)
        {
            if (getProvinceID(*it) == prov->getID())
            {
                locationToSave = *it;
                break;
            }
        }
        ofstream out;
        out.open((parameters::getFilesLocation() + locationToSave).c_str(), ofstream::out);
        if (!out)
        {
            cout << "Can't save to " << locationToSave << endl;
            return false;
        }
        const vector<string>& inside = prov->getInside();
        for (auto i : inside)
        {
            out << i << endl;
        }
        out.close();
        return true;
    }
}
