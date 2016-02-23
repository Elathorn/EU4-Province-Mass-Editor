#include "fileListing.h"
#include <Windows.h>
#include <string>
#include <atlstr.h>
#include "parameters.h"
using namespace std;

namespace fileListing
{

    vector<string>* patternVec;
    vector<string>* filesVec;

    vector<string>* getFilesInDirectory()
    {
        string location = parameters::getFilesLocation() + "*";
        HANDLE dir;
        WIN32_FIND_DATA file_data;
        vector<string>* out = new vector<string>;
        if ((dir = FindFirstFile(location.c_str(), &file_data)) == INVALID_HANDLE_VALUE)
            return nullptr; /* No files found */
        do {
            const string file_name = file_data.cFileName;
            const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

            if (file_name[0] == '.')
                continue;

            if (is_directory)
                continue;

            out->push_back(file_name);
        } while (FindNextFile(dir, &file_data));

        FindClose(dir);
        return out;
    }

    vector<string>* createPattern(vector<int>* pattern)
    {
        vector<string>* patternVec = new vector<string>;
        for (auto i : *pattern)
        {
            patternVec->push_back(to_string(i)); //pushing every int as string to pattern vector
        }
        return patternVec;
    }

    bool checkPattern(const string& filename)
    {
        //patternVec can't be null at this point, it is checked in getListOfFiles

        std::vector<std::string>::iterator i = patternVec->begin();
        while (i != patternVec->end())
        {
            if (filename.compare(0, i->size(), *i) == 0) //checking if begining of file name is same as pattern we want
            {
                if (filename.size() == i->size())
                {
                    patternVec->erase(i); //deleting province ID we already got from list (slighty better perfomance)
                    return true;
                }
                if (!(filename[i->size() + 1] >= 48 && filename[i->size() + 1] <= 57)) //checking if next char in string isn't a number (it would be diffrent province id)
                {
                    patternVec->erase(i);
                    return true;
                }
            }
            i++;
        }
        return false; //we didn't find any pattern which would be ok
    }

    vector<string>* getListOfFiles(vector<int>* pattern)
    {
        filesVec = getFilesInDirectory();
        patternVec = createPattern(pattern);

        if (filesVec == nullptr || patternVec == nullptr)
            return nullptr;

        std::vector<std::string>::iterator it = filesVec->begin();
        while (it != filesVec->end())
        {
            if (checkPattern(*it))
                ++it;
            else
                it = filesVec->erase(it);
        }
        return filesVec;
    }

}